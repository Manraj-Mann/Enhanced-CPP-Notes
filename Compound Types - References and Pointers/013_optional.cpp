#include <iostream>

/*

    Notes : 

    1. Returning a std::optional - C++17 introduces std::optional, which is a class template type that implements an optional value. That is, a std::optional<T> can either have a value of type T, or not. We can use this to implement the third option above:

    2. Using std::optional is quite easy. We can construct a std::optional<T> either with or without a value:

        std::optional<int> o1 { 5 };            // initialize with a value
        std::optional<int> o2 {};               // initialize with no value
        std::optional<int> o3 { std::nullopt }; // initialize with no value

    3. To see if a std::optional has a value, we can choose one of the following:

        if (o1.has_value()) // call has_value() to check if o1 has a value
        if (o2)             // use implicit conversion to bool to check if o2 has a value

    4. To get the value from a std::optional, we can choose one of the following:

        std::cout << *o1;             // dereference to get value stored in o1 (undefined behavior if o1 does not have a value)
        std::cout << o2.value();      // call value() to get value stored in o2 (throws std::bad_optional_access exception if o2 does not have a value)
        std::cout << o3.value_or(42); // call value_or() to get value stored in o3 (or value `42` if o3 doesn't have a value)

    5. Pros and cons of returning a std::optional

        = Returning a std::optional is nice for a number of reasons:

            - Using std::optional effectively documents that a function may return a value or not.
            - We don’t have to remember which value is being returned as a sentinel.
            - The syntax for using std::optional is convenient and intuitive.
        
        = Returning a std::optional does come with a few downsides:

            - We have to make sure the std::optional contains a value before getting the value. If we dereference a std::optional that does not contain a value, we get undefined behavior.
            - std::optional does not provide a way to pass back information about why the function failed.

    6. Using std::optional as an optional function parameter - 

        void printIDNumber(std::optional<const int> id = std::nullopt)
        {
            if (id)
                std::cout << "Your ID number is " << *id << ".\n";
            else
                std::cout << "Your ID number is not known.\n";
        }

        int main()
        {
            printIDNumber(); // we don't know the user's ID yet

            int userid { 34 };
            printIDNumber(userid); // we know the user's ID now

            printIDNumber(62); // we can also pass an rvalue

            return 0;
        }

        There are two advantages to this approach:

            1. It effectively documents that the parameter is optional.
            
            2. We can pass in an rvalue (since std::optional will make a copy).

        However, because std::optional makes a copy of its argument, this becomes problematic when T is an expensive-to-copy type (like std::string). With normal function parameters, we worked around this by making the parameter a const lvalue reference, so that a copy would not be made. Unfortunately, as of C++23 std::optional does not support references.

    7. Prefer std::optional for optional return types.

        Prefer function overloading for optional function parameters (when possible). Otherwise, use std::optional<T> for optional arguments when T would normally be passed by value. Favor const T* when T is expensive to copy.


*/


// Our function now optionally returns an int value
std::optional<int> doIntDivision(int x, int y)
{
    if (y == 0)
        return {}; // or return std::nullopt
    return x / y;
}

int main()
{
    std::optional<int> result1 { doIntDivision(20, 5) };
    if (result1) // if the function returned a value
        std::cout << "Result 1: " << *result1 << '\n'; // get the value
    else
        std::cout << "Result 1: failed\n";

    std::optional<int> result2 { doIntDivision(5, 0) };

    if (result2)
        std::cout << "Result 2: " << *result2 << '\n';
    else
        std::cout << "Result 2: failed\n";

    return 0;
}