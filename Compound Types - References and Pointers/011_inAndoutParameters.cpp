#include <iostream>

/*

    Notes : 

    1.  function and its caller communicate with each other via two mechanisms: parameters and return values. When a function is called, the caller provides arguments, which the function receives via its parameters. These arguments can be passed by value, reference, or address.

    2. In parameters - In most cases, a function parameter is used only to receive an input from the caller. Parameters that are used only for receiving input from the caller are sometimes called in parameters. In-parameters are typically passed by value or by const reference.

    3. Out parameters - A function parameter that is used only for the purpose of returning information back to the caller is called an out parameter. A function argument passed by (non-const) reference (or by address) allows the function to modify the value of an object passed as an argument. This provides a way for a function to return data back to the caller in cases where using a return value is not sufficient for some reason.

    4. Out parameters have an unnatural syntax - Out-parameters, while functional, have a few downsides.

        First, the caller must instantiate (and initialize) objects and pass them as arguments, even if it doesn’t intend to use them. These objects must be able to be assigned to, which means they can’t be made const.

        Second, because the caller must pass in objects, these values can’t be used as temporaries, or easily used in a single expression.
        
        int getByValue()
        {
            return 5;
        }

        void getByReference(int& x)
        {
            x = 5;
        }

        int main()
        {
            // return by value
            [[maybe_unused]] int x{ getByValue() }; // can use to initialize object
            std::cout << getByValue() << '\n';      // can use temporary return value in expression

            // return by out parameter
            int y{};                // must first allocate an assignable object
            getByReference(y);      // then pass to function to assign the desired value
            std::cout << y << '\n'; // and only then can we use that value

            return 0;
        }

    5. Out-parameters by reference don’t make it obvious the arguments will be modified - Using pass by address instead of pass by reference can in some case help make out-parameters more obvious by requiring the caller to pass in the address of objects as arguments.

        void foo1(int x);  // pass by value
        void foo2(int& x); // pass by reference
        void foo3(int* x); // pass by address

        In rare cases, a function will actually use the value of an out-parameter before overwriting its value. Such a parameter is called an in-out parameter. In-out-parameters work identically to out-parameters and have all the same challenges.

    6. When to pass by non-const reference - If you’re going to pass by reference in order to avoid making a copy of the argument, you should almost always pass by const reference.


*/

int getByValue()
{
    return 5;
}

void getByReference(int& x)
{
    x = 5;
}

int main()
{
    // return by value
    [[maybe_unused]] int x{ getByValue() }; // can use to initialize object
    std::cout << getByValue() << '\n';      // can use temporary return value in expression

    // return by out parameter
    int y{};                // must first allocate an assignable object
    getByReference(y);      // then pass to function to assign the desired value
    std::cout << y << '\n'; // and only then can we use that value

    return 0;
}