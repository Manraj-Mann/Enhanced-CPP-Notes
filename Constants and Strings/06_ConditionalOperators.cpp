#include <iostream>


/*

Notes : 

1. Conditional	?:	c ? x : y	If conditional c is true then evaluate x, otherwise evaluate y

2. The conditional operator evaluates as an expression : 

    Because the operands of the conditional operator are expressions rather than statements, the conditional operator can be used in places where an expression is required.

    CODE :

    constexpr bool inBigClassroom { false };
    constexpr int classSize { inBigClassroom ? 30 : 20 };
    std::cout << "The class size is: " << classSize << '\n';

3. Parenthesizing the conditional operator : 

    Because C++ prioritizes the evaluation of most operators above the evaluation of the conditional operator, it’s quite easy to write expressions using the conditional operator that don’t evaluate as expected.

    int z { 10 - x > y ? x : y };
    std::cout << z;

    => You might expect this to evaluate as 10 - (x > y ? x : y) (which would evaluate to 8) but it actually evaluates as (10 - x) > y ? x : y (which evaluates to 2).

    => Use parenthesis to make expression to be evaluated as compound expression

4. The type of the expressions must match or be convertible:

    To comply with C++’s type checking rules, one of the following must be true:

    1. The type of the second and third operand must match.
    2. The compiler must be able to find a way to convert one or both of the second and third operands to matching types. 
       The conversion rules the compiler uses are fairly complex and may yield surprising results in some cases.

*/

int main()
{
    // Conditional

    constexpr bool inBigClassroom { false };
    constexpr int classSize { inBigClassroom ? 30 : 20 };
    std::cout << "The class size is: " << classSize << '\n';

    // The type of the expressions must match or be convertible

    std::cout << (true ? 1 : 2) << '\n';    // okay: both operands have matching type int

    std::cout << (false ? 1 : 2.2f) << '\n'; // okay: int value 1 converted to double // compiler know implicit cast

    std::cout << (true ? -1 : 2u) << '\n';  // surprising result: -1 converted to unsigned int, result out of range

    constexpr int x{ 5 };
    std::cout << ((x != 5) ? x : "x is 5"); // compile error: compiler can't find common type for constexpr int and C-style string literal
    
    return 0;
}
