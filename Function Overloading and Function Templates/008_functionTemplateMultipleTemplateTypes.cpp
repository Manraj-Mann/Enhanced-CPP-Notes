#include <iostream>

/*
    Notes : 

    1.  Type conversion is done only when resolving function overloads, not when performing template argument deduction.

        This lack of type conversion is intentional for at least two reasons. First, it helps keep things simple: we either find an exact match between the function call arguments and template type parameters, or we don’t. Second, it allows us to create function templates for cases where we want to ensure that two or more parameters have the same type (as in the example above).

        template <typename T>
        T max(T x, T y)
        {
            return (x < y) ? y : x;
        }

        int main()
        {
            std::cout << max(2, 3.5) << '\n';  // compile error

            return 0;
        }

    2. Fortunately, we can solve this problem in (at least) three ways : 

        2.1. Use static_cast to convert the arguments to matching types - The first solution is to put the burden on the caller to convert the arguments into matching types. For example:

        std::cout << max(static_cast<double>(2), 3.5) << '\n'; // convert our int to a double so we can call max(double, double)

        2.2. Provide an explicit type template argument - If we had written a non-template max(double, double) function, then we would be able to call max(int, double) and let the implicit type conversion rules convert our int argument into a double so the function call could be resolved:

            double max(double x, double y)
            {
                return (x < y) ? y : x;
            }

            std::cout << max(2, 3.5) << '\n'; // the int argument will be converted to a double

            However, when the compiler is doing template argument deduction, it won’t do any type conversions. Fortunately, we don’t have to use template argument deduction if we specify an explicit type template argument to be used instead:

            // we've explicitly specified type double, so the compiler won't use template argument deduction
            std::cout << max<double>(2, 3.5) << '\n';

        2.3. Function templates with multiple template type parameters - The root of our problem is that we’ve only defined the single template type (T) for our function template, and then specified that both parameters must be of this same type. The best way to solve this problem is to rewrite our function template in such a way that our parameters can resolve to different types. Rather than using one template type parameter T, we’ll now use two (T and U):

            template <typename T, typename U> // We're using two template type parameters named T and U
            T max(T x, U y) // x can resolve to type T, and y can resolve to type U
            {
                return (x < y) ? y : x; // uh oh, we have a narrowing conversion problem here
            }

            However, the above code still has a problem: using the usual arithmetic rules (10.5 -- Arithmetic conversions), double takes precedence over int, so our conditional operator will return a double. But our function is defined as returning a T -- in cases where T resolves to an int, our double return value will undergo a narrowing conversion to an int, which will produce a warning (and possible loss of data).

            Making the return type a U instead doesn’t solve the problem, as we can always flip the order of the operands in the function call to flip the types of T and U.

            How do we solve this? This is a good use for an auto return type -- we’ll let the compiler deduce what the return type should be from the return statement:

            template <typename T, typename U>
            auto max(T x, U y)
            {
                return (x < y) ? y : x;
            }

    3. Abbreviated function templates - C++20 introduces a new use of the auto keyword: When the auto keyword is used as a parameter type in a normal function, the compiler will automatically convert the function into a function template with each auto parameter becoming an independent template type parameter. This method for creating a function template is called an abbreviated function template.

        For example:

        auto max(auto x, auto y)
        {
            return (x < y) ? y : x;
        }

        is shorthand in C++20 for the following:

        template <typename T, typename U>
        auto max(T x, U y)
        {
            return (x < y) ? y : x;
        }

        which is the same as the max function template we wrote above.

        Feel free to use abbreviated function templates with a single auto parameter, or where each auto parameter should be an independent type (and your language standard is set to C++20 or newer).

    4. Function templates may be overloaded - 

        Just like functions may be overloaded, function templates may also be overloaded. Such overloads can have a different number of template types and/or a different number or type of function parameters:

        // Add two values with matching types
        template <typename T>
        T add(T x, T y)
        {
            return x + y;
        }

        // Add two values with non-matching types
        // As of C++20 we could also use auto add(auto x, auto y)
        template <typename T, typename U>
        T add(T x, U y)
        {
            return x + y;
        }

        // Add three values with any type
        // As of C++20 we could also use auto add(auto x, auto y, auto z)
        template <typename T, typename U, typename V>
        T add(T x, U y, V z)
        {
            return x + y + z;
        }

        One interesting note here is that for the call to add(1.2, 3.4), the compiler will prefer add<T> over add<T, U> even though both could possibly match.

        The rules for determining which of multiple matching function templates should be preferred are called “partial ordering of function templates”. In short, whichever function template is more restrictive/specialized will be preferred. add<T> is the more restrictive function template in this case (since it only has one template parameter), so it is preferred.

        If multiple function templates can match a call and the compiler can’t determine which is more restrictive, the compiler will error with an ambiguous match.



*/

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

template <typename T>
T add(T x, T y)
{
    return x + y;
}

// Add two values with non-matching types
// As of C++20 we could also use auto add(auto x, auto y)
template <typename T, typename U>
T add(T x, U y)
{
    return x + y;
}

// Add three values with any type
// As of C++20 we could also use auto add(auto x, auto y, auto z)
template <typename T, typename U, typename V>
T add(T x, U y, V z)
{
    return x + y + z;
}

int main()
{   
    std::cout << max(static_cast<double>(2), 3.5) << '\n'; // convert our int to a double so we can call max(double, double)

    std::cout << add(1.2, 3.4) << '\n'; // instantiates and calls add<double>()
    std::cout << add(5.6, 7) << '\n';   // instantiates and calls add<double, int>()
    std::cout << add(8, 9, 10) << '\n'; // instantiates and calls add<int, int, int>()

    return 0;
}