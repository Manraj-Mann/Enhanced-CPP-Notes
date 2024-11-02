#include <iostream>
/* 
    Notes :  
    
    1. A recursive function in C++ is a function that calls itself. A tail call is a function call that occurs at the tail (end) of a function. Functions with recursive tail calls are fairly easy for the compiler to optimize into an iterative (non-recursive) function. Such a function would not cause the system to run out of stack space. If you run the above program and it runs forever, this is likely what happened.

    2. Recursive termination conditions - Recursive function calls generally work just like normal function calls. However, the program above illustrates the most important difference with recursive functions: you must include a recursive termination condition, or they will run “forever” (actually, until the call stack runs out of memory). A recursive termination is a condition that, when met, will cause the recursive function to stop calling itself.

    3. Recursive function calls generally work just like normal function calls. However, the program above illustrates the most important difference with recursive functions: you must include a recursive termination condition, or they will run “forever” (actually, until the call stack runs out of memory). A recursive termination is a condition that, when met, will cause the recursive function to stop calling itself.

    4. Recursive algorithms - 

        Recursive functions typically solve a problem by first finding the solution to a subset of the problem (recursively), and then modifying that sub-solution to get to a solution. In the above algorithm, sumTo(value) first solves sumTo(value-1), and then adds the value of variable value to find the solution for sumTo(value).

        In many recursive algorithms, some inputs produce trivial outputs. For example, sumTo(1) has the trivial output 1 (you can calculate this in your head), and does not benefit from further recursion. Inputs for which an algorithm trivially produces an output is called a base case. Base cases act as termination conditions for the algorithm. Base cases can often be identified by considering the output for an input of 0, 1, “”, ”, or null.

    5. Memoization algorithms - 

        The above recursive Fibonacci algorithm isn’t very efficient, in part because each call to a Fibonacci non-base case results in two more Fibonacci calls. This produces an exponential number of function calls (in fact, the above example calls fibonacci() 1205 times!). There are techniques that can be used to reduce the number of calls necessary. One technique, called memoization, caches the results of expensive function calls so the result can be returned when the same input occurs again.

    6. Recursive vs iterative -

        One question that is often asked about recursive functions is, “Why use a recursive function if you can do many of the same tasks iteratively (using a for loop or while loop)?”. It turns out that you can always solve a recursive problem iteratively -- however, for non-trivial problems, the recursive version is often much simpler to write (and read). For example, while it’s possible to write the Fibonacci function iteratively, it’s a little more difficult! (Try it!)

        Iterative functions (those using a for-loop or while-loop) are almost always more efficient than their recursive counterparts. This is because every time you call a function there is some amount of overhead that takes place in pushing and popping stack frames. Iterative functions avoid this overhead.

        That’s not to say iterative functions are always a better choice. Sometimes the recursive implementation of a function is so much cleaner and easier to follow that incurring a little extra overhead is more than worth it for the benefit in maintainability, particularly if the algorithm doesn’t need to recurse too many times to find a solution.

        In general, recursion is a good choice when most of the following are true:

            - The recursive code is much simpler to implement.
            - The recursion depth can be limited (e.g. there’s no way to provide an input that will cause it to recurse down 100,000 levels).
            - The iterative version of the algorithm requires managing a stack of data.
            - This isn’t a performance-critical section of code.
        
        However, if the recursive algorithm is simpler to implement, it may make sense to start recursively and then optimize to an iterative algorithm later.

*/
int main()
{
    return 0;
}