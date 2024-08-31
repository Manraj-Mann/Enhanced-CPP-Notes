#include <iostream>

/*

    Notes : 

    1. Narrowing conversions - In C++, a narrowing conversion is a potentially unsafe numeric conversion where the destination type may not be able to hold all the values of the source type. 
    
    2. Make intentional narrowing conversions explicit - If you need to perform a narrowing conversion, use static_cast to convert it into an explicit conversion.

    3. Brace initialization disallows narrowing conversions - Narrowing conversions are disallowed when using brace initialization (which is one of the primary reasons this initialization form is preferred), and attempting to do so will produce a compile error.

    4. Some constexpr conversions aren’t considered narrowing - When the source value of a narrowing conversion isn’t known until runtime, the result of the conversion also can’t be determined until runtime. In such cases, whether the narrowing conversion preserves the value or not also can’t be determined until runtime.

        void print(unsigned int u) // note: unsigned
        {
            std::cout << u << '\n';
        }

        int main()
        {
            std::cout << "Enter an integral value: ";
            int n{};
            std::cin >> n; // enter 5 or -5
            print(n);      // conversion to unsigned may or may not preserve value

            return 0;
        }

        When the source value of a narrowing conversion is constexpr, the specific value to be converted must be known to the compiler. In such cases, the compiler can perform the conversion itself, and then check whether the value was preserved. If the value was not preserved, the compiler can halt compilation with an error. If the value is preserved, the conversion is not considered to be narrowing (and the compiler can replace the entire conversion with the converted result, knowing that doing so is safe).

    5. Conversion from a constexpr floating point type to a narrower floating point type is not considered narrowing even when a loss of precision results.

        - constexpr double d { 0.1 };
        
        - float f { d }; // not narrowing, even though loss of precision results.

    6. List initialization with constexpr initializers - 

        These constexpr exception clauses are incredibly useful when list initializing non-int/non-double objects, as we can use an int or double literal (or a constexpr object) initialization value.

        This allows us to avoid:

        - Having to use literal suffixes in most cases
        - Having to clutter our initializations with a static_cast

        int main()
        {
            // We can avoid literals with suffixes
            unsigned int u { 5 }; // okay (we don't need to use `5u`)
            float f { 1.5 };      // okay (we don't need to use `1.5f`)

            // We can avoid static_casts
            constexpr int n{ 5 };
            double d { n };       // okay (we don't need a static_cast here)
            short s { 5 };        // okay (there is no suffix for short, we don't need a static_cast here)

            return 0;
        }

*/
int main()
{

    return 0;
}