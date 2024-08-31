#include <iostream>

/*

    Notes: 

    1. Type aliases  - In C++, using is a keyword that creates an alias for an existing data type. To create such a type alias, we use the using keyword, followed by a name for the type alias, followed by an equals sign and an existing data type. For example:

        using Distance = double; // define Distance as an alias for type double

    2. Naming type aliases - Name your type aliases starting with a capital letter and do not use a suffix (unless you have a specific reason to do otherwise).

    3. The scope of a type alias - Because scope is a property of an identifier, type alias identifiers follow the same scoping rules as variable identifiers: a type alias defined inside a block has block scope and is usable only within that block, whereas a type alias defined in the global namespace has global scope and is usable to the end of the file.

    4. Typedefs - A typedef (which is short for “type definition”) is an older way of creating an alias for a type. To create a typedef alias, we use the typedef keyword:

        // The following aliases are identical
        typedef long Miles;
        using Miles = long;

    Typedefs are still in C++ for backwards compatibility reasons, but they have been largely replaced by type aliases in modern C++.

    5. Prefer type aliases over typedefs.

    6. Using type aliases for platform independent coding - 

        #ifdef INT_2_BYTES
        using int8_t = char;
        using int16_t = int;
        using int32_t = long;
        #else
        using int8_t = char;
        using int16_t = short;
        using int32_t = int;
        #endif

*/
int main()
{


    return 0;
}