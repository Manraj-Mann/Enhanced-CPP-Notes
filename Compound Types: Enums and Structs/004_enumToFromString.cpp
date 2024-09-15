#include <iostream>
/* 
    Notes :  
    
    1. Getting the name of an enumerator - 

        - The typical way to get the name of an enumerator is to write a function that allows us to pass in an enumerator and returns the enumerator’s name as a string. But that requires some way to determine which string should be returned for a given enumerator.

        - There are two common ways to do this : 

            1. A switch statement can switch on either an integral value or an enumerated value. 

                constexpr std::string_view getColorName(Color color)
                {
                    switch (color)
                    {
                    case black: return "black";
                    case red:   return "red";
                    case blue:  return "blue";
                    default:    return "???";
                    }
                }

                constexpr Color shirt{ blue };
                std::cout << "Your shirt is " << getColorName(shirt) << '\n';

                - Each case returns the name of the appropriate color as a C-style string literal. This C-style string literal gets implicitly converted into a std::string_view, which is returned to the caller.

                - Because C-style string literals exist for the entire program, it’s okay to return a std::string_view that is viewing a C-style string literal. When the std::string_view is copied back to the caller, the C-style string literal being viewed will still exist.

            2. The second way to solve the program of mapping enumerators to strings is to use an array. 

    2. Unscoped enumerator input - 

        - One simple way to work around this is to read in an integer, and use static_cast to convert the integer to an enumerator of the appropriate enumerated type:

            Pet pet{ static_cast<Pet>(input) }; // static_cast our integer to a Pet

        - Getting an enumeration from a string 

            constexpr std::optional<Pet> getPetFromString(std::string_view sv)
            {
                if (sv == "cat")   return cat;
                if (sv == "dog")   return dog;
                if (sv == "pig")   return pig;
                if (sv == "whale") return whale;

                return {};
            }

        -    if (!pet)
                std::cout << "You entered an invalid pet\n";
            else
                std::cout << "You entered: " << getPetName(*pet) << '\n';

    3. Note that the above solution only matches lower case letters. If you want to match any letter case, you can use the following function to convert the user’s input to lower case:

        #include <algorithm> // for std::transform
        #include <cctype>    // for std::tolower
        #include <string>
        #include <string_view>

        // This function returns a std::string that is the lower-case version of the std::string_view passed in.
        // Only 1:1 character mapping can be performed by this function
        std::string toASCIILowerCase(std::string_view sv)
        {
            std::string lower{};
            std::transform(sv.begin(), sv.end(), std::back_inserter(lower),
                [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
            return lower;
        }


*/
int main()
{
    return 0;
}