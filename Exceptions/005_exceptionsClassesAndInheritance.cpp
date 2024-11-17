#include <iostream>
/* 
    Notes :  Exceptions, classes, and inheritance
    
    1. Exceptions and member functions : Up to this point in the tutorial, you’ve only seen exceptions used in non-member functions. However, exceptions are equally useful in member functions, and even more so in overloaded operators. Consider the following overloaded [] operator as part of a simple integer array class:

        int& IntArray::operator[](const int index)
        {
            return m_data[index];
        }

        - Now if the user passes in an invalid index, the program will cause an assertion error. Unfortunately, because overloaded operators have specific requirements as to the number and type of parameter(s) they can take and return, there is no flexibility for passing back error codes or Boolean values to the caller to handle. However, since exceptions do not change the signature of a function, they can be put to great use here. Here’s an example:

            int& IntArray::operator[](const int index)
            {
                if (index < 0 || index >= getLength())
                    throw index;

                return m_data[index];
            }

    2. When constructors fail : Constructors are another area of classes in which exceptions can be very useful. If a constructor must fail for some reason (e.g. the user passed in invalid input), simply throw an exception to indicate the object failed to create. In such a case, the object’s construction is aborted, and all class members (which have already been created and initialized prior to the body of the constructor executing) are destructed as per usual.

        - However, the class’s destructor is never called (because the object never finished construction). Because the destructor never executes, you can’t rely on said destructor to clean up any resources that have already been allocated.

        - Fortunately, there is a better way. Taking advantage of the fact that class members are destructed even if the constructor fails, if you do the resource allocations inside the members of the class (rather than in the constructor itself), then those members can clean up after themselves when they are destructed.

            class Member
            {
            public:
                Member()
                {
                    std::cerr << "Member allocated some resources\n";
                }

                ~Member()
                {
                    std::cerr << "Member cleaned up\n";
                }
            };

            class A
            {
            private:
                int m_x {};
                Member m_member;

            public:
                A(int x) : m_x{x}
                {
                    if (x <= 0)
                        throw 1;
                }

                ~A()
                {
                    std::cerr << "~A\n"; // should not be called
                }
            };


            int main()
            {
                try
                {
                    A a{0};
                }
                catch (int)
                {
                    std::cerr << "Oops\n";
                }

                return 0;
            }

        - In the above program, when class A throws an exception, all of the members of A are destructed. m_member’s destructor is called, providing an opportunity to clean up any resources that it allocated. This is part of the reason that RAII (covered in lesson 19.3 -- Destructors) is advocated so highly -- even in exceptional circumstances, classes that implement RAII are able to clean up after themselves.

    3. Exception classes : An exception class is just a normal class that is designed specifically to be thrown as an exception. Let’s design a simple exception class to be used with our IntArray class:

        class ArrayException
        {
        private:
            std::string m_error;

        public:
            ArrayException(std::string_view error)
                : m_error{ error }
            {
            }

            const std::string& getError() const { return m_error; }
        };

        class IntArray
        {
        private:
            int m_data[3]{}; // assume array is length 3 for simplicity

        public:
            IntArray() {}

            int getLength() const { return 3; }

            int& operator[](const int index)
            {
                if (index < 0 || index >= getLength())
                    throw ArrayException{ "Invalid index" };

                return m_data[index];
            }

        };

        int main()
        {
            IntArray array;

            try
            {
                int value{ array[5] }; // out of range subscript
            }
            catch (const ArrayException& exception)
            {
                std::cerr << "An array exception occurred (" << exception.getError() << ")\n";
            }
        }

        - Exceptions of a class type should be caught by (const) reference to prevent expensive copying and slicing.

    4. Exceptions and inheritance : Since it’s possible to throw classes as exceptions, and classes can be derived from other classes, we need to consider what happens when we use inherited classes as exceptions. As it turns out, exception handlers will not only match classes of a specific type, they’ll also match classes derived from that specific type as well! Consider the following example:

        class Base
        {
        public:
            Base() {}
        };

        class Derived: public Base
        {
        public:
            Derived() {}
        };

        int main()
        {
            try
            {
                throw Derived();
            }
            catch (const Base& base)
            {
                std::cerr << "caught Base";
            }
            catch (const Derived& derived)
            {
                std::cerr << "caught Derived";
            }

            return 0;
        }

        - In the above example we throw an exception of type Derived. However, the output of this program is:

            caught Base

        - Handlers for derived exception classes should be listed before those for base classes.

    5. std::exception : Many of the classes and operators in the standard library throw exception classes on failure. For example, operator new can throw std::bad_alloc if it is unable to allocate enough memory. A failed dynamic_cast will throw std::bad_cast. And so on. As of C++20, there are 28 different exception classes that can be thrown, with more being added in each subsequent language standard.

        - The good news is that all of these exception classes are derived from a single class called std::exception (defined in the <exception> header). std::exception is a small interface class designed to serve as a base class to any exception thrown by the C++ standard library.

        -   Code Example : 

            #include <cstddef> // for std::size_t
            #include <exception> // for std::exception
            #include <iostream>
            #include <limits>
            #include <string> // for this example

            int main()
            {
                try
                {
                    // Your code using standard library goes here
                    // We'll trigger one of these exceptions intentionally for the sake of the example
                    std::string s;
                    s.resize(std::numeric_limits<std::size_t>::max()); // will trigger a std::length_error or allocation exception
                }
                // This handler will catch std::exception and all the derived exceptions too
                catch (const std::exception& exception)
                {
                    std::cerr << "Standard exception: " << exception.what() << '\n';
                }

                return 0;
            }

        - The above example should be pretty straightforward. The one thing worth noting is that std::exception has a virtual member function named what() that returns a C-style string description of the exception. Most derived classes override the what() function to change the message. Note that this string is meant to be used for descriptive text only -- do not use it for comparisons, as it is not guaranteed to be the same across compilers.

            try
            {
                // code using standard library goes here
            }
            // This handler will catch std::length_error (and any exceptions derived from it) here
            catch (const std::length_error& exception)
            {
                std::cerr << "You ran out of memory!" << '\n';
            }
            // This handler will catch std::exception (and any exception derived from it) that fall
            // through here
            catch (const std::exception& exception)
            {
                std::cerr << "Standard exception: " << exception.what() << '\n';
            }

        - In this example, exceptions of type std::length_error will be caught by the first handler and handled there. Exceptions of type std::exception and all of the other derived classes will be caught by the second handler.

    6. Using the standard exceptions directly : Nothing throws a std::exception directly, and neither should you. However, you should feel free to throw the other standard exception classes in the standard library if they adequately represent your needs. std::runtime_error (included as part of the stdexcept header) is a popular choice, because it has a generic name, and its constructor takes a customizable message:

        #include <exception> // for std::exception
        #include <iostream>
        #include <stdexcept> // for std::runtime_error

        int main()
        {
            try
            {
                throw std::runtime_error("Bad things happened");
            }
            // This handler will catch std::exception and all the derived exceptions too
            catch (const std::exception& exception)
            {
                std::cerr << "Standard exception: " << exception.what() << '\n';
            }

            return 0;
        }

    7. Deriving your own classes from std::exception or std::runtime_error : You can, of course, derive your own classes from std::exception, and override the virtual what() const member function. Here’s the same program as above, with ArrayException derived from std::exception:

        class ArrayException : public std::exception
        {
        private:
            std::string m_error{}; // handle our own string

        public:
            ArrayException(std::string_view error)
                : m_error{error}
            {
            }

            // std::exception::what() returns a const char*, so we must as well
            const char* what() const noexcept override { return m_error.c_str(); }
        };

        class IntArray
        {
        private:
            int m_data[3] {}; // assume array is length 3 for simplicity

        public:
            IntArray() {}

            int getLength() const { return 3; }

            int& operator[](const int index)
            {
                if (index < 0 || index >= getLength())
                    throw ArrayException("Invalid index");

                return m_data[index];
            }

        };

        int main()
        {
            IntArray array;

            try
            {
                int value{ array[5] };
            }
            catch (const ArrayException& exception) // derived catch blocks go first
            {
                std::cerr << "An array exception occurred (" << exception.what() << ")\n";
            }
            catch (const std::exception& exception)
            {
                std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
            }
        }


        - Note that virtual function what() has specifier noexcept (which means the function promises not to throw exceptions itself). Therefore, our override should also have specifier noexcept.

        - Because std::runtime_error already has string handling capabilities, it’s also a popular base class for derived exception classes. std::runtime_error can take a C-style string parameter, or a std::string parameter.

            class ArrayException : public std::runtime_error
            {
            public:
                // std::runtime_error takes a const char* null-terminated string.
                // std::string_view may not be null-terminated, so it's not a good choice here.
                // Our ArrayException will take a const std::string& instead,
                // which is guaranteed to be null-terminated, and can be converted to a const char*.
                ArrayException(const std::string& error)
                    : std::runtime_error{ error } // std::runtime_error will handle the string
                {
                }

                    // no need to override what() since we can just use std::runtime_error::what()
            };

            class IntArray
            {
            private:
                int m_data[3]{}; // assume array is length 3 for simplicity

            public:
                IntArray() {}

                int getLength() const { return 3; }

                int& operator[](const int index)
                {
                    if (index < 0 || index >= getLength())
                        throw ArrayException("Invalid index");

                    return m_data[index];
                }

            };

    8. The lifetime of exceptions : 

        - When an exception is thrown, the object being thrown is typically a temporary or local variable that has been allocated on the stack. However, the process of exception handling may unwind the function, causing all variables local to the function to be destroyed. So how does the exception object being thrown survive stack unwinding?

        - When an exception is thrown, the compiler makes a copy of the exception object to some piece of unspecified memory (outside of the call stack) reserved for handling exceptions. That way, the exception object is persisted regardless of whether or how many times the stack is unwound. The exception is guaranteed to exist until the exception has been handled.

        - This means that the objects being thrown generally need to be copyable (even if the stack is not actually unwound). Smart compilers may be able to perform a move instead, or elide the copy altogether in specific circumstances.

            class Base
            {
            public:
                Base() {}
            };

            class Derived : public Base
            {
            public:
                Derived() {}

                Derived(const Derived&) = delete; // not copyable
            };

            int main()
            {
                Derived d{};

                try
                {
                    throw d; // compile error: Derived copy constructor was deleted
                }
                catch (const Derived& derived)
                {
                    std::cerr << "caught Derived";
                }
                catch (const Base& base)
                {
                    std::cerr << "caught Base";
                }

                return 0;
            }

        - When this program is compiled, the compiler will complain that the Derived copy constructor is not available, and halt compilation. Exception objects should not keep pointers or references to stack-allocated objects. If a thrown exception results in stack unwinding (causing the destruction of stack-allocated objects), these pointers or references may be left dangling.

*/

#include <exception> // for std::exception
#include <string>
#include <string_view>

class ArrayException : public std::exception
{
private:
	std::string m_error{}; // handle our own string

public:
	ArrayException(std::string_view error)
		: m_error{error}
	{
	}

	// std::exception::what() returns a const char*, so we must as well
	const char* what() const noexcept override { return m_error.c_str(); }
};

class IntArray
{
private:
	int m_data[3] {}; // assume array is length 3 for simplicity

public:
	IntArray() {}

	int getLength() const { return 3; }

	int& operator[](const int index)
	{
		if (index < 0 || index >= getLength())
			throw ArrayException("Invalid index");

		return m_data[index];
	}

};

int main()
{
	IntArray array;

	try
	{
		int value{ array[5] };
	}
	catch (const ArrayException& exception) // derived catch blocks go first
	{
		std::cerr << "An array exception occurred (" << exception.what() << ")\n";
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
	}
}