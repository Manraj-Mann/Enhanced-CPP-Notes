#include <iostream>

/*

    Notes : 

    1. A halt is a flow control statement that terminates the program. In C++, halts are implemented as functions (rather than keywords), so our halt statements will be function calls.

    2. A special function called std::exit() is called, with the return value from main() (the status code) passed in as an argument. 

    3. The std::exit() function : 

        => std::exit() is a function that causes the program to terminate normally. Normal termination means the program has exited in an expected way. Note that the term normal termination does not imply anything about whether the program was successful (that’s what the status code is for). 

        => std::exit() performs a number of cleanup functions. First, "objects with static storage duration are destroyed". Then some other miscellaneous file cleanup is done if any files were used. Finally, control is returned back to the OS, with the argument passed to std::exit() used as the status code.

    4. Calling std::exit() explicitly : 

        => Although std::exit() is called implicitly after function main() returns, std::exit() can also be called explicitly to halt the program before it would normally terminate. When std::exit() is called this way, you will need to include the cstdlib header.

    5. std::exit() does not clean up local variables : 

        => The std::exit() function does not clean up local variables in the current function or up the call stack.

    6. std::atexit : 

        Because std::exit() terminates the program immediately, you may want to manually do some cleanup before terminating. In this context, cleanup means things like closing database or network connections, deallocating any memory you have allocated, writing information to a log file, etc…

        => When an application exits, modern OSes will generally clean up any memory that the application does not properly clean up itself. 

        void cleanup()
        {
            // code here to do any kind of cleanup required
            std::cout << "cleanup!\n";
        }

        // register cleanup() to be called automatically when std::exit() is called
        std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now

        std::cout << 1 << '\n';

        std::exit(0); // terminate and return status code 0 to operating system

        => A few notes here about std::atexit() and the cleanup function: 
        
        1. First, because std::exit() is called implicitly when main() terminates, this will invoke any functions registered by std::atexit() if the program exits that way. 
        
        2. Second, the function being registered must take no parameters and have no return value. Finally, you can register multiple cleanup functions using std::atexit() if you want, and they will be called in reverse order of registration (the last one registered will be called first).

    7. In multi-threaded programs, calling std::exit() can cause your program to crash (because the thread calling std::exit() will cleanup static objects that may still be accessed by other threads). 
    
    For this reason, C++ has introduced another pair of functions that work similarly to std::exit() and std::atexit() called std::quick_exit() and std::at_quick_exit(). std::quick_exit() terminates the program normally, but does not clean up static objects, and may or may not do other types of cleanup. std::at_quick_exit() performs the same role as std::atexit() for programs terminated with std::quick_exit().

    8. std::abort and std::terminate : C++ contains two other halt-related functions.

    9. The std::abort() function causes your program to terminate abnormally. Abnormal termination means the program had some kind of unusual runtime error and the program couldn’t continue to run. For example, trying to divide by 0 will result in an abnormal termination. std::abort() does not do any cleanup.

    The std::terminate() function is typically used in conjunction with exceptions (we’ll cover exceptions in a later chapter). Although std::terminate can be called explicitly, it is more often called implicitly when an exception isn’t handled (and in a few other exception-related cases). By default, std::terminate() calls std::abort().

    10. Only use a halt if there is no safe or reasonable way to return normally from the main function. If you haven’t disabled exceptions, prefer using exceptions for handling errors safely.


*/

int main()
{
    return 0;
}