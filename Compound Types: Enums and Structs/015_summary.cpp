#include <iostream>
/* 
    Notes :  
    
    1. A program-defined type (also called a user-defined type) is a custom type that we can create for use in our own programs. The enumerated types and class types (including structs, classes and unions) allow for creation of program-defined types. Program-defined types must be defined before they can be used. The definition of a program-defined type is called a type definition. Type definitions are exempt from the one-definition rule.

    2. An enumeration (also called an enumerated type or an enum) is a compound data type where every possible value is defined as a symbolic constant (called an enumerator). Enumerations are distinct types, meaning the compiler can differentiate them from other types (unlike type aliases).

    3. Unscoped enumerations are named such because they put their enumerator names into the same scope as the enumeration definition itself (as opposed to creating a new scope region like a namespace does). Unscoped enumerations also provide a named scope region for their enumerators. Unscoped enumerations will implicitly convert to integral values.

    4. Scoped enumerations work similarly to unscoped enumerations but won’t implicitly convert to integers, and the enumerators are only placed into the scope region of the enumeration (not into the scope region where the enumeration is defined).

    5. A struct (short for structure) is a program-defined data type that allows us to bundle multiple variables together into a single type. The variables that are part of the struct (or class) are called data members (or member variables). To access a specific member variable, we use the member selection operator (operator.) in between the struct variable name and the member name (for normal structs and references to structs), or the member selection from pointer operator (operator->) (for pointers to structs).

    6. In general programming, an aggregate data type (also called an aggregate) is any type that can contain multiple data members. In C++, arrays and structs with only data members are aggregates.

    7. Aggregates use a form of initialization called aggregate initialization, which allows us to directly initialize the members of aggregates. To do this, we provide an initializer list as an initializer, which is just a list of comma-separated values. Aggregate initialization does a memberwise initialization, which means each member in the struct is initialized in the order of declaration.

    8. In C++20, Designated initializers allow you to explicitly define which initialization values map to which members. The members must be initialized in the order in which they are declared in the struct, otherwise an error will result.

    9. When we define a struct (or class) type, we can provide a default initialization value for each member as part of the type definition. This process is called non-static member initialization, and the initialization value is called a default member initializer.

    10. For performance reasons, the compiler will sometimes add gaps into structures (this is called padding), so the size of a structure may be larger than the sum of the size of its members.

    11. A class template is a template definition for instantiating class types (structs, classes, or unions). Class template argument deduction (CTAD) is a C++17 feature that allows the compiler to deduce the template type arguments from an initializer.

*/
int main()
{
    return 0;
}