#include <iostream>
/* 
    Notes :  
    
    1. C++ also supports operator overloading, which lets us define overloads of existing operators, so that we can make those operators work with our program-defined data types.

    2. Basic operator overloading is fairly straightforward:

        - Define a function using the name of the operator as the function’s name.
        - Add a parameter of the appropriate type for each operand (in left-to-right order). One of these parameters must be a user-defined type (a class type or an enumerated type), otherwise the compiler will error.
        - Set the return type to whatever type makes sense.
        - Use a return statement to return the result of the operation.

    3. When the compiler encounters the use of an operator in an expression and one or more of the operands is a user-defined type, the compiler will check to see if there is an overloaded operator function that it can use to resolve that call. For example, given some expression x + y, the compiler will use function overload resolution to see if there is an operator+(x, y) function call that it can use to evaluate the operation. If a non-ambiguous operator+ function can be found, it will be called, and the result of the operation returned as the return value.


    4. When this expression is evaluated, the compiler will look for an overloaded operator<< function that can handle arguments of type std::ostream and int. It will find such a function (also defined as part of the standard I/O library) and call it. Inside that function, std::cout is used to output x to the console (exactly how is implementation-defined). Finally, the operator<< function returns its left-operand (which in this case is std::cout), so that subsequent calls to operator<< can be chained.


        // Teach operator<< how to print a Color
        // std::ostream is the type of std::cout, std::cerr, etc...
        // The return type and parameter type are references (to prevent copies from being made)
        std::ostream& operator<<(std::ostream& out, Color color)
        {
            out << getColorName(color); // print our color's name to whatever output stream out
            return out;                 // operator<< conventionally returns its left operand

            // The above can be condensed to the following single line:
            // return out << getColorName(color)
        }

    Let’s unpack our overloaded operator function a bit. First, the name of the function is operator<<, since that is the name of the operator we’re overloading. operator<< has two parameters. The left parameter is our output stream, which has type std::ostream. We use pass by non-const reference here because we don’t want to make a copy of a std::ostream object when the function is called, but the std::ostream object needs to be modified in order to do output. The right parameter is our Color object. Since operator<< conventionally returns its left operand, the return type matches the type of the left-operand, which is std::ostream&.

    5. Overloading operator>> to input an enumerator - 

        // pet is an in/out parameter
        std::istream& operator>>(std::istream& in, Pet& pet)
        {
            std::string s{};
            in >> s; // get input string from user

            std::optional<Pet> match { getPetFromString(s) };
            if (match) // if we found a match
            {
                pet = *match; // dereference std::optional to get matching enumerator
                return in;
            }

            // We didn't find a match, so input must have been invalid
            // so we will set input stream to fail state
            in.setstate(std::ios_base::failbit);

            // On an extraction failure, operator>> zero-initializes fundamental types
            // Uncomment the following line to make this operator do the same thing
            // pet = {};

            return in;
        }


*/

#include <string_view>
#include <optional>
#include <limits>

enum Color
{
	black,
	red,
	blue,
};

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

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

constexpr std::optional<Pet> getPetFromString(std::string_view sv)
{
    if (sv == "cat")   return cat;
    if (sv == "dog")   return dog;
    if (sv == "pig")   return pig;
    if (sv == "whale") return whale;

    return {};
}

std::ostream& operator<<(std::ostream &out , Color color)
{
    out<<getColorName(color);
    return out;
}


// pet is an in/out parameter
std::istream& operator>>(std::istream& in, Pet& pet)
{
    std::string s{};
    in >> s; // get input string from user

    std::optional<Pet> match { getPetFromString(s) };
    if (match) // if we found a match
    {
        pet = *match; // dereference std::optional to get matching enumerator
        return in;
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // On an extraction failure, operator>> zero-initializes fundamental types
    // Uncomment the following line to make this operator do the same thing
    pet = {};

    return in;
}


int main()
{
	Color shirt{ blue };
	std::cout << "Your shirt is " << shirt << '\n'; // it works!

    std::cout << "Enter a pet: cat, dog, pig, or whale: ";
    Pet pet{};
    std::cin >> pet;

    if (std::cin) // if we found a match
        std::cout << "You chose: " << getPetName(pet) << '\n';
    else
    {
        std::cin.clear(); // reset the input stream to good
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Your pet was not valid\n";
    }

	return 0;
}
