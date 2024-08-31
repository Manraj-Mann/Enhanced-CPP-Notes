#include <iostream>

/*

    Notes : 

    1. Type deduction for initialized variables - 

        Type deduction (also sometimes called type inference) is a feature that allows the compiler to deduce the type of an object from the object’s initializer. To use type deduction with variables, the auto keyword is used in place of the variable’s type:

        int main()
        {
            auto d{ 5.0 }; // 5.0 is a double literal, so d will be type double
            auto i{ 1 + 2 }; // 1 + 2 evaluates to an int, so i will be type int
            auto x { i }; // i is an int, so x will be type int too

            return 0;
        }

    2. Type deduction will not work for objects that do not have initializers or have empty initializers. It also will not work when the initializer has type void (or any other incomplete type). Thus, the following is not valid:

        auto x;          // The compiler is unable to deduce the type of x
        auto y{ };       // The compiler is unable to deduce the type of y
        auto z{ foo() }; // z can't have type void, so this is invalid

    3. Type deduction drops const / constexpr qualifiers : 

        In most cases, type deduction will drop the const or constexpr qualifier from deduced types. For example:

        int main()
        {
            const int x { 5 }; // x has type const int
            auto y { x };      // y will be type int (const is dropped)

            return 0;
        }

    4. Type deduction for string literals - 

            using namespace std::literals; // easiest way to access the s and sv suffixes

            auto s1 { "goo"s };  // "goo"s is a std::string literal, so s1 will be deduced as a std::string
            auto s2 { "moo"sv }; // "moo"sv is a std::string_view literal, so s2 will be deduced as a std::string_view

    5. Use type deduction for your variables when the type of the object doesn’t matter.

        Favor an explicit type when you require a specific type that differs from the type of the initializer, or when your object is used in a context where making the type obvious is useful.

*/

int main()
{


    return 0;
}