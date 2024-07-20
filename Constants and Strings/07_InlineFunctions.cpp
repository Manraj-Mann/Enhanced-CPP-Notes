#include <iostream>

/*

Notes : 

1. We have two functions : 1. Inline 2. Functions

2. One downside of using a function is that every time a function is called, there is a certain amount of performance overhead that occurs

function ( x , y ) is a function -
When a call to function() is encountered, the CPU must store the address of the current instruction it is executing (so it knows where to return to later) along with the values of various CPU registers (so they can be restored upon returning). Then parameters x and y must be instantiated and then initialized. Then the execution path has to jump to the code in the function() function. When the function ends, the program has to jump back to the location of the function call, and the return value has to be copied so it can be output. This has to be done for each function call.

3. Then whats better ? Depends what function does , in case its complex this cost is insignificant so it doesn't matter. If its not complex or does not do lot's for work we can go for inline expansion.

Example : 

int min(int x, int y)
{
    return (x < y) ? x : y;
}

4. Inline expansion : Inline expansion is a process where a function call is replaced by the code from the called function’s definition.

Above example inline expanded : 

int main()
{
    std::cout << ((5 < 6) ? 5 : 6) << '\n';
    std::cout << ((3 < 2) ? 3 : 2) << '\n';
    return 0;
}

5. The performance of inline code : 

    5.1. Beyond removing the cost of function call, inline expansion can also allow the compiler to optimize the resulting code more efficiently.

    5.2. Inline expansion has its own potential cost: if the body of the function being expanded takes more instructions than the function call being replaced, then each inline expansion will cause the executable to grow larger. Larger executables tend to be slower (due to not fitting as well in memory caches).

    Note : Cache Implications
    When the executable grows larger due to the inlining of large functions, it might exceed the size of the CPU's cache. This can lead to more cache misses, where the CPU has to fetch data from slower main memory instead of the fast cache. Consequently, the performance can degrade despite the potential gains from eliminating function call overhead.

6. Modern optimizing compilers make the decision about when functions should be expanded inline.

7. The inline keyword, historically :

=> Compilers were not smart enough so c++ added the inline keyword to hint compiler that function can be inlined

inline int min(int x, int y) // inline keyword means this function is an inline function
{
    return (x < y) ? x : y;
}

Modern optimizing compilers are typically good at determining which function calls should be made inline -- better than humans in most cases. As a result, the compiler will likely ignore or devalue any use of inline to request inline expansion for your functions.

Best practice : Do not use the inline keyword to request inline expansion for your functions.

8. The inline keyword, modernly:

In modern C++, the term inline has evolved to mean “multiple definitions are allowed”. Thus, an inline function is one that is allowed to be defined in multiple translation units (without violating the ODR).

Rule : The compiler needs to be able to see the full definition of an inline function wherever it is used, and all such definitions must be identical (or undefined behavior will result).

The linker will consolidate all inline function definitions for an identifier into a single definition (thus still meeting the requirements of the one definition rule).

The following are implicitly inline:

    1. Functions defined inside a class, struct, or union type definition.
    2. Constexpr / consteval functions.
    3. Functions implicitly instantiated from function templates.

9. Inline variables C++17: Inline variables, which are variables that are allowed to be defined in multiple files. Inline variables work similarly to inline functions, and have the same requirements



*/

inline int min(int x, int y) // inline keyword means this function is an inline function
{
    return (x < y) ? x : y;
}

int main()
{

    return 0;
}
