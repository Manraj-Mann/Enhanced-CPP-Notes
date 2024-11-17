#include <iostream>
/* 
    Notes :  
    
    1. Throwing exceptions : In C++, a throw statement is used to signal that an exception or error case has occurred (think of throwing a penalty flag). Signaling that an exception has occurred is also commonly called raising an exception. To use a throw statement, simply use the throw keyword, followed by a value of any data type you wish to use to signal that an error has occurred. Typically, this value will be an error code, a description of the problem, or a custom exception class.

        throw -1; // throw a literal integer value
        throw ENUM_INVALID_INDEX; // throw an enum value
        throw "Can not take square root of negative number"; // throw a literal C-style (const char*) string
        throw dX; // throw a double variable that was previously defined
        throw MyException("Fatal Error"); // Throw an object of class MyException

    2. Looking for exceptions : In C++, we use the try keyword to define a block of statements (called a try block). The try block acts as an observer, looking for any exceptions that are thrown by any of the statements within the try block. Here’s an example of a try block:

        try
        {
            // Statements that may throw exceptions you want to handle go here
            throw -1; // here's a trivial throw statement
        }

    3. Handling exceptions : Actually handling exceptions is the job of the catch block(s). The catch keyword is used to define a block of code (called a catch block) that handles exceptions for a single data type. Here’s an example of a catch block that will catch integer exceptions:

        catch (int x)
        {
            // Handle an exception of type int here
            std::cerr << "We caught an int exception with value" << x << '\n';
        }

        Note : No type conversion is done for exceptions (so an int exception will not be converted to match a catch block with a double parameter).

    4. Putting throw, try, and catch together : 

        int main()
        {
            try
            {
                // Statements that may throw exceptions you want to handle go here
                throw -1; // here's a trivial example
            }
            catch (double) // no variable name since we don't use the exception itself in the catch block below
            {
                // Any exceptions of type double thrown within the above try block get sent here
                std::cerr << "We caught an exception of type double\n";
            }
            catch (int x)
            {
                // Any exceptions of type int thrown within the above try block get sent here
                std::cerr << "We caught an int exception with value: " << x << '\n';
            }
            catch (const std::string&) // catch classes by const reference
            {
                // Any exceptions of type std::string thrown within the above try block get sent here
                std::cerr << "We caught an exception of type std::string\n";
            }

            // Execution continues here after the exception has been handled by any of the above catch blocks
            std::cout << "Continuing on our merry way\n";

            return 0;
        }

    5. Recapping exception handling : Exception handling is actually quite simple, and the following two paragraphs cover most of what you need to remember about it:

        1. When an exception is raised (using throw), the running program finds the nearest enclosing try block (propagating up the stack if necessary to find an enclosing try block -- we’ll discuss this in more detail next lesson) to see if any of the catch handlers attached to the try block can handle that type of exception. If so, execution jumps to the top of the catch block, the exception is considered handled.
        
        2. If no appropriate catch handlers exist in the nearest enclosing try block, the program continues to look at subsequent enclosing try blocks for a catch handler. If no appropriate catch handlers can be found before the end of the program, the program will fail with a runtime exception error.

        3. Note that the program will not perform implicit conversions or promotions when matching exceptions with catch blocks! For example, a char exception will not match with an int catch block. An int exception will not match a float catch block. However, casts from a derived class to one of its parent classes will be performed.

    6. Exceptions are handled immediately : Here’s a short program that demonstrates how exceptions are handled immediately:

        int main()
        {
            try
            {
                throw 4.5; // throw exception of type double
                std::cout << "This never prints\n";
            }
            catch (double x) // handle exception of type double
            {
                std::cerr << "We caught a double of value: " << x << '\n';
            }

            return 0;
        }

        - This program is about as simple as it gets. Here’s what happens: the throw statement is the first statement that gets executed -- this causes an exception of type double to be raised. Execution immediately moves to the nearest enclosing try block, which is the only try block in this program. The catch handlers are then checked to see if any handler matches. Our exception is of type double, so we’re looking for a catch handler of type double. We have one, so it executes.

        - Consequently, the result of this program is as follows:

            We caught a double of value: 4.5

    7. What catch blocks typically do :  If an exception is routed to a catch block, it is considered “handled” even if the catch block is empty. However, typically you’ll want your catch blocks to do something useful. There are four common things that catch blocks do when they catch an exception:

        1. First, catch blocks may print an error (either to the console, or a log file) and then allow the function to proceed.

        2. Second, catch blocks may return a value or error code back to the caller.

        3. Third, a catch block may throw another exception. Because the catch block is outside of the try block, the newly thrown exception in this case is not handled by the preceding try block -- it’s handled by the next enclosing try block.

        4. Fourth, a catch block in main() may be used to catch fatal errors and terminate the program in a clean way.

*/

int main()
{
    try
    {
        // Statements that may throw exceptions you want to handle go here
        throw -1; // here's a trivial example
    }
    catch (double) // no variable name since we don't use the exception itself in the catch block below
    {
        // Any exceptions of type double thrown within the above try block get sent here
        std::cerr << "We caught an exception of type double\n";
    }
    catch (int x)
    {
        // Any exceptions of type int thrown within the above try block get sent here
        std::cerr << "We caught an int exception with value: " << x << '\n';
    }
    catch (const std::string&) // catch classes by const reference
    {
        // Any exceptions of type std::string thrown within the above try block get sent here
        std::cerr << "We caught an exception of type std::string\n";
    }

    // Execution continues here after the exception has been handled by any of the above catch blocks
    std::cout << "Continuing on our merry way\n";

    return 0;
}