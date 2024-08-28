#include <iostream>
/*

Notes : 

    1. An identifier with external linkage can be seen and used both from the file in which it is defined, and from other code files (via a forward declaration). 
       In this sense, identifiers with external linkage are truly “global” in that they can be used anywhere in your program!

    2. Identifiers with external linkage are visible to the linker. This allows the linker to do two things:

        1- Connect an identifier used in one translation unit with the appropriate definition in another translation unit.

        2- Deduplicate inline identifiers so one canonical definition remains. 

    3. Functions have external linkage by default - 
       In order to call a function defined in another file, you must place a forward declaration for the function in any other files wishing to use the function. The forward declaration tells the compiler about the existence of the function, and the linker connects the function calls to the actual function definition.

    4. Global variables with external linkage - 
       Global variables with external linkage are sometimes called external variables. To make a global variable external (and thus accessible by other files), we can use the extern keyword to do so:

       => int g_x { 2 }; // non-constant globals are external by default

       => const int g_y { 3 }; // const globals are by default internal

       => extern const int g_y { 3 }; // const globals can be defined as extern, making them external
    
       Non-const global variables are external by default (if used, the extern keyword will be ignored).

    5. Variable forward declarations via the extern keyword - 

    => To actually use an external global variable that has been defined in another file, you also must place a forward declaration for the global variable in any other files wishing to use the variable.

    a.cpp:

    // global variable definitions
    int g_x { 2 }; // non-constant globals have external linkage by default
    extern const int g_y { 3 }; // this extern gives g_y external linkage
   
    main.cpp:

    extern int g_x; // this extern is a forward declaration of a variable named g_x that is defined somewhere else
    extern const int g_y; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else

    6. Note that the extern keyword has different meanings in different contexts. In some contexts, extern means “give this variable external linkage”. In other contexts, extern means “this is a forward declaration for an external variable that is defined somewhere else”

    7. Although constexpr variables can be given external linkage via the extern keyword, they can not be forward declared as constexpr. 
    
    This is because the compiler needs to know the value of the constexpr variable (at compile time). If that value is defined in some other file, the compiler has no visibility on what value was defined in that other file.

    However, you can forward declare a constexpr variable as const, which the compiler will treat as a runtime const. This isn’t particularly useful.

    8. Scope determines where a variable is accessible. Duration determines when a variable is created and destroyed. Linkage determines whether the variable can be exported to another file or not.

        -> Global variables have global scope (a.k.a. file scope), which means they can be accessed from the point of declaration to the end of the file in which they are declared.

        -> Global variables have static duration, which means they are created when the program is started, and destroyed when it ends.

        -> Global variables can have either internal or external linkage, via the static and extern keywords respectively.
*/


int main()
{
    return 0;
}