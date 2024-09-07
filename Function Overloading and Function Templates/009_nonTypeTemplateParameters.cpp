#include <iostream>


/*
    Notes : 

    1. A non-type template parameter is a template parameter with a fixed type that serves as a placeholder for a constexpr value passed in as a template argument.

        A non-type template parameter can be any of the following types:

        -> An integral type
        -> An enumeration type
        -> std::nullptr_t
        -> A floating point type (since C++20)
        -> A pointer or reference to an object
        -> A pointer or reference to a function
        -> A pointer or reference to a member function
        -> A literal class type (since C++20)

    2. We saw our first example of a non-type template parameter when we discussed std::bitset.

        std::bitset<8> bits{ 0b0000'0101 }; // The <8> is a non-type template parameter

    3. Defining our own non-type template parameters - Here’s a simple example of a function that uses an int non-type template parameter: 

        template <int N> // declare a non-type template parameter of type int named N
        void print()
        {
            std::cout << N << '\n'; // use value of N here
        }

    4. What are non-type template parameters useful for? 

        As of C++20, function parameters cannot be constexpr. This is true for normal functions, constexpr functions (which makes sense, as they must be able to be run at runtime), and perhaps surprisingly, even consteval functions.

        Non-type template parameters are used primarily when we need to pass constexpr values to functions (or class types) so they can be used in contexts that require a constant expression.

        Having to use non-type template parameters to circumvent the restriction that function parameters can’t be constexpr isn’t great. There are quite a few different proposals being evaluated to help address situations like this. I expect that we might see a better solution to this in a future C++ language standard.

    5. Type deduction for non-type template parameters using auto - 

        As of C++17, non-type template parameters may use auto to have the compiler deduce the non-type template parameter from the template argument:

        template <auto N> // deduce non-type template parameter from template argument
        void print()
        {
            std::cout << N << '\n';
        }

        int main()
        {
            print<5>();   // N deduced as int `5`
            print<'c'>(); // N deduced as char `c`

            return 0;
        }

    6. You may be wondering why this example doesn’t produce an ambiguous match like the example in the prior section. The compiler looks for ambiguous matches first, and then instantiates the function template if no ambiguous matches exist. In this case, there is only one function template, so there is no possible ambiguity.

    After instantiating the function template for the above example, the program looks something like this:

        template <auto N>
        void print()
        {
            std::cout << N << '\n';
        }

        template <>
        void print<5>() // note that this is print<5> and not print<int>
        {
            std::cout << 5 << '\n';
        }

        template <>
        void print<'c'>() // note that this is print<`c`> and not print<char>
        {
            std::cout << 'c' << '\n';
        }

        int main()
        {
            print<5>();   // calls print<5>
            print<'c'>(); // calls print<'c'>

            return 0;
        }


*/


template <int N> // declare a non-type template parameter of type int named N
void print()
{
    std::cout << N << '\n'; // use value of N here
}

int main()
{
    print<5>(); // 5 is our non-type template argument

    return 0;
}