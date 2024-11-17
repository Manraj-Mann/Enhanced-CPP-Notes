#include <iostream>
/* 
    Notes :  
    
    1. Try and catch blocks work well enough in most cases, but there is one particular case in which they are not sufficient. Consider the following example:

        class A
        {
        private:
            int m_x;
        public:
            A(int x) : m_x{x}
            {
                if (x <= 0)
                    throw 1; // Exception thrown here
            }
        };

        class B : public A
        {
        public:
            B(int x) : A{x}
            {
                // What happens if creation of A fails and we want to handle it here?
            }
        };

        int main()
        {
            try
            {
                B b{0};
            }
            catch (int)
            {
                std::cout << "Oops\n";
            }
        }

        - But what if we want to catch the exception inside of B? The call to base constructor A happens via the member initialization list, before the B constructor’s body is called. There’s no way to wrap a standard try block around it. In this situation, we have to use a slightly modified try block called a function try block.

    2. Function try blocks : Function try blocks are designed to allow you to establish an exception handler around the body of an entire function, rather than around a block of code.

        class A
        {
        private:
            int m_x;
        public:
            A(int x) : m_x{x}
            {
                if (x <= 0)
                    throw 1; // Exception thrown here
            }
        };

        class B : public A
        {
        public:
            B(int x) try : A{x} // note addition of try keyword here
            {
            }
            catch (...) // note this is at same level of indentation as the function itself
            {
                        // Exceptions from member initializer list or
                        // from constructor body are caught here

                        std::cerr << "Exception caught\n";

                        throw; // rethrow the existing exception
            }
        };

        int main()
        {
            try
            {
                B b{0};
            }
            catch (int)
            {
                std::cout << "Oops\n";
            }
        }

        - When this program is run, it produces the output:

            Exception caught
            Oops

    3. Limitations on function catch blocks : With a regular catch block (inside a function), we have three options: 
    
        1. We can throw a new exception, 
        
        2. rethrow the current exception, or 
        
        3. resolve the exception (by either a return statement, or by letting control reach the end of the catch block).

        - A function-level catch block for a constructor must either throw a new exception or rethrow the existing exception -- they are not allowed to resolve exceptions! Return statements are also not allowed, and reaching the end of the catch block will implicitly rethrow.

        - A function-level catch block for a destructor can throw, rethrow, or resolve the current exception via a return statement. Reaching the end of the catch block will implicitly rethrow.

        - A function-level catch block for other functions can throw, rethrow, or resolve the current exception via a return statement. Reaching the end of the catch block will implicitly resolve the exception for non-value (void) returning functions and produce undefined behavior for value-returning functions!

        Note : Avoid letting control reach the end of a function-level catch block. Instead, explicitly throw, rethrow, or return.

    4. Function try blocks can catch both base and the current class exceptions : In the above example, if either A or B’s constructor throws an exception, it will be caught by the try block around B’s constructor. We can see that in the following example, where we’re throwing an exception from class B instead of class A:

        class A
        {
        private:
            int m_x;
        public:
            A(int x) : m_x{x}
            {
            }
        };

        class B : public A
        {
        public:
            B(int x) try : A{x} // note addition of try keyword here
            {
                if (x <= 0) // moved this from A to B
                    throw 1; // and this too
            }
            catch (...)
            {
                        std::cerr << "Exception caught\n";

                        // If an exception isn't explicitly thrown here,
                        // the current exception will be implicitly rethrown
            }
        };

        int main()
        {
            try
            {
                B b{0};
            }
            catch (int)
            {
                std::cout << "Oops\n";
            }
        }

        - We get the same output:

            Exception caught
            Oops

    5. Don’t use function try to clean up resources : When construction of an object fails, the destructor of the class is not called. Consequently, you may be tempted to use a function try block as a way to clean up a class that had partially allocated resources before failing. However, referring to members of the failed object is considered undefined behavior since the object is “dead” before the catch block executes. This means that you can’t use function try to clean up after a class. If you want to clean up after a class, follow the standard rules for cleaning up classes that throw exceptions.

    - Function try is useful primarily for either logging failures before passing the exception up the stack, or for changing the type of exception thrown.

*/
int main()
{
    return 0;
}