#include <iostream>
/* 
    Notes :  
    
    1. Member functions can be defined outside the class definition just like non-member functions. The only difference is that we must prefix the member function names with the name of the class type (in this case, Date::) so the compiler knows we’re defining a member of that class type rather than a non-member.

    => Note that we left the access functions defined inside the class definition. Because access functions are typically only one line, defining these functions inside the class definition adds minimal clutter, whereas moving them outside the class definition would result in many extra lines of code. For this reason, the definitions of access functions (and other trivial, one-line functions) are often left inside the class definition.

    2. Putting class definitions in a header file - 

        => If you define a class inside a source (.cpp) file, that class is only usable within that particular source file. In larger programs, it’s common that we’ll want to use the classes we write in multiple source files.

        => Unlike functions, which only need a forward declaration to be used, the compiler typically needs to see the full definition of a class (or any program-defined type) in order for the type to be used. This is because the compiler needs to understand how members are declared in order to ensure they are used properly, and it needs to be able to calculate how large objects of that type are in order to instantiate them. So our header files usually contain the full definition of a class rather than just a forward declaration of the class.

    3. Naming your class header and code files - 

        => Most often, classes are defined in header files of the same name as the class, and any member functions defined outside of the class are put in a .cpp file of the same name as the class.

        => Now any other header or code file that wants to use the Date class can simply #include "Date.h". Note that Date.cpp also needs to be compiled into any project that uses Date.h so that the linker can connect calls to the member functions to their definitions.

    4. Doesn’t defining a class in a header file violate the one-definition rule if the header is #included more than once?

        => Types are exempt from the part of the one-definition rule (ODR) that says you can only have one definition per program. Therefore, there isn’t an issue #including class definitions into multiple translation units. If there was, classes wouldn’t be of much use.

        => Including a class definition more than once into a single translation unit is still an ODR violation. However, header guards (or #pragma once) will prevent this from happening.

    5. Inline member functions - Functions defined inside the class definition are implicitly inline, which allows them to be #included into multiple code files without violating the ODR. Functions defined outside the class definition are not implicitly inline. They can be made inline by using the inline keyword.

    6. Inline expansion of member functions - The compiler must be able to see a full definition of a function in order to perform inline expansion. Most often, such functions (e.g. access functions) are defined inside the class definition. However, if you want to define a member function outside the class definition, but still want it to be eligible for inline expansion, you can define it as an inline function just below the class definition (in the same header file). That way the definition of the function is accessible to anybody who #includes the header.

    7. Default arguments for member functions : Put any default arguments for member functions inside the class definition.

    8. Libraries : 
    
        => The header files provide the declarations that the compiler requires in order to validate that the programs you’re writing are syntactically correct. However, the implementations for the classes that belong to the C++ standard library are contained in a precompiled file that is linked in automatically at the link stage. You never see the code.

        => Many open source software packages provide both .h and .cpp files for you to compile into your program. However, most commercial libraries provide only .h files and a precompiled library file. There are several reasons for this: 1) It’s faster to link a precompiled library than to recompile it every time you need it, 2) A single copy of a precompiled library can be shared by many applications, whereas compiled code gets compiled into every executable that uses it (inflating file sizes), and 3) Intellectual property reasons (you don’t want people stealing your code).

*/
int main()
{
    return 0;
}