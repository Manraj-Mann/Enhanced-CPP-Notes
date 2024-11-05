#include <iostream>
/* 
    Notes :  
    
    1. Recapping copy constructors and copy assignment : Copy constructors are used to initialize a class by making a copy of an object of the same class. Copy assignment is used to copy one class object to another existing class object. By default, C++ will provide a copy constructor and copy assignment operator if one is not explicitly provided. These compiler-provided functions do shallow copies, which may cause problems for classes that allocate dynamic memory. So classes that deal with dynamic memory should override these functions to do deep copies.

        - Returning back to our Auto_ptr smart pointer class example from the first lesson in this chapter, let’s look at a version that implements a copy constructor and copy assignment operator that do deep copies, and a sample program that exercises them:

            template<typename T>
            class Auto_ptr3
            {
                T* m_ptr {};

            public:
                Auto_ptr3(T* ptr = nullptr)
                    : m_ptr { ptr }
                {
                }

                ~Auto_ptr3()
                {
                    delete m_ptr;
                }

                // Copy constructor
                // Do deep copy of a.m_ptr to m_ptr
                Auto_ptr3(const Auto_ptr3& a)
                {
                    m_ptr = new T;
                    *m_ptr = *a.m_ptr;
                }

                // Copy assignment
                // Do deep copy of a.m_ptr to m_ptr
                Auto_ptr3& operator=(const Auto_ptr3& a)
                {
                    // Self-assignment detection
                    if (&a == this)
                        return *this;

                    // Release any resource we're holding
                    delete m_ptr;

                    // Copy the resource
                    m_ptr = new T;
                    *m_ptr = *a.m_ptr;

                    return *this;
                }

                T& operator*() const { return *m_ptr; }
                T* operator->() const { return m_ptr; }
                bool isNull() const { return m_ptr == nullptr; }
            };

            class Resource
            {
            public:
                Resource() { std::cout << "Resource acquired\n"; }
                ~Resource() { std::cout << "Resource destroyed\n"; }
            };

            Auto_ptr3<Resource> generateResource()
            {
                Auto_ptr3<Resource> res{new Resource};
                return res; // this return value will invoke the copy constructor
            }

            int main()
            {
                Auto_ptr3<Resource> mainres;
                mainres = generateResource(); // this assignment will invoke the copy assignment

                return 0;
            }

        - Output:

            Resource acquired
            Resource acquired
            Resource destroyed
            Resource acquired
            Resource destroyed
            Resource destroyed

        - So, in short, because we call the copy constructor once to copy construct res to a temporary, and copy assignment once to copy the temporary into mainres, we end up allocating and destroying 3 separate objects in total. Inefficient, but at least it doesn’t crash! However, with move semantics, we can do better.

    2. Move constructors and move assignment : C++11 defines two new functions in service of move semantics: a move constructor, and a move assignment operator. Whereas the goal of the copy constructor and copy assignment is to make a copy of one object to another, the goal of the move constructor and move assignment is to move ownership of the resources from one object to another (which is typically much less expensive than making a copy).

        - Defining a move constructor and move assignment work analogously to their copy counterparts. However, whereas the copy flavors of these functions take a const l-value reference parameter (which will bind to just about anything), the move flavors of these functions use non-const rvalue reference parameters (which only bind to rvalues).

        - Here’s the same Auto_ptr3 class as above, with a move constructor and move assignment operator added. We’ve left in the deep-copying copy constructor and copy assignment operator for comparison purposes.

            // move constructor
            Auto_ptr3(Auto_ptr3 &&a) noexcept : m_ptr(a.m_ptr) 
            {
                // std::cout<<"move constructor"<<std::endl;
                a.m_ptr = nullptr;
            }

            // move assignment
            Auto_ptr3& operator=(Auto_ptr3 &&a)
            {
                // std::cout<<"move assignement"<<std::endl;
                if(this == &a)
                {
                    return *this;
                }

                delete m_ptr;
                m_ptr = a.m_ptr;
                a.m_ptr = nullptr;

                return *this;
            }
        
        - The move constructor and move assignment operator are simple. Instead of deep copying the source object (a) into the destination object (the implicit object), we simply move (steal) the source object’s resources. This involves shallow copying the source pointer into the implicit object, then setting the source pointer to null.

        - The flow of the program is exactly the same as before. However, instead of calling the copy constructor and copy assignment operators, this program calls the move constructor and move assignment operators. Looking a little more deeply:

            1. Inside generateResource(), local variable res is created and initialized with a dynamically allocated Resource, which causes the first “Resource acquired”.
        
            2. Res is returned back to main() by value. Res is move constructed into a temporary object, transferring the dynamically created object stored in res to the temporary object. We’ll talk about why this happens below.
        
            3. Res goes out of scope. Because res no longer manages a pointer (it was moved to the temporary), nothing interesting happens here.
        
            4. The temporary object is move assigned to mainres. This transfers the dynamically created object stored in the temporary to mainres.
        
            5. The assignment expression ends, and the temporary object goes out of expression scope and is destroyed. However, because the temporary no longer manages a pointer (it was moved to mainres), nothing interesting happens here either.
        
            6. At the end of main(), mainres goes out of scope, and our final “Resource destroyed” is displayed.
        
        - So instead of copying our Resource twice (once for the copy constructor and once for the copy assignment), we transfer it twice. This is more efficient, as Resource is only constructed and destroyed once instead of three times.

        - Move constructors and move assignment should be marked as noexcept. This tells the compiler that these functions will not throw exceptions.

    3. When are the move constructor and move assignment called?

        - The move constructor and move assignment are called when those functions have been defined, and the argument for construction or assignment is an rvalue. Most typically, this rvalue will be a literal or temporary value.

        - The copy constructor and copy assignment are used otherwise (when the argument is an lvalue, or when the argument is an rvalue and the move constructor or move assignment functions aren’t defined).

    4. Implicit move constructor and move assignment operator :

        - The compiler will create an implicit move constructor and move assignment operator if all of the following are true:

            = There are no user-declared copy constructors or copy assignment operators.
            = There are no user-declared move constructors or move assignment operators.
            = There is no user-declared destructor.

        - These functions do a memberwise move, which behaves as follows:

            = If member has a move constructor or move assignment (as appropriate), it will be invoked.
            = Otherwise, the member will be copied.
        
            * Notably, this means that pointers will be copied, not moved!

    5. The key insight behind move semantics : "Move semantics is an optimization opportunity."

        - If we construct an object or do an assignment where the argument is an l-value, the only thing we can reasonably do is copy the l-value. We can’t assume it’s safe to alter the l-value, because it may be used again later in the program. If we have an expression “a = b” (where b is an lvalue), we wouldn’t reasonably expect b to be changed in any way.

        - However, if we construct an object or do an assignment where the argument is an r-value, then we know that r-value is just a temporary object of some kind. Instead of copying it (which can be expensive), we can simply transfer its resources (which is cheap) to the object we’re constructing or assigning. This is safe to do because the temporary will be destroyed at the end of the expression anyway, so we know it will never be used again!

        - C++11, through r-value references, gives us the ability to provide different behaviors when the argument is an r-value vs an l-value, enabling us to make smarter and more efficient decisions about how our objects should behave.

    6. Move functions should always leave both objects in a valid state :  

        - In the above examples, both the move constructor and move assignment functions set a.m_ptr to nullptr. This may seem extraneous -- after all, if a is a temporary r-value, why bother doing “cleanup” if parameter a is going to be destroyed anyway?

        - The answer is simple: When a goes out of scope, the destructor for a will be called, and a.m_ptr will be deleted. If at that point, a.m_ptr is still pointing to the same object as m_ptr, then m_ptr will be left as a dangling pointer. When the object containing m_ptr eventually gets used (or destroyed), we’ll get undefined behavior.

        - When implementing move semantics, it is important to ensure the moved-from object is left in a valid state, so that it will destruct properly (without creating undefined behavior).

    7. Automatic l-values returned by value may be moved instead of copied : 

        - In the generateResource() function of the Auto_ptr4 example above, when variable res is returned by value, it is moved instead of copied, even though res is an l-value. The C++ specification has a special rule that says automatic objects returned from a function by value can be moved even if they are l-values. This makes sense, since res was going to be destroyed at the end of the function anyway! We might as well steal its resources instead of making an expensive and unnecessary copy.

        - Although the compiler can move l-value return values, in some cases it may be able to do even better by simply eliding the copy altogether (which avoids the need to make a copy or do a move at all). In such a case, neither the copy constructor nor move constructor would be called.

    8. Disabling copying - In the Auto_ptr4 class above, we left in the copy constructor and assignment operator for comparison purposes. But in move-enabled classes, it is sometimes desirable to delete the copy constructor and copy assignment functions to ensure copies aren’t made. In the case of our Auto_ptr class, we don’t want to copy our templated object T -- both because it’s expensive, and whatever class T is may not even support copying! Example : 

        - 	// Copy constructor -- no copying allowed!
            Auto_ptr5(const Auto_ptr5& a) = delete;

        - 	// Copy assignment -- no copying allowed!
	        Auto_ptr5& operator=(const Auto_ptr5& a) = delete;

    9. Deleting the move constructor and move assignment : 

        - You can delete the move constructor and move assignment using the = delete syntax in the exact same way you can delete the copy constructor and copy assignment.

        - The rule of five says that if the copy constructor, copy assignment, move constructor, move assignment, or destructor are defined or deleted, then each of those functions should be defined or deleted.

    10. Issues with move semantics and std::swap :

        - Copy and swap also works for move semantics, meaning we can implement our move constructor and move assignment by swapping resources with the object that will be destroyed.

        - This has two benefits:

            1. The persistent object now controls the resources that were previously under ownership of the dying object (which was our primary goal).
            
            2. The dying object now controls the resources that were previously under ownership of the persistent object. When the dying object actually dies, it can do any kind of cleanup required on those resources.

        - When you think about swapping, the first thing that comes to mind is usually std::swap(). However, implementing the move constructor and move assignment using std::swap() is problematic, as std::swap() calls both the move constructor and move assignment on move-capable objects. This will result in an infinite recursion issue.

            class Name
            {
            private:
                std::string m_name {}; // std::string is move capable

            public:
                Name(std::string_view name) : m_name{ name }
                {
                }

                Name(const Name& name) = delete;
                Name& operator=(const Name& name) = delete;

                Name(Name&& name) noexcept
                {
                    std::cout << "Move ctor\n";

                    std::swap(*this, name); // bad!
                }

                Name& operator=(Name&& name) noexcept
                {
                    std::cout << "Move assign\n";

                    std::swap(*this, name); // bad!

                    return *this;
                }

                const std::string& get() const { return m_name; }
            };

            int main()
            {
                Name n1{ "Alex" };
                n1 = Name{"Joe"}; // invokes move assignment

                std::cout << n1.get() << '\n';

                return 0;
            }
        
        - You can implement the move constructor and move assignment using your own swap function, as long as your swap member function does not call the move constructor or move assignment. 


*/


