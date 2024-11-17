#include <iostream>
/* 
    Notes :  
    
    1. Cleaning up resources : 

        - One of the biggest problems that new programmers run into when using exceptions is the issue of cleaning up resources when an exception occurs. Consider the following example:

            #include <iostream>
            try
            {
                openFile(filename);
                writeFile(filename, data);
                closeFile(filename);
            }
            catch (const FileException& exception)
            {
                std::cerr << "Failed to write to file: " << exception.what() << '\n';
            }

        - Try this : 

            #include <iostream>

            try
            {
                openFile(filename);
                writeFile(filename, data);
            }
            catch (const FileException& exception)
            {
                std::cerr << "Failed to write to file: " << exception.what() << '\n';
            }

            // Make sure file is closed
            closeFile(filename);


        - The best option (whenever possible) is to prefer to stack allocate objects that implement RAII (automatically allocate resources on construction, deallocate resource on destruction). That way when the object managing the resource goes out of scope for any reason, it will automatically deallocate as appropriate, so we don’t have to worry about such things!

    2. Exceptions and destructors : Unlike constructors, where throwing exceptions can be a useful way to indicate that object creation did not succeed, exceptions should never be thrown in destructors.

        - The problem occurs when an exception is thrown out of a destructor during the stack unwinding process. If that happens, the compiler is put in a situation where it doesn’t know whether to continue the stack unwinding process or handle the new exception. The end result is that your program will be terminated immediately.

        - Consequently, the best course of action is just to abstain from using exceptions in destructors altogether. Write a message to a log file instead.

        - If an exception is thrown out of a destructor during stack unwinding, the program will be halted.

    3. Performance concerns : Exceptions do come with a small performance price to pay. They increase the size of your executable, and they may also cause it to run slower due to the additional checking that has to be performed. However, the main performance penalty for exceptions happens when an exception is actually thrown. In this case, the stack must be unwound and an appropriate exception handler found, which is a relatively expensive operation.

        - As a note, some modern computer architectures support an exception model called zero-cost exceptions. Zero-cost exceptions, if supported, have no additional runtime cost in the non-error case (which is the case we most care about performance). However, they incur an even larger penalty in the case where an exception is found.

    4. So when should I use exceptions? Exception handling is best used when all of the following are true:

        - The error being handled is likely to occur only infrequently.
        - The error is serious and execution could not continue otherwise.
        - The error cannot be handled at the place where it occurs.
        - There isn’t a good alternative way to return an error code back to the caller.



*/
int main()
{
    return 0;
}