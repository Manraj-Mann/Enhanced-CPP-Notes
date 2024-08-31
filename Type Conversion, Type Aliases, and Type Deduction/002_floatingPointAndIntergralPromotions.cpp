#include <iostream>

/*
    Note: 

    1. Because C++ is designed to be portable and performant across a wide range of architectures, the language designers did not want to assume a given CPU would be able to efficiently manipulate values that were narrower than the natural data size for that CPU.

    2. To help address this challenge, C++ defines a category of type conversions informally called the numeric promotions. A numeric promotion is the type conversion of certain narrower numeric types (such as a char) to certain wider numeric types (typically int or double) that can be processed efficiently.

    3. All numeric promotions are value-preserving. A value-preserving conversion (also called a safe conversion) is one where every possible source value can be converted into an equal value of the destination type.

    4. Numeric promotion categories - 

        => The numeric promotion rules are divided into two subcategories: integral promotions and floating point promotions. Only the conversions listed in these categories are considered to be numeric promotions.

    5. Floating point promotions - Using the floating point promotion rules, a value of type float can be converted to a value of type double.

    6. Integral promotions - 

    Using the integral promotion rules, the following conversions can be made:

    - signed char or signed short can be converted to int.
    - unsigned char, char8_t, and unsigned short can be converted to int if int can hold the entire range of the type, or unsigned int otherwise.
    - If char is signed by default, it follows the signed char conversion rules above. If it is unsigned by default, it follows the unsigned char conversion rules above.
    - bool can be converted to int, with false becoming 0 and true becoming 1.
    
    Assuming an 8 bit byte and an int size of 4 bytes or larger (which is typical these days), the above basically means that bool, char, signed char, unsigned char, signed short, and unsigned short all get promoted to int.



*/

int main()
{

    return 0;
}