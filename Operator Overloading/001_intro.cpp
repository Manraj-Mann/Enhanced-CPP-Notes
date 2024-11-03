#include <iostream>
/* 
    Notes :  
    
    1. In C++, operators are implemented as functions. By using function overloading on the operator functions, you can define your own versions of the operators that work with different data types (including classes that you’ve written). Using function overloading to overload operators is called operator overloading.

    2. Operators as functions - The compiler comes with a built-in version of the plus operator (+) for integer operands -- this function adds integers x and y together and returns an integer result. When you see the expression x + y, you can translate this in your head to the function call operator+(x, y) (where operator+ is the name of the function).

    3. Resolving overloaded operators - When evaluating an expression containing an operator, the compiler uses the following rules:

        3.1. If all of the operands are fundamental data types, the compiler will call a built-in routine if one exists. If one does not exist, the compiler will produce a compiler error.

        4.2. If any of the operands are program-defined types (e.g. one of your classes, or an enum type), the compiler will use the function overload resolution algorithm (described in lesson 11.3 -- Function overload resolution and ambiguous matches) to see if it can find an overloaded operator that is an unambiguous best match. This may involve implicitly converting one or more operands to match the parameter types of an overloaded operator. It may also involve implicitly converting program-defined types into fundamental types (via an overloaded typecast, which we’ll cover later in this chapter) so that it can match a built-in operator. If no match can be found (or an ambiguous match is found), the compiler will error.
    
    4. What are the limitations on operator overloading? 

        - An overloaded operator should operate on at least one program-defined type (either as a parameter of the function, or the implicit object).

        - When overloading operators, it’s best to keep the function of the operators as close to the original intent of the operators as possible.

        - If the meaning of an overloaded operator is not clear and intuitive, use a named function instead.

        - Operators that do not modify their operands (e.g. arithmetic operators) should generally return results by value. Operators that modify their leftmost operand (e.g. pre-increment, any of the assignment operators) should generally return the leftmost operand by reference.

*/
int main()
{
    return 0;
}