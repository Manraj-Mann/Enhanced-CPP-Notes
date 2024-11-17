#include <iostream>
/* 
    Notes :  
    
    1. Throwing exceptions from a called function : In the prior lesson, we noted, “a try block detects any exceptions that are thrown by statements within the try block”. In the corresponding examples, our throw statements were placed within a try block, and caught by an associated catch block, all within the same function. Having to both throw and catch exceptions within a single function is of limited value.

        - Try blocks catch exceptions not only from statements within the try block, but also from functions that are called within the try block.

            // A modular square root function
            double mySqrt(double x)
            {
                // If the user entered a negative number, this is an error condition
                if (x < 0.0)
                    throw "Can not take sqrt of negative number"; // throw exception of type const char*

                return std::sqrt(x);
            }

            int main()
            {
                std::cout << "Enter a number: ";
                double x {};
                std::cin >> x;

                try // Look for exceptions that occur within try block and route to attached catch block(s)
                {
                    double d = mySqrt(x);
                    std::cout << "The sqrt of " << x << " is " << d << '\n';
                }
                catch (const char* exception) // catch exceptions of type const char*
                {
                    std::cerr << "Error: " << exception << std::endl;
                }

                return 0;
            }

    2. Exception handling and stack unwinding : 

        - When an exception is thrown, the program first looks to see if the exception can be handled immediately inside the current function (meaning the exception was thrown within a try block inside the current function, and there is a corresponding catch block associated). If the current function can handle the exception, it does so.

        - If not, the program next checks whether the function’s caller (the next function up the call stack) can handle the exception. In order for the function’s caller to handle the exception, the call to the current function must be inside a try block, and a matching catch block must be associated. If no match is found, then the caller’s caller (two functions up the call stack) is checked. Similarly, in order for the caller’s caller to handle the exception, the call to the caller must be inside a try block, and a matching catch block must be associated.

        - The process of checking each function up the call stack continues until either a handler is found, or all of the functions on the call stack have been checked and no handler can be found. If a matching exception handler is found, then execution jumps from the point where the exception is thrown to the top of the matching catch block. This requires unwinding the stack (removing the current function from the call stack) as many times as necessary to make the function handling the exception the top function on the call stack.

        - If no matching exception handler is found, the stack may or may not be unwound. We will talk more about this case in the next lesson (27.4 -- Uncaught exceptions and catch-all handlers). When the current function is removed from the call stack, all local variables are destroyed as usual, but no value is returned.

    3. Another stack unwinding example

*/

void D() // called by C()
{
    std::cout << "Start D\n";
    std::cout << "D throwing int exception\n";

    throw - 1;

    std::cout << "End D\n"; // skipped over
}

void C() // called by B()
{
    std::cout << "Start C\n";
    D();
    std::cout << "End C\n";
}

void B() // called by A()
{
    std::cout << "Start B\n";

    try
    {
        C();
    }
    catch (double) // not caught: exception type mismatch
    {
        std::cerr << "B caught double exception\n";
    }

    try
    {
    }
    catch (int) // not caught: exception not thrown within try
    {
        std::cerr << "B caught int exception\n";
    }

    std::cout << "End B\n";
}

void A() // called by main()
{
    std::cout << "Start A\n";

    try
    {
        B();
    }
    catch (int) // exception caught here and handled
    {
        std::cerr << "A caught int exception\n";
    }
    catch (double) // not called because exception was handled by prior catch block
    {
        std::cerr << "A caught double exception\n";
    }

    // execution continues here after the exception is handled
    std::cout << "End A\n";
}

int main()
{
    std::cout << "Start main\n";

    try
    {
        A();
    }
    catch (int) // not called because exception was handled by A
    {
        std::cerr << "main caught int exception\n";
    }
    std::cout << "End main\n";

    return 0;
}