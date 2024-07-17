#include <iostream>


/* Notes : 

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Normal variables : 

// Non-const variables:
int a { 5 };                 // 5 is a constant expression
double b { 1.2 + 3.4 };      // 1.2 + 3.4 is a constant expression
    
These values can be calculated at the compile time so to mark them so we can use const.

+> constants = 1. compile time , 2. Run time 

1. compile time : value must be determined at compiler time

// Const integral variables with a constant expression initializer
// are compile-time constants:
const int c { 5 };           // 5 is a constant expression
const int d { c };           // c is a constant expression
const long e { c + 2 };      // c + 2 is a constant expression

2. runtime : value is constant at runtime , means it will be calculated after some of the operartions.

// Other const variables are runtime constants:
const int f { a };           // a is not a constant expression
const int g { a + 1 };       // a + 1 is not a constant expression
const long h { a + c };      // a + c is not a constant expression
const int i { getNumber() }; // getNumber() is not a constant expression

why important to mark constants ?

=> Constant expressions are always eligible for compile-time evaluation, meaning they are more likely to be optimized at compile-time. This produces faster and smaller code.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1. Const is used to mark variable as not modifiable constant

const int x { 3 + 4 }; // constant expression 3 + 4 must be evaluated at compile-time
int y { 3 + 4 };       // constant expression 3 + 4 may be evaluated at compile-time or runtime

2. Partial optimization of constant subexpressions example std::cout << 3 + 4 << '\n'; 

3. Optimization of non-constant expressions : 

    int x { 7 };            // x is non-const
    std::cout << x << '\n'; // x is a non-constant subexpression
    
    Even though x is non-const, a smart compiler might realize that x will always evaluate to 7 in this particular program, and under the as-if rule, optimize the program to this:
    
    int x { 7 };
    std::cout << 7 << '\n';
    
    When a variable is removed from a program, we say the variable has been optimized out (or optimized away).

4. Ranking variables by the likelihood of the compiler being able to optimize them:

    1.Compile-time constant variables (always eligible to be optimized)
    2.Runtime constant variables
    3.Non-const variables (likely optimized in simple cases only)

5. As if Rule : The rule says compiler can optimize however it likes as long as the observeable behaviour of code doesn't change.

=> One kind of expression that can always be evaluated at compile time is called a “constant expression”

6. A constant expression is an expression that contains only compile-time constants and operators/functions that support compile-time evaluation.

7. A compile-time constant is a constant whose value must be known at compile time. This includes:
    1. Literals (e.g. ‘5’, ‘1.2’)
    2. Constexpr variables (we discuss these shortly in lesson 5.5 -- Constexpr variables)
    3. Const integral variables with a constant expression initializer (e.g. const int x { 5 };). This is a historical exception -- in modern C++, constexpr variables are preferred.
    4. Non-type template parameters (see 11.10 -- Non-type template parameters). Enumerators (see 13.2 -- Unscoped enumerations).

8. The most common type of operators and functions that support compile-time evaluation include:

    1. Arithmetic operators with operands that are compile-time constants (e.g. 1 + 2)
    2. Constexpr and consteval functions (we’ll discuss these later in the chapter)

*/

int getNumber()
{
    std::cout << "Enter a number: ";
    int y{};
    std::cin >> y;

    return y;
}

int main()
{
    // Non-const variables:
    int a { 5 };                 // 5 is a constant expression
    double b { 1.2 + 3.4 };      // 1.2 + 3.4 is a constant expression

    // Const integral variables with a constant expression initializer
    // are compile-time constants:
    const int c { 5 };           // 5 is a constant expression
    const int d { c };           // c is a constant expression
    const long e { c + 2 };      // c + 2 is a constant expression

    // Other const variables are runtime constants:
    const int f { a };           // a is not a constant expression
    const int g { a + 1 };       // a + 1 is not a constant expression
    const long h { a + c };      // a + c is not a constant expression
    const int i { getNumber() }; // getNumber() is not a constant expression

    const double j { b };        // b is not a constant expression
    const double k { 1.2 };      // 1.2 is a constant expression

    return 0;
}
