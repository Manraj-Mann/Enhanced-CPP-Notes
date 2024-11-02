#include <iostream>
/* 
    Notes :  
    
    1. The memory that a program uses is typically divided into a few different areas, called segments:

        - The code segment (also called a text segment), where the compiled program sits in memory. The code segment is typically read-only.
        - The bss segment (also called the uninitialized data segment), where zero-initialized global and static variables are stored.
        - The data segment (also called the initialized data segment), where initialized global and static variables are stored.
        - The heap, where dynamically allocated variables are allocated from.
        - The call stack, where function parameters, local variables, and other function-related information are stored.

    2. The heap segment - 

        - The heap segment (also known as the “free store”) keeps track of memory used for dynamic memory allocation. 
        - In C++, when you use the new operator to allocate memory, this memory is allocated in the application’s heap segment.
        - Assuming an int is 4 bytes:

            int* ptr { new int }; // new int allocates 4 bytes in the heap
            int* array { new int[10] }; // new int[10] allocates 40 bytes in the heap
        
        - The address of this memory is passed back by operator new, and can then be stored in a pointer. You do not have to worry about the mechanics behind the process of how free memory is located and allocated to the user. However, it is worth knowing that sequential memory requests may not result in sequential memory addresses being allocated!

        - When a dynamically allocated variable is deleted, the memory is “returned” to the heap and can then be reassigned as future allocation requests are received. Remember that deleting a pointer does not delete the variable, it just returns the memory at the associated address back to the operating system.

        - The heap has advantages and disadvantages:

            - Allocating memory on the heap is comparatively slow.
            - Allocated memory stays allocated until it is specifically deallocated (beware memory leaks) or the application ends (at which point the OS should clean it up).
            - Dynamically allocated memory must be accessed through a pointer. Dereferencing a pointer is slower than accessing a variable directly.
            - Because the heap is a big pool of memory, large arrays, structures, or classes can be allocated here.

    3. The call stack - 

        The call stack (usually referred to as “the stack”) has a much more interesting role to play. The call stack keeps track of all the active functions (those that have been called but have not yet terminated) from the start of the program to the current point of execution, and handles allocation of all function parameters and local variables.

        The call stack is implemented as a stack data structure.

    4. The call stack segment -  The call stack segment holds the memory used for the call stack. When the application starts, the main() function is pushed on the call stack by the operating system. Then the program begins executing.

        - When a function call is encountered, the function is pushed onto the call stack. When the current function ends, that function is popped off the call stack (this process is sometimes called unwinding the stack). Thus, by looking at the functions that are currently on the call stack, we can see all of the functions that were called to get to the current point of execution.

        - The stack itself is a fixed-size chunk of memory addresses. The mailboxes are memory addresses, and the “items” we’re pushing and popping on the stack are called stack frames. A stack frame keeps track of all of the data associated with one function call. We’ll talk more about stack frames in a bit. The “marker” is a register (a small piece of memory in the CPU) known as the stack pointer (sometimes abbreviated “SP”). The stack pointer keeps track of where the top of the call stack currently is.

        - We can make one further optimization: When we pop an item off the call stack, we only have to move the stack pointer down -- we don’t have to clean up or zero the memory used by the popped stack frame (the equivalent of emptying the mailbox). This memory is no longer considered to be “on the stack” (the stack pointer will be at or below this address), so it won’t be accessed. If we later push a new stack frame to this same memory, it will overwrite the old value we never cleaned up.

    5. The call stack in action : 

        - Let’s examine in more detail how the call stack works. Here is the sequence of steps that takes place when a function is called:

            1. The program encounters a function call.
            
            2. A stack frame is constructed and pushed on the stack. The stack frame consists of:
            
                - The address of the instruction beyond the function call (called the return address). This is how the CPU remembers where to return to after the called function exits.
                - All function arguments.
                - Memory for any local variables
                - Saved copies of any registers modified by the function that need to be restored when the function returns
            
            3. The CPU jumps to the function’s start point.
            
            4. The instructions inside of the function begin executing.
        
        - When the function terminates, the following steps happen:

            1. Registers are restored from the call stack
        
            2. The stack frame is popped off the stack. This frees the memory for all local variables and arguments.
        
            3. The return value is handled.
        
            4. The CPU resumes execution at the return address.
        
        - Return values can be handled in a number of different ways, depending on the computer’s architecture. Some architectures include the return value as part of the stack frame. Others use CPU registers.

        - Typically, it is not important to know all the details about how the call stack works. However, understanding that functions are effectively pushed on the stack when they are called and popped off (unwound) when they return gives you the fundamentals needed to understand recursion, as well as some other concepts that are useful when debugging.

        - A technical note: on some architectures, the call stack grows away from memory address 0. On others, it grows towards memory address 0. As a consequence, newly pushed stack frames may have a higher or a lower memory address than the previous ones.
                
    6. Stack overflow - 

        - The stack has a limited size, and consequently can only hold a limited amount of information. On Visual Studio for Windows, the default stack size is 1MB. With g++/Clang for Unix variants, it can be as large as 8MB. If the program tries to put too much information on the stack, stack overflow will result. Stack overflow happens when all the memory in the stack has been allocated -- in that case, further allocations begin overflowing into other sections of memory.

        - Stack overflow is generally the result of allocating too many variables on the stack, and/or making too many nested function calls (where function A calls function B calls function C calls function D etc…) On modern operating systems, overflowing the stack will generally cause your OS to issue an access violation and terminate the program.

        - This program tries to allocate a huge (likely 40MB) array on the stack. Because the stack is not large enough to handle this array, the array allocation overflows into portions of memory the program is not allowed to use.

        - Here’s another program that will cause a stack overflow for a different reason:

            int g_counter{ 0 };

            void eatStack()
            {
                std::cout << ++g_counter << ' ';

                // We use a conditional here to avoid compiler warnings about infinite recursion
                if (g_counter > 0)
                    eatStack(); // note that eatStack() calls itself

                // Needed to prevent compiler from doing tail-call optimization
                std::cout << "hi";
            }

            int main()
            {
                eatStack();

                return 0;
            }

        - In the above program, a stack frame is pushed on the stack every time function eatStack() is called. Since eatStack() calls itself (and never returns to the caller), eventually the stack will run out of memory and cause an overflow.

    7. The stack has advantages and disadvantages:

        - Allocating memory on the stack is comparatively fast.
        - Memory allocated on the stack stays in scope as long as it is on the stack. It is destroyed when it is popped off the stack.
        - All memory allocated on the stack is known at compile time. Consequently, this memory can be accessed directly through a variable.
        - Because the stack is relatively small, it is generally not a good idea to do anything that eats up lots of stack space. This includes allocating or copying large arrays or other memory-intensive structures.

    8. Get stack memory available : ulimit -s , used by exe : ./your_executable & pmap <pid_of_your_process> | grep stack

*/

int g_counter{ 0 };

void eatStack()
{
    std::cout << ++g_counter << ' ';

    // We use a conditional here to avoid compiler warnings about infinite recursion
    if (g_counter > 0)
        eatStack(); // note that eatStack() calls itself

    // Needed to prevent compiler from doing tail-call optimization
    std::cout << "hi";
}

int main()
{
    int *ptr {new int};
    int *arr{new int[10]};

    std::cout<<(new int)<<std::endl;

    // int stack[10000000]; // stack overflow
    // std::cout << "hi" << stack[0]; // we'll use stack[0] here so the compiler won't optimize the array away

    eatStack();

    return 0;
}