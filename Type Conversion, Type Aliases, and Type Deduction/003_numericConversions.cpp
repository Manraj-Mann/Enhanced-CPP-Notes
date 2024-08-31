#include <iostream>

/*

    Note : 

    1. C++ supports another category of numeric type conversions, called numeric conversions. These numeric conversions cover additional type conversions between fundamental types.

    2. There are five basic types of numeric conversions.

        2.1. Converting an integral type to any other integral type (excluding integral promotions):

            - short s = 3; // convert int to short
            - long l = 3; // convert int to long
            - char ch = s; // convert short to char
            - unsigned int u = 3; // convert int to unsigned int

        2.2. Converting a floating point type to any other floating point type (excluding floating point promotions):
        
            - float f = 3.0; // convert double to float
            - long double ld = 3.0; // convert double to long double
        
        2.3. Converting a floating point type to any integral type:

            - int i = 3.5; // convert double to int

        2.4. Converting an integral type to any floating point type:
        
            - double d = 3; // convert int to double

        2.5. Converting an integral type or a floating point type to a bool:
            
            - bool b1 = 3; // convert int to bool
            - bool b2 = 3.0; // convert double to bool

    3. Unlike numeric promotions (which are always value-preserving and thus “safe”), many numeric conversions are unsafe. An unsafe conversion is one where at least one value of the source type cannot be converted into an equal value of the destination type.

    4. Numeric conversions fall into three general safety categories: 

        4.1. "Value-preserving conversions" are safe numeric conversions where the destination type can exactly represent all possible values in the source type. A value converted using a value-preserving conversion can always be converted back to the source type, resulting in a value that is equivalent to the original value.

        4.2. "Reinterpretive conversions" are unsafe numeric conversions where the converted value may be different than the source value, but no data is lost. Signed/unsigned conversions fall into this category. Values converted using a reinterpretive conversion can be converted back to the source type, resulting in a value equivalent to the original value (even if the initial conversion produced a value out of range of the source type). As such, reinterpretive conversions do not lose data during the conversion process.

        4.3. "Lossy conversions" are unsafe numeric conversions where data may be lost during the conversion. For example, double to int is a conversion that may result in data loss. Unsafe conversions should be avoided as much as possible. However, this is not always possible. 




*/

int main()
{

    return 0;
}