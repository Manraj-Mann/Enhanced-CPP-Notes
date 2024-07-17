#include <iostream>

/*

Notes : 

1. The compile-time const challenge : 

This method has two challenges.

    1. First, when using const, our integral variables could end up as either a compile-time const or a runtime const, depending on whether the initializer is a constant expression or not. In some cases, this can make it hard to tell whether the const variable is actually a compile-time constant or not.

        For example:

        int a { 5 };       // not const at all
        const int b { a }; // obviously a runtime const (since initializer is non-const)
        const int c { 5 }; // obviously a compile-time const (since initializer is a constant expression)

        const int d { someVar };    // not obvious whether this is a runtime or compile-time const
        const int e { getValue() }; // not obvious whether this is a runtime or compile-time const
    
    2. Second, this use of const to create compile-time constant variables does not extend to non-integral variables. And there are many cases where we would like non-integral variables to be compile-time constants too.

2. The constexpr keyword : help compiler to tell we want a compile time constant here. A constexpr (which is short for “constant expression”) variable is always a compile-time constant. As a result, a constexpr variable must be initialized with a constant expression, otherwise a compilation error will result.
    
    constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    constexpr int myAge { age };      // compile error: age is not a constant expression
    
3. constexpr works for both integral and non-integral types ( like double).

4. const vs constexpr for variables
    
    => For variables, “const” means that the value of an object cannot be changed after initialization. “Constexpr” means that an object must have a value that is known at compile-time.
    => In the future we will discuss some types that are not fully compatible with constexpr (including std::string, std::vector, and other types that use dynamic memory allocation). For constant objects of these types, either use const instead of constexpr, or pick a different type that is constexpr compatible (e.g. std::string_view or std::array).

5. Normal function calls are evaluated at runtime, with the supplied arguments being used to initialize the function’s parameters. Because the initialization of function parameters happens at runtime, this leads to two consequences:

    1. const function parameters are treated as runtime constants (even when the supplied argument is a compile-time constant).
    2. Function parameters cannot be declared as constexpr, since their initialization value isn’t determined until runtime.

*/
int main() 
{
    // const double p {10.0}; error: the value of 'p' is not usable in a constant expression
    constexpr double p{0.01};// works fine since value of p is now known at compile time and gurantted to compiler;
    constexpr double num {p+1};
    
    // success because the intergral type is treated as compile time constant
    const int a{1};
    constexpr int b{a + 11};
    
    return 0;
}
