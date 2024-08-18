#include <iostream>

/*
    Note : Internal Linkage 

    1. “An identifier’s linkage determines whether other declarations of that name refer to the same object or not".

    2. Global variable and functions identifiers can have either internal linkage or external linkage.

    3. An identifier with internal linkage can be seen and used within a single translation unit, but it is not accessible from other translation units. This means that if two source files have identically named identifiers with internal linkage, those identifiers will be treated as independent (and do not result in an ODR violation for having duplicate definitions)

    Key Insight : Identifiers with internal linkage may not be visible to the linker at all. Alternatively, they may visible to the linker, but marked for use in a specific translation unit only.

    4. Global variables with internal linkage

    => Global variables with internal linkage are sometimes called internal variables. To make a non-constant global variable internal, we use the static keyword.



*/

static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword

const int g_y{ 1 }; // const globals have internal linkage by default
constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default

int main()
{

    return 0;
}