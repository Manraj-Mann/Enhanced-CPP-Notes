#include <iostream>
/* 
    Notes :  
    
    1. Scoped enumerations - Scoped enumerations work similarly to unscoped enumerations (13.2 -- Unscoped enumerations), but have two primary differences: They won’t implicitly convert to integers, and the enumerators are only placed into the scope region of the enumeration (not into the scope region where the enumeration is defined).

    To make a scoped enumeration, we use the keywords enum class. The rest of the scoped enumeration definition is the same as an unscoped enumeration definition. Here’s an example:

        enum class Color // "enum class" defines this as a scoped enumeration rather than an unscoped enumeration
        {
            red, // red is considered part of Color's scope region
            blue,
        };

        enum class Fruit
        {
            banana, // banana is considered part of Fruit's scope region
            apple,
        };

        Color color { Color::red }; // note: red is not directly accessible, we have to use Color::red
        Fruit fruit { Fruit::banana }; // note: banana is not directly accessible, we have to use Fruit::banana

        if (color == fruit) // compile error: the compiler doesn't know how to compare different types Color and Fruit

    2. The class keyword (along with the static keyword), is one of the most overloaded keywords in the C++ language, and can have different meanings depending on context. Although scoped enumerations use the class keyword, they aren’t considered to be a “class type” (which is reserved for structs, classes, and unions).

    enum struct also works in this context, and behaves identically to enum class. However, use of enum struct is non-idiomatic, so avoid its use.

    3. Scoped enumerations define their own scope regions - 

        Unlike unscoped enumerations, which place their enumerators in the same scope as the enumeration itself, scoped enumerations place their enumerators only in the scope region of the enumeration. In other words, scoped enumerations act like a namespace for their enumerators. This built-in namespacing helps reduce global namespace pollution and the potential for name conflicts when scoped enumerations are used in the global scope.


    4. Because scoped enumerations offer their own implicit namespacing for enumerators, there’s no need to put scoped enumerations inside another scope region (such as a namespace), unless there’s some other compelling reason to do so, as it would be redundant.

    5. Scoped enumerations don’t implicitly convert to integers - 

        There are occasionally cases where it is useful to be able to treat a scoped enumerator as an integral value. In these cases, you can explicitly convert a scoped enumerator to an integer by using a static_cast. A better choice in C++23 is to use std::to_underlying() (defined in the <utility> header), which converts an enumerator to a value of the underlying type of the enumeration.

        std::cout << static_cast<int>(color) << '\n';   // explicit conversion to int, will print 1
        std::cout << std::to_underlying(color) << '\n'; // convert to underlying type, will print 1 (C++23)

    6. Easing the conversion of scoped enumerators to integers (advanced)  - 

        Scoped enumerations are great, but the lack of implicit conversion to integers can sometimes be a pain point. If we need to convert a scoped enumeration to integers often (e.g. cases where we want to use scoped enumerators as array indices), having to use static_cast every time we want a conversion can clutter our code significantly.

        If you find yourself in the situation where it would be useful to make conversion of scoped enumerators to integers easier, a useful hack is to overload the unary operator+ to perform this conversion:

            enum class Animals
            {
                chicken, // 0
                dog, // 1
                cat, // 2
                elephant, // 3
                duck, // 4
                snake, // 5

                maxAnimals,
            };

            // Overload the unary + operator to convert Animals to the underlying type
            // adapted from https://stackoverflow.com/a/42198760, thanks to Pixelchemist for the idea
            constexpr auto operator+(Animals a) noexcept
            {
                return static_cast<std::underlying_type_t<Animals>>(a);
            }

    7. using enum statements C++20

        Introduced in C++20, a using enum statement imports all of the enumerators from an enum into the current scope. When used with an enum class type, this allows us to access the enum class enumerators without having to prefix each with the name of the enum class.

            enum class Color
            {
                black,
                red,
                blue,
            };

            constexpr std::string_view getColor(Color color)
            {
                using enum Color; // bring all Color enumerators into current scope (C++20)
                // We can now access the enumerators of Color without using a Color:: prefix

                switch (color)
                {
                case black: return "black"; // note: black instead of Color::black
                case red:   return "red";
                case blue:  return "blue";
                default:    return "???";
                }
            }

        


*/

#include <string_view>

enum class Animals
{
    chicken, // 0
    dog, // 1
    cat, // 2
    elephant, // 3
    duck, // 4
    snake, // 5

    maxAnimals,
};

// Overload the unary + operator to convert Animals to the underlying type
// adapted from https://stackoverflow.com/a/42198760, thanks to Pixelchemist for the idea
constexpr auto operator+(Animals a) noexcept
{
    return static_cast<std::underlying_type_t<Animals>>(a);
}

enum class Color
{
    black,
    red,
    blue,
};

constexpr std::string_view getColor(Color color)
{
    using enum Color; // bring all Color enumerators into current scope (C++20)
    // We can now access the enumerators of Color without using a Color:: prefix

    switch (color)
    {
    case black: return "black"; // note: black instead of Color::black
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

int main()
{
    // enum class Color // "enum class" defines this as a scoped enum rather than an unscoped enum
    // {
    //     red, // red is considered part of Color's scope region
    //     blue,
    // };

    // std::cout << red << '\n';        // compile error: red not defined in this scope region
    // std::cout << Color::red << '\n'; // compile error: std::cout doesn't know how to print this (will not implicitly convert to int)

    // Color color { Color::blue }; // okay
    std::cout << +Animals::elephant << '\n'; // convert Animals::elephant to an integer using unary operator+


    Color shirt{ Color::blue };

    std::cout << "Your shirt is " << getColor(shirt) << '\n';


    return 0;
}