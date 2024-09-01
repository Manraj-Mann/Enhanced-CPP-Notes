#include <iostream>

/*
    Notes : 

    1. A default argument is a default value provided for a function parameter. 

        void print(int x, int y=10) // 10 is the default argument
        {
            std::cout << "x: " << x << '\n';
            std::cout << "y: " << y << '\n';
        }

    2. Default arguments are inserted by the compiler at site of the function call.

    3. When to use default arguments - Default arguments are an excellent option when a function needs a value that has a reasonable default value, but for which you want to let the caller override if they wish.

    For example, here are a couple of function prototypes for which default arguments might be commonly used:

        int rollDie(int sides=6);
        void openLogFile(std::string filename="default.log");

    Because the user can choose whether to supply a specific argument value or use the default value, a parameter with a default value provided is sometimes called an optional parameter. However, the term optional parameter is also used to refer to several other types of parameters (including parameters passed by address, and parameters using std::optional), so we recommend avoiding this term.

    4. Multiple default arguments - 

        void print(int x=10, int y=20, int z=30)
        {
            std::cout << "Values: " << x << " " << y << " " << z << '\n';
        }

        print(1, 2, 3); // all explicit arguments
        print(1, 2); // rightmost argument defaulted
        print(1); // two rightmost arguments defaulted
        print(); // all arguments defaulted

        If a parameter is given a default argument, all subsequent parameters (to the right) must also be given default arguments.

    5. Default arguments can not be redeclared, and must be declared before use - 

        Once declared, a default argument can not be redeclared in the same translation unit. That means for a function with a forward declaration and a function definition, the default argument can be declared in either the forward declaration or the function definition, but not both.

            void print(int x, int y=4); // forward declaration

            void print(int x, int y=4) // compile error: redefinition of default argument
            {
                std::cout << "x: " << x << '\n';
                std::cout << "y: " << y << '\n';
            }

        The default argument must also be declared in the translation unit before it can be used:

            void print(int x, int y); // forward declaration, no default argument

            void print(int x, int y=4)
            {
                std::cout << "x: " << x << '\n';
                std::cout << "y: " << y << '\n';
            }

        The best practice is to declare the default argument in the forward declaration and not in the function definition, as the forward declaration is more likely to be seen by other files and included before use (particularly if it’s in a header file).

    6. Default arguments and function overloading - 

        Functions with default arguments may be overloaded. For example, the following is allowed: 

        void print(std::string_view s)
        {
            std::cout << s << '\n';
        }

        void print(char c = ' ')
        {
            std::cout << c << '\n';
        }

    7. Default arguments don’t work for functions called through function pointers 

*/

void print(int x, int y=10) // 10 is the default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

void print(int x=10, int y=20, int z=30)
{
    std::cout << "Values: " << x << " " << y << " " << z << '\n';
}

int main()
{
    // print(1, 2, 3); // all explicit arguments
    // print(1, 2); // rightmost argument defaulted
    // print(1); // two rightmost arguments defaulted
    // print(); // all arguments defaulted

    return 0;
}