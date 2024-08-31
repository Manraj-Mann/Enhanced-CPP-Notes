#include <iostream>

/*
    Notes : 

    1. In C++, certain operators require that their operands be of the same type. If one of these operators is invoked with operands of different types, one or both of the operands will be implicitly converted to matching types using a set of rules called the usual arithmetic conversions.

    2. The operators that require operands of the same type - 

        The following operators require their operands to be of the same type:

        - The binary arithmetic operators: +, -, *, /, %
        - The binary relational operators: <, >, <=, >=, ==, !=
        - The binary bitwise arithmetic operators: &, ^, |
        - The conditional operator ?: (excluding the condition, which is expected to be of type bool)

    3. The usual arithmetic conversion rules - 

        The usual arithmetic conversion rules are somewhat complex, so we’ll simplify a bit. The compiler has a ranked list of types that looks something like this:

        - long double (highest rank)
        - double
        - float
        - long long
        - long
        - int (lowest rank)
        
    
    4. The following rules are applied to find a matching type:

        - If one operand is an integral type and the other a floating point type, the integral operand is converted to the type of the floating point operand (no integral promotion takes place).

        - Otherwise, any integral operands are numerically promoted (see 10.2 -- Floating-point and integral promotion).

    
    5. If one operand is signed and the other unsigned, special rules apply (see below)
       
       Otherwise, the operand with lower rank is converted to the type of the operand with higher rank.

    6. Signed and unsigned issues - This prioritization hierarchy and conversion rules can cause some problematic issues when mixing signed and unsigned values. 

    This is one of the primary reasons to avoid unsigned integers -- when you mix them with signed integers in arithmetic expressions, you’re at risk for unexpected results. And the compiler probably won’t even issue a warning.

    std::cout << typeid(5u-10).name() << ' ' << 5u - 10 << '\n'; // 5u means treat 5 as an unsigned integer 

    output : unsigned int 4294967291




*/

int main()
{

    int i{ 2 };
    double d{ 3.5 };
    std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; // show us the type of i + d

    return 0;
}