template<typename T>
class Auto_ptr3
{
	T* m_ptr {};

public:
	Auto_ptr3(T* ptr = nullptr)
		: m_ptr { ptr }
	{
	}

	~Auto_ptr3()
	{
		delete m_ptr;
	}

	// Copy constructor
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr3(const Auto_ptr3& a) = delete;

	// Copy assignment
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr3& operator=(const Auto_ptr3& a) = delete;

    // move constructor
    Auto_ptr3(Auto_ptr3 &&a) noexcept 
    : m_ptr(a.m_ptr) 
    {
        std::cout<<"move constructor"<<std::endl;
        a.m_ptr = nullptr;
    }

    // move assignment
    Auto_ptr3& operator=(Auto_ptr3 &&a) noexcept
    {
        std::cout<<"move assignement"<<std::endl;
        if(this == &a)
        {
            return *this;
        }

        delete m_ptr;
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;

        return *this;
    }

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

#include <algorithm>

template <typename T>
class DynamicArray
{
    T * _arr;
    int _len;

    public:

    DynamicArray(int size) : _arr{new T[size]} , _len{size}
    {

    }

    ~DynamicArray()
    { 
        delete [] _arr;
    }

    // copy constructor
    DynamicArray(const DynamicArray& copy) :
    _len{copy._len}
    {
        _arr = new T[_len];
        std::copy_n(copy._arr , _len , _arr);
    }

    // copy assignment
    DynamicArray& operator=(const DynamicArray &copy)
    {
        if(this == &copy)
        {
            return *this;
        }

        delete [] _arr;
        _len = copy._len;
        _arr = new T[_len];

        std::copy_n(copy._arr , _len , _arr);

        return *this;
    }

    // move constructor
    DynamicArray(DynamicArray &&copy) noexcept
    : _arr{copy._arr} , _len{copy._len}
    {
        copy._len = 0;
        copy._arr = nullptr;
    }

    // move assignment
    DynamicArray & operator=(DynamicArray && copy) noexcept
    {

        if(this == &copy)
        {
            return *this;
        }

        delete [] _arr;

        _len = copy._len;
        _arr = copy._arr;

        copy._len = 0;
        copy._arr = nullptr;

        return *this;
    }


    int getLength() const
    {
        return _len;
    }

    T & operator[](int index)
    {
        return _arr[index];
    }

    const T & operator[](int index) const
    {
        return _arr[index];
    }

};

#include <chrono>

class Timer
{
    using Clock = std::chrono::high_resolution_clock;
    using Nanosecond = std::chrono::duration<double, std::nano>;

    std::chrono::time_point<Clock> _begin { Clock::now() };

public:
    void reset()
    {
        _begin = Clock::now();
    }

    double elapsed()
    {
        return std::chrono::duration_cast<Nanosecond>(Clock::now() - _begin).count();
    }
};

Auto_ptr3<Resource> generateResource()
{
	Auto_ptr3<Resource> res{new Resource};
	return res; // this return value will invoke the copy/move constructor
}

// Return a copy of arr with all of the values doubled
DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int> &arr)
{
	DynamicArray<int> dbl(arr.getLength());
	for (int i = 0; i < arr.getLength(); ++i)
		dbl[i] = arr[i] * 2;

	return dbl;
}
#include <iomanip>  // For std::setprecision
int main()
{
	// Auto_ptr3<Resource> mainres;
	// mainres = generateResource(); // this assignment will invoke the copy/move assignment

    Timer t;

	DynamicArray<int> arr(1000000);

	for (int i = 0; i < arr.getLength(); i++)
		arr[i] = i;

	arr = cloneArrayAndDouble(arr);

	std::cout <<std::setprecision(20)<<t.elapsed()<<" ns"<<std::endl;

	return 0;
}