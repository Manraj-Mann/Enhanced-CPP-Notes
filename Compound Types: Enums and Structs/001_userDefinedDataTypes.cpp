#include <iostream>
/* 
    Notes :  
    
    1. By allowing us to create entirely new, custom types for use in our programs! Such types are often called user-defined types (though we think the term program-defined types is better -- we’ll discuss the difference later in this lesson).

    2. C++ has two different categories of compound types that can be used to create program-defined types:

        1. Enumerated types (including unscoped and scoped enumerations)
        
        2. Class types (including structs, classes, and unions).

    3. Just like type aliases, program-defined types must also be defined before they can be used. The definition for a program-defined type is called a type definition.

    4. Name your program-defined types starting with a capital letter and do not use a suffix.

    5. Every code file that uses a program-defined type needs to see the full type definition before it is used. A forward declaration is not sufficient. This is required so that the compiler knows how much memory to allocate for objects of that type.

    6. To propagate type definitions into the code files that need them, program-defined types are typically defined in header files, and then #included into any code file that requires that type definition. These header files are typically given the same name as the program-defined type (e.g. a program-defined type named Fraction would be defined in Fraction.h)

    7. Type definitions are partially exempt from the one-definition rule (ODR)

*/
int main()
{
    return 0;
}