#include <iostream>


/*

    Note : 
    
    1. Global constants as internal variables : 

        Prior to C++17, the following is the easiest and most common solution:
        1.1.Create a header file to hold these constants
        1.2.Inside this header file, define a namespace (discussed in lesson 7.2 -- User-defined namespaces and the scope resolution operator)
        1.3.Add all your constants inside the namespace (make sure they’re constexpr)
        1.4.#include the header file wherever you need it

    2. The above method has a few potential downsides.

        Therefore, if constants.h gets included into 20 different code files, each of these variables is duplicated 20 times. Header guards won’t stop this from happening, as they only prevent a header from being included more than once into a single including file, not from being included one time into multiple different code files. This introduces two challenges:

        2.1. Changing a single constant value would require recompiling every file that includes the constants header, which can lead to lengthy rebuild times for larger projects.

        2.2. If the constants are large in size and can’t be optimized away, this can use a lot of memory.
    
    3. One way to avoid these problems is by turning these constants into external variables.

        constants.cpp - contain the extenal linkage of variables

        #include "constants.h"
        namespace constants
        {
            // actual global variables
            extern constexpr double pi { 3.14159 };
            extern constexpr double avogadro { 6.0221413e23 };
            extern constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
        }

        constants.h   - contian the forward declarartion
            
        #ifndef CONSTANTS_H
        #define CONSTANTS_H

        namespace constants
        {
            // since the actual variables are inside a namespace, the forward declarations need to be inside a namespace as well
            // we can't forward declare variables as constexpr, but we can forward declare them as (runtime) const
            extern const double pi;
            extern const double avogadro;
            extern const double myGravity;
        }

        #endif


        However, there are a couple of downsides to this method. First, these constants are now considered compile-time constants only within the file they are actually defined in (constants.cpp). In other files, the compiler will only see the forward declaration, which doesn’t define a constexpr value (and must be resolved by the linker). This means in other files, these are treated as runtime constant values, not compile-time constants. Thus outside of constants.cpp, these variables can’t be used anywhere that requires a compile-time constant. Second, because compile-time constants can typically be optimized more than runtime constants, the compiler may not be able to optimize these as much.

        Given the above downsides, prefer defining your constants in a header file

    4. Global constants as inline variables 

        Remember : Constexpr functions are implicitly inline, but constexpr variables are not implicitly inline. If you want an inline constexpr variable, you must explicitly mark it as inline

        Inline variables have external linkage by default, so that they are visible to the linker. This is necessary so the linker can de-duplicate the definitions.

        Non-inline constexpr variables have internal linkage. If included into multiple translation units, each translation unit will get its own copy of the variable. This is not an ODR violation because they are not exposed to the linker.

        // define your own namespace to hold constants
        namespace constants
        {
            inline constexpr double pi { 3.14159 }; // note: now inline constexpr
            inline constexpr double avogadro { 6.0221413e23 };
            inline constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
            // ... other related constants
        }

        => We can include constants.h into as many code files as we want, but these variables will only be instantiated once and shared across all code files.
        => This method does retain the downside of requiring every file that includes the constants header be recompiled if any constant value is changed.


*/


int main()
{

    return 0;
}