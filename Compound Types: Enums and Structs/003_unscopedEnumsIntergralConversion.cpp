#include <iostream>
#include <cstdint>
/* 
    Notes :  
    
    1. Enumerators are symbolic constants. What we didn’t tell you then is that these enumerators have values that are of an integral type.

    2. A char is really just a 1-byte integral value, and the character 'A' gets converted to an integral value (in this case, 65) and stored.

    3. It is possible to explicitly define the value of enumerators. These integral values can be positive or negative, and can share the same value as other enumerators. Any non-defined enumerators are given a value one greater than the previous enumerator.

        enum Animal
        {
            cat = -3,    // values can be negative
            dog,         // -2
            pig,         // -1
            horse = 5,
            giraffe = 5, // shares same value as horse
            chicken,     // 6
        };

        - Avoid assigning explicit values to your enumerators unless you have a compelling reason to do so.

    4. Make the enumerator representing 0 the one that is the best default meaning for your enumeration. If no good default meaning exists, consider adding an “invalid” or “unknown” enumerator that has value 0, so that state is explicitly documented and can be explicitly handled where appropriate.

    5. Unscoped enumerations will implicitly convert to integral values - Even though enumerations store integral values, they are not considered to be an integral type (they are a compound type). However, an unscoped enumeration will implicitly convert to an integral value. Because enumerators are compile-time constants, this is a constexpr conversion 

            enum Color
            {
                black, // assigned 0
                red, // assigned 1
                blue, // assigned 2
                green, // assigned 3
                white, // assigned 4
                cyan, // assigned 5
                yellow, // assigned 6
                magenta, // assigned 7
            };

            int main()
            {
                Color shirt{ blue };

                std::cout << "Your shirt is " << shirt << '\n'; // what does this do?

                return 0;
            }
            
        - When an enumerated type is used in a function call or with an operator, the compiler will first try to find a function or operator that matches the enumerated type. For example, when the compiler tries to compile std::cout << shirt, the compiler will first look to see if operator<< knows how to print an object of type Color (because shirt is of type Color) to std::cout. It doesn’t.

        - Since the compiler can’t find a match, it will then then check if operator<< knows how to print an object of the integral type that the unscoped enumeration converts to. Since it does, the value in shirt gets converted to an integral value and printed as integral value 2.

    6. Enumeration size and underlying type (base)  - 

        - Enumerators have values that are of an integral type. But what integral type? The specific integral type used to represent the value of enumerators is called the enumeration’s underlying type (or base).

        - For unscoped enumerations, the C++ standard does not specify which specific integral type should be used as the underlying type, so the choice is implementation-defined. Most compilers will use int as the underlying type (meaning an unscoped enum will be the same size as an int), unless a larger type is required to store the enumerator values. But you shouldn’t assume this will hold true for every compiler or platform.

        - It is possible to explicitly specify an underlying type for an enumeration. The underlying type must be an integral type. For example, if you are working in some bandwidth-sensitive context (e.g. sending data over a network) you may want to specify a smaller type for your enumeration: 

            // Use an 8-bit integer as the enum underlying type
            enum Color : std::int8_t
            {
                black,
                red,
                blue,
            };

            int main()
            {
                Color c{ black };
                std::cout << sizeof(c) << '\n'; // prints 1 (byte)

                return 0;
            }

        - Because std::int8_t and std::uint8_t are usually type aliases for char types, using either of these types as the enum base will most likely cause the enumerators to print as char values rather than int values.


    7. Integer to unscoped enumerator conversion - 

        While the compiler will implicitly convert an unscoped enumeration to an integer, it will not implicitly convert an integer to an unscoped enumeration. The following will produce a compiler error:

        enum Pet // no specified base
        {
            cat, // assigned 0
            dog, // assigned 1
            pig, // assigned 2
            whale, // assigned 3
        };

        int main()
        {
            Pet pet { 2 }; // compile error: integer value 2 won't implicitly convert to a Pet
            pet = 3;       // compile error: integer value 3 won't implicitly convert to a Pet

            return 0;
        }

        - There are two ways to work around this.

            1. First, you can explicitly convert an integer to an unscoped enumerator using static_cast:

                Pet pet { static_cast<Pet>(2) }; // convert integer 2 to a Pet
                pet = static_cast<Pet>(3);       // our pig evolved into a whale!

                It is also safe to static_cast any integral value that is in range of the target enumeration’s underlying type, even if there are no enumerators representing that value. Static casting a value outside the range of the underlying type will result in undefined behavior.

            2. Second, as of C++17, if an unscoped enumeration has an explicitly specified base, then the compiler will allow you to list initialize an unscoped enumeration using an integral value:

                Pet pet1 { 2 }; // ok: can brace initialize unscoped enumeration with specified base with integer (C++17)
                Pet pet2 (2);   // compile error: cannot direct initialize with integer
                Pet pet3 = 2;   // compile error: cannot copy initialize with integer

                pet1 = 3;       // compile error: cannot assign with integer

    8.  - If the enumeration has an explicitly defined underlying type, the range of the enumeration is identical to the range of the underlying type.

        - If the enumeration does not have an explicit underlying type, things are a bit more complicated. In this case, the compiler gets to pick the underlying type, and it can pick any signed or unsigned type so long as the value of all enumerators fit in that type. Given this, it is only safe to static_cast integral values that fit in the range of the smallest number of bits that can hold the value of all enumerators.

        - Let’s do two examples to illustrate this:

            1. With enumerators that have values 2, 9, and 12, these enumerators could minimally fit in an unsigned 4-bit integral type with range 0 to 15. Therefore, it is only safe to static_cast integral values 0 through 15 to this enumerated type.
            
            2. With enumerators that have values -28, 2, and 6, these enumerators could minimally fit in a signed 6-bit integral type with range -32 to 31. Therefore, it is only safe to static_cast integral values -32 through 31 to this enumerated type.

    9. Enumerators need not be unique. Since enumerators implicitly convert to integers, and integers can be given to enumerators, enumerators can be initialized with other enumerators (though there is typically little reason to do so!).

        enum Status {
        OK = 0,
        WARNING = 1,
        ERROR = 1,  // ERROR has the same value as WARNING
        CRITICAL = 2
    };

*/

enum types : std::uint8_t
{
    int_i = 0, 
    int_j,
};

enum Animal
{
    cat = -3,    // values can be negative
    dog,         // -2
    pig,         // -1
    horse = 5,
    giraffe = 5, // shares same value as horse
    chicken,     // 6
};

enum Status {
    OK = 0,
    WARNING = 1,
    ERROR = 1,  // ERROR has the same value as WARNING
    CRITICAL = 2
};


int main()
{
    std::cout<<"SIZE OF : "<<sizeof(int)<<std::endl;
    std::cout<<"SIZE OF : "<<sizeof(types)<<std::endl;
    std::cout<<"SIZE OF : "<<sizeof(Animal)<<std::endl;

    return 0;
}