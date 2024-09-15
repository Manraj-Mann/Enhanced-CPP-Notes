#include <iostream>
/* 
    Notes :  
    
    1. An enumeration (also called an enumerated type or an enum) is a compound data type whose values are restricted to a set of named symbolic constants (called enumerators).

    2. C++ supports two kinds of enumerations: unscoped enumerations (which we’ll cover now) and scoped enumerations (which we’ll cover later in this chapter).

    3. Unscoped enumerations - Unscoped enumerations are defined via the enum keyword.

        // Define a new unscoped enumeration named Color
        enum Color
        {
            // Here are the enumerators
            // These symbolic constants define all the possible values this type can hold
            // Each enumerator is separated by a comma, not a semicolon
            red,
            green,
            blue, // trailing comma optional but recommended
        }; 

        // Define a few variables of enumerated type Color
        Color apple { red };   // my apple is red
        Color shirt { green }; // my shirt is green
        Color cup { blue };    // my cup is blue

        Color socks { white }; // error: white is not an enumerator of Color
        Color hat { 2 };       // error: 2 is not an enumerator of Color


    4. Name your enumerated types starting with a capital letter. Name your enumerators starting with a lower case letter.

    5. Enumerated types are distinct types - Each enumerated type you create is considered to be a distinct type, meaning the compiler can distinguish it from other types (unlike typedefs or type aliases, which are considered non-distinct from the types they are aliasing).

        enum Pet
        {
            cat,
            dog,
            pig,
            whale,
        };

        enum Color
        {
            black,
            red,
            blue,
        };

        int main()
        {
            Pet myPet { black }; // compile error: black is not an enumerator of Pet
            Color shirt { pig }; // compile error: pig is not an enumerator of Color

            return 0;
        }

    6. Putting enumerations to use - 

        - Sometimes functions will return a status code to the caller to indicate whether the function executed successfully or encountered an error. Traditionally, small negative numbers were used to represent different possible error codes. 

        - Then the caller can test the function’s return value against the appropriate enumerator, which is easier to understand than testing the return result for a specific integer value.

        - Because enumerations are small and inexpensive to copy, it is fine to pass (and return) them by value.

    7. The scope of unscoped enumerations - 

        - Unscoped enumerations are named such because they put their enumerator names into the same scope as the enumeration definition itself (as opposed to creating a new scope region like a namespace does).

            enum Color
            {
                red,
                green,
                blue, // blue is put into the global namespace
            };

            enum Feeling
            {
                happy,
                tired,
                blue, // error: naming collision with the above blue
            };

            int main()
            {
                Color apple { red }; // my apple is red
                Feeling me { happy }; // I'm happy right now (even though my program doesn't compile)

                return 0;
            }

        - The Color enumeration is defined in the global scope. Therefore, all the enumeration names (red, green, and blue) also go into the global scope. This pollutes the global scope and significantly raises the chance of naming collisions.

    8. Avoiding enumerator naming collisions - There are quite a few common ways to prevent unscoped enumerator naming collisions.

        - One option is to prefix each enumerator with the name of the enumeration itself:

            enum Color
            {
                color_red,
                color_blue,
                color_green,
            };

            enum Feeling
            {
                feeling_happy,
                feeling_tired,
                feeling_blue, // no longer has a naming collision with color_blue
            };

        - This still pollutes the namespace but reduces the chance for naming collisions by making the names longer and more unique.

        - A better option is to put the enumerated type inside something that provides a separate scope region, such as a namespace:

            namespace Color
            {
                // The names Color, red, blue, and green are defined inside namespace Color
                enum Color
                {
                    red,
                    green,
                    blue,
                };
            }

            namespace Feeling
            {
                enum Feeling
                {
                    happy,
                    tired,
                    blue, // Feeling::blue doesn't collide with Color::blue
                };
            }

    9. Comparing against enumerators - We can use the equality operators (operator== and operator!=) to test whether an enumeration has the value of a particular enumerator or not.

*/

enum Color
{
    // Here are the enumerators
    // These symbolic constants define all the possible values this type can hold
    // Each enumerator is separated by a comma, not a semicolon
    red,
    green,
    blue, // trailing comma optional but recommended
}; 


int main()
{
    // Define a few variables of enumerated type Color
    Color apple { red };   // my apple is red
    Color shirt { green }; // my shirt is green
    Color cup { blue };    // my cup is blue

    // Color socks { white }; // error: white is not an enumerator of Color
    // Color hat { 2 };       // error: 2 is not an enumerator of Color
    return 0;
}