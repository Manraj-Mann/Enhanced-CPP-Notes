#include <iostream>

/*
    Note : Internal Linkage 

    1. “An identifier’s linkage determines whether other declarations of that name refer to the same object or not".
        => Local Variables donot have no linkage.

    2. Global variable and functions identifiers can have either i. internal linkage or ii. external linkage.

    3. An identifier with internal linkage can be seen and used within a single translation unit, but it is not accessible from other translation units. This means that if two source files have identically named identifiers with internal linkage, those identifiers will be treated as independent (and do not result in an ODR violation for having duplicate definitions)

    Key Insight : Identifiers with internal linkage may not be visible to the linker at all. Alternatively, they may visible to the linker, but marked for use in a specific translation unit only.
    when it says 'that is, it is not exposed to the linker' it mean when a variable or a function has internal linkage , they are invisible to the linker in terms of resolving references between different translation units

    4. Global variables with internal linkage

    => Global variables with internal linkage are sometimes called internal variables. To make a non-constant global variable internal, we use the static keyword.

    static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword

    const int g_y{ 1 }; // const globals have internal linkage by default
    constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default

    Const and constexpr global variables have internal linkage by default (and thus don’t need the static keyword -- if it is used, it will be ignored).

    5. The use of the static keyword above is an example of a "storage class specifier", which sets both the "name’s linkage" and its "storage duration". 
       The most commonly used storage class specifiers are static, extern, and mutable. The term storage class specifier is mostly used in technical documentations.

    6,  function identifiers also have linkage. Functions default to external linkage (which we’ll cover in the next lesson), but can be set to internal linkage via the static keyword.

    7. ODR rule - However, it’s worth noting that internal objects (and functions) that are defined in different files are considered to be independent entities (even if their names and types are identical), so there is no violation of the one-definition rule. Each internal object only has one definition.

    8. static vs unnamed namespaces

        In modern C++, use of the static keyword for giving identifiers internal linkage is falling out of favor. Unnamed namespaces can give internal linkage to a wider range of identifiers (e.g. type identifiers), and they are better suited for giving many identifiers internal linkage.

*/

static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword

const int g_y{ 1 }; // const globals have internal linkage by default
constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default

int main()
{

    return 0;
}