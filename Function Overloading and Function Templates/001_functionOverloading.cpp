#include <iostream>

/*

    Notes : 

    1. Function overloading allows us to create multiple functions with the same name, so long as each identically named function has different parameter types (or the functions can be otherwise differentiated). Each function sharing a name (in the same scope) is called an overloaded function (sometimes called an overload for short).

        int add(int x, int y) // integer version
        {
            return x + y;
        }

        double add(double x, double y) // floating point version
        {
            return x + y;
        }

        Functions can be overloaded so long as each overloaded function can be differentiated by the compiler. If an overloaded function can not be differentiated, a compile error will result.

    2. Introduction to overload resolution - When a function call is made to a function that has been overloaded, the compiler will try to match the function call to the appropriate overload based on the arguments used in the function call. This is called overload resolution.

    3. Making it compile - In order for a program using overloaded functions to compile, two things have to be true:

        - Each overloaded function has to be differentiated from the others.
        - Each call to an overloaded function has to resolve to an overloaded function.

    4. 


*/

int add(int x, int y) // integer version
{
    return x + y;
}

double add(double x, double y) // floating point version
{
    return x + y;
}

int main()
{
    std::cout << add(1, 2); // calls add(int, int)
    std::cout << '\n';
    std::cout << add(1.2, 3.4); // calls add(double, double)
    std::cout << '\n';

    return 0;
}