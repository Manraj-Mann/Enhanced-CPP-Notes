#include <iostream>

/*
    Notes : 

    1. Lvalue reference to const - By using the const keyword when declaring an lvalue reference, we tell an lvalue reference to treat the object it is referencing as const. Such a reference is called an lvalue reference to a const value (sometimes called a reference to const or a const reference).Lvalue references to const can bind to non-modifiable lvalues:

        const int x { 5 };    // x is a non-modifiable lvalue
        const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    2. Initializing an lvalue reference to const with a modifiable lvalue - Lvalue references to const can also bind to modifiable lvalues. In such a case, the object being referenced is treated as const when accessed through the reference (even though the underlying object is non-const):

        int x { 5 };          // x is a modifiable lvalue
        const int& ref { x }; // okay: we can bind a const reference to a modifiable lvalue

        std::cout << ref << '\n'; // okay: we can access the object through our const reference
        ref = 7;                  // error: we can not modify an object through a const reference

        x = 6;                // okay: x is a modifiable lvalue, we can still modify it through the original identifier

    3. Favor lvalue references to const over lvalue references to non-const unless you need to modify the object being referenced.

    4. Initializing an lvalue reference to const with an rvalue - 

        const int& ref { 5 }; // okay: 5 is an rvalue
        std::cout << ref << '\n'; // prints 5

        When this happens, a temporary object is created and initialized with the rvalue, and the reference to const is bound to that temporary object.

    5. Initializing an lvalue reference to const with a value of a different type - Lvalue references to const can even bind to values of a different type, so long as those values can be implicitly converted to the reference type:

        // case 1
        const double& r1 { 5 };  // temporary double initialized with value 5, r1 binds to temporary

        std::cout << r1 << '\n'; // prints 5

        // case 2
        char c { 'a' };
        const int& r2 { c };     // temporary int initialized with value 'a', r2 binds to temporary

        std::cout << r2 << '\n'; // prints 97 (since r2 is a reference to int)

    => If you try to bind a const lvalue reference to a value of a different type, the compiler will create a temporary object of the same type as the reference, initialize it using the value, and then bind the reference to the temporary.

    6. Const references bound to temporary objects extend the lifetime of the temporary object - 

        - Temporary objects are normally destroyed at the end of the expression in which they are created.
        - To avoid dangling references , C++ has a special rule: When a const lvalue reference is directly bound to a temporary object, the lifetime of the temporary object is extended to match the lifetime of the reference.

    7. Key insight : 

        - Lvalue references can only bind to modifiable lvalues.
        - Lvalue references to const can bind to modifiable lvalues, non-modifiable lvalues, and rvalues. This makes them a much more flexible type of reference.

    8. Lifetime extension only works when a const reference is directly bound to a temporary. Temporaries returned from a function (even ones returned by const reference) are not eligible for lifetime extension.

    9. Constexpr lvalue references - When applied to a reference, constexpr allows the reference to be used in a constant expression. Constexpr references have a particular limitation: they can only be bound to objects with static duration (either globals or static locals). This is because the compiler knows where static objects will be instantiated in memory, so it can treat that address as a compile-time constant.

    A constexpr reference cannot bind to a (non-static) local variable. This is because the address of local variables is not known until the function they are defined within is actually called.

    int g_x { 5 };

    int main()
    {
        [[maybe_unused]] constexpr int& ref1 { g_x }; // ok, can bind to global

        static int s_x { 6 };
        [[maybe_unused]] constexpr int& ref2 { s_x }; // ok, can bind to static local

        int x { 6 };
        [[maybe_unused]] constexpr int& ref3 { x }; // compile error: can't bind to non-static object

        return 0;
    }

*/

int g_x { 5 };


int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    std::cout << ref << '\n'; // okay: we can access the const object
    // ref = 6;                  // error: we can not modify an object through a const reference

    // case 1
    const double& r1 { 5 };  // temporary double initialized with value 5, r1 binds to temporary

    std::cout << r1 << '\n'; // prints 5

    // case 2
    char c { 'a' };
    const int& r2 { c };     // temporary int initialized with value 'a', r2 binds to temporary

    std::cout << r2 << '\n'; // prints 97 (since r2 is a reference to int)



    [[maybe_unused]] constexpr int& ref1 { g_x }; // ok, can bind to global

    static int s_x { 6 };
    [[maybe_unused]] constexpr int& ref2 { s_x }; // ok, can bind to static local

    // int x { 6 };
    // [[maybe_unused]] constexpr int& ref3 { x }; // compile error: can't bind to non-static object

    return 0;
}