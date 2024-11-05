#include <iostream>
/* 
    Notes :  
    
    1. std::unique_ptr : std::unique_ptr is the C++11 replacement for std::auto_ptr. It should be used to manage any dynamically allocated object that is not shared by multiple objects. That is, std::unique_ptr should completely own the object it manages, not share that ownership with other classes. std::unique_ptr lives in the <memory> header.

        - Example : 

            #include <iostream>
            #include <memory> // for std::unique_ptr

            class Resource
            {
            public:
                Resource() { std::cout << "Resource acquired\n"; }
                ~Resource() { std::cout << "Resource destroyed\n"; }
            };

            int main()
            {
                // allocate a Resource object and have it owned by std::unique_ptr
                std::unique_ptr<Resource> res{ new Resource() };

                return 0;
            } // res goes out of scope here, and the allocated Resource is destroyed

        - Because the std::unique_ptr is allocated on the stack here, it’s guaranteed to eventually go out of scope, and when it does, it will delete the Resource it is managing. Unlike std::auto_ptr, std::unique_ptr properly implements move semantics.

            Example : 

                std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
                std::unique_ptr<Resource> res2{}; // Start as nullptr

                std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
                std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

                // res2 = res1; // Won't compile: copy assignment is disabled
                res2 = std::move(res1); // res2 assumes ownership, res1 is set to null

                std::cout << "Ownership transferred\n";

                std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
                std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

            Output : 

                Resource acquired
                res1 is not null
                res2 is null
                Ownership transferred
                res1 is null
                res2 is not null
                Resource destroyed

        - Because std::unique_ptr is designed with move semantics in mind, copy initialization and copy assignment are disabled. If you want to transfer the contents managed by std::unique_ptr, you must use move semantics. In the program above, we accomplish this via std::move (which converts res1 into an r-value, which triggers a move assignment instead of a copy assignment).

    2. Accessing the managed object : std::unique_ptr has an overloaded operator* and operator-> that can be used to return the resource being managed. Operator* returns a reference to the managed resource, and operator-> returns a pointer.

        Example : 

            std::unique_ptr<Resource> res{ new Resource{} };

            if (res) // use implicit cast to bool to ensure res contains a Resource
                std::cout << *res << '\n'; // print the Resource that res is owning

    3. std::unique_ptr and arrays : Unlike std::auto_ptr, std::unique_ptr is smart enough to know whether to use scalar delete or array delete, so std::unique_ptr is okay to use with both scalar objects and arrays. However, std::array or std::vector (or std::string) are almost always better choices than using std::unique_ptr with a fixed array, dynamic array, or C-style string.

    4. std::make_unique : C++14 comes with an additional function named std::make_unique(). This templated function constructs an object of the template type and initializes it with the arguments passed into the function.

        - Example : 

            class Fraction
            {
            private:
                int m_numerator{ 0 };
                int m_denominator{ 1 };

            public:
                Fraction(int numerator = 0, int denominator = 1) :
                    m_numerator{ numerator }, m_denominator{ denominator }
                {
                }

                friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
                {
                    out << f1.m_numerator << '/' << f1.m_denominator;
                    return out;
                }
            };


            int main()
            {
                // Create a single dynamically allocated Fraction with numerator 3 and denominator 5
                // We can also use automatic type deduction to good effect here
                auto f1{ std::make_unique<Fraction>(3, 5) };
                std::cout << *f1 << '\n';

                // Create a dynamically allocated array of Fractions of length 4
                auto f2{ std::make_unique<Fraction[]>(4) };
                std::cout << f2[0] << '\n';

                return 0;
            }

        - Use of std::make_unique() is optional, but is recommended over creating std::unique_ptr yourself. This is because code using std::make_unique is simpler, and it also requires less typing (when used with automatic type deduction). Furthermore, in C++14 it resolves an exception safety issue that can result from C++ leaving the order of evaluation for function arguments unspecified.

    5. The exception safety issue in more detail : Consider an expression like this one - 

            => some_function(std::unique_ptr<T>(new T), function_that_can_throw_exception());
    
        - The compiler is given a lot of flexibility in terms of how it handles this call. It could create a new T, then call function_that_can_throw_exception(), then create the std::unique_ptr that manages the dynamically allocated T. If function_that_can_throw_exception() throws an exception, then the T that was allocated will not be deallocated, because the smart pointer to do the deallocation hasn’t been created yet. This leads to T being leaked.

        - std::make_unique() doesn’t suffer from this problem because the creation of the object T and the creation of the std::unique_ptr happen inside the std::make_unique() function, where there’s no ambiguity about order of execution.

        - This issue was fixed in C++17, as evaluation of function arguments can no longer be interleaved.

    6. Returning std::unique_ptr from a function : std::unique_ptr can be safely returned from a function by value:

        std::unique_ptr<Resource> createResource()
        {
            return std::make_unique<Resource>();
        }

        int main()
        {
            auto ptr{ createResource() };

            // do whatever

            return 0;
        }

        - In the above code, createResource() returns a std::unique_ptr by value. If this value is not assigned to anything, the temporary return value will go out of scope and the Resource will be cleaned up. If it is assigned (as shown in main()), in C++14 or earlier, move semantics will be employed to transfer the Resource from the return value to the object assigned to (in the above example, ptr), and in C++17 or newer, the return will be elided. This makes returning a resource by std::unique_ptr much safer than returning raw pointers!

        - In general, you should not return std::unique_ptr by pointer (ever) or reference (unless you have a specific compelling reason to).

    7. Passing std::unique_ptr to a function : 

        - If you want the function to take ownership of the contents of the pointer, pass the std::unique_ptr by value. Note that because copy semantics have been disabled, you’ll need to use std::move to actually pass the variable in.

            class Resource
            {
            public:
                Resource() { std::cout << "Resource acquired\n"; }
                ~Resource() { std::cout << "Resource destroyed\n"; }
            };

            std::ostream& operator<<(std::ostream& out, const Resource&)
            {
                out << "I am a resource";
                return out;
            }

            // This function takes ownership of the Resource, which isn't what we want
            void takeOwnership(std::unique_ptr<Resource> res)
            {
                if (res)
                    std::cout << *res << '\n';
            } // the Resource is destroyed here

            int main()
            {
                auto ptr{ std::make_unique<Resource>() };

            //    takeOwnership(ptr); // This doesn't work, need to use move semantics
                takeOwnership(std::move(ptr)); // ok: use move semantics

                std::cout << "Ending program\n";

                return 0;
            }

        - Note that in this case, ownership of the Resource was transferred to takeOwnership(), so the Resource was destroyed at the end of takeOwnership() rather than the end of main().

        - However, most of the time, you won’t want the function to take ownership of the resource. Although you can pass a std::unique_ptr by const reference (which will allow the function to use the object without assuming ownership), it’s better to just pass the resource itself (by pointer or reference, depending on whether null is a valid argument). This allows the function to remain agnostic of how the caller is managing its resources.

        - To get a raw pointer from a std::unique_ptr, you can use the get() member function:

            class Resource
            {
            public:
                Resource() { std::cout << "Resource acquired\n"; }
                ~Resource() { std::cout << "Resource destroyed\n"; }
            };

            std::ostream& operator<<(std::ostream& out, const Resource&)
            {
                out << "I am a resource";
                return out;
            }

            // The function only uses the resource, so we'll accept a pointer to the resource, not a reference to the whole std::unique_ptr<Resource>
            void useResource(const Resource* res)
            {
                if (res)
                    std::cout << *res << '\n';
                else
                    std::cout << "No resource\n";
            }

            int main()
            {
                auto ptr{ std::make_unique<Resource>() };

                useResource(ptr.get()); // note: get() used here to get a pointer to the Resource

                std::cout << "Ending program\n";

                return 0;
            } // The Resource is destroyed here

    8. std::unique_ptr and classes : 

        - You can, of course, use std::unique_ptr as a composition member of your class. This way, you don’t have to worry about ensuring your class destructor deletes the dynamic memory, as the std::unique_ptr will be automatically destroyed when the class object is destroyed.

        - However, if the class object is not destroyed properly (e.g. it is dynamically allocated and not deallocated properly), then the std::unique_ptr member will not be destroyed either, and the object being managed by the std::unique_ptr will not be deallocated.

    9. Misusing std::unique_ptr : 

        - There are two easy ways to misuse std::unique_ptrs, both of which are easily avoided. First, don’t let multiple objects manage the same resource. For example:

            Resource* res{ new Resource() };
            std::unique_ptr<Resource> res1{ res };
            std::unique_ptr<Resource> res2{ res };

            => While this is legal syntactically, the end result will be that both res1 and res2 will try to delete the Resource, which will lead to undefined behavior.

        - Second, don’t manually delete the resource out from underneath the std::unique_ptr.

            Resource* res{ new Resource() };
            std::unique_ptr<Resource> res1{ res };
            delete res;

        - If you do, the std::unique_ptr will try to delete an already deleted resource, again leading to undefined behavior. Note that std::make_unique() prevents both of the above cases from happening inadvertently.

*/
#include <memory> // for std::unique_ptr
#include <iostream>

class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

std::ostream& operator<<(std::ostream& out, const Resource&)
{
	out << "I am a resource";
	return out;
}

// The function only uses the resource, so we'll accept a pointer to the resource, not a reference to the whole std::unique_ptr<Resource>
void useResource(const Resource* res)
{
	if (res)
		std::cout << *res << '\n';
	else
		std::cout << "No resource\n";
}

int main()
{
	std::unique_ptr<Resource> ptr{ std::make_unique<Resource>() };

	useResource(ptr.get()); // note: get() used here to get a pointer to the Resource

	std::cout << "Ending program\n";

	return 0;
} // The Resource is destroyed here