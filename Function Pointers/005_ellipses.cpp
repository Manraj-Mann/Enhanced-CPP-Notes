#include <iostream>
/* 
    Notes :  
    
    1. Ellipsis - In all of the functions we’ve seen so far, the number of parameters a function will take must be known in advance (even if they have default values). However, there are certain cases where it can be useful to be able to pass a variable number of parameters to a function. C++ provides a special specifier known as ellipsis (aka “…”) that allow us to do precisely this.

    2. Because ellipsis are rarely used, potentially dangerous, and we recommend avoiding their use, this section can be considered optional reading.

        - Functions that use ellipsis take the form:

            return_type function_name(argument_list, ...)
    
        - The argument_list is one or more normal function parameters. Note that functions that use ellipsis must have at least one non-ellipsis parameter. Any arguments passed to the function must match the argument_list parameters first.

    3. The ellipsis (which are represented as three periods in a row) must always be the last parameter in the function. The ellipsis capture any additional arguments (if there are any). Though it is not quite accurate, it is conceptually useful to think of the ellipsis as an array that holds any additional parameters beyond those in the argument_list.

    4. An ellipsis example - The best way to learn about ellipsis is by example. So let’s write a simple program that uses ellipsis. Let’s say we want to write a function that calculates the average of a bunch of integers. We’d do it like this:

        // The ellipsis must be the last parameter
        // count is how many additional arguments we're passing
        double findAverage(int count, ...)
        {
            int sum{ 0 };

            // We access the ellipsis through a va_list, so let's declare one
            std::va_list list;

            // We initialize the va_list using va_start.  The first argument is
            // the list to initialize.  The second argument is the last non-ellipsis
            // parameter.
            va_start(list, count);

            // Loop through all the ellipsis values
            for (int arg{ 0 }; arg < count; ++arg)
            {
                // We use va_arg to get values out of our ellipsis
                // The first argument is the va_list we're using
                // The second argument is the type of the value
                sum += va_arg(list, int);
            }

            // Cleanup the va_list when we're done.
            va_end(list);

            return static_cast<double>(sum) / count;
        }

    5. Why ellipsis are dangerous: Type checking is suspended - 

        - Ellipsis offer the programmer a lot of flexibility to implement functions that can take a variable number of parameters. However, this flexibility comes with some downsides.

        - With regular function parameters, the compiler uses type checking to ensure the types of the function arguments match the types of the function parameters (or can be implicitly converted so they match). This helps ensure you don’t pass a function an integer when it was expecting a string, or vice versa. However, note that ellipsis parameters have no type declarations. When using ellipsis, the compiler completely suspends type checking for ellipsis parameters. This means it is possible to send arguments of any type to the ellipsis! However, the downside is that the compiler will no longer be able to warn you if you call the function with ellipsis arguments that do not make sense. When using the ellipsis, it is completely up to the caller to ensure the function is called with ellipsis arguments that the function can handle. Obviously that leaves quite a bit of room for error (especially if the caller wasn’t the one who wrote the function).

    6. Why ellipsis are dangerous: ellipsis don’t know how many parameters were passed - 

        Not only do the ellipsis throw away the type of the parameters, it also throws away the number of parameters in the ellipsis. This means we have to devise our own solution for keeping track of the number of parameters passed into the ellipsis. Typically, this is done in one of three ways.

        6.1. Method 1: Pass a length parameter : Method #1 is to have one of the fixed parameters represent the number of optional parameters passed. This is the solution we use in the findAverage() example above.

        6.2. Method 2: Use a sentinel value : Method #2 is to use a sentinel value. A sentinel is a special value that is used to terminate a loop when it is encountered. For example, with strings, the null terminator is used as a sentinel value to denote the end of the string. With ellipsis, the sentinel is typically passed in as the last parameter.

            // The ellipsis must be the last parameter
            double findAverage(int first, ...)
            {
                // We have to deal with the first number specially
                int sum{ first };

                // We access the ellipsis through a va_list, so let's declare one
                std::va_list list;

                // We initialize the va_list using va_start.  The first argument is
                // the list to initialize.  The second argument is the last non-ellipsis
                // parameter.
                va_start(list, first);

                int count{ 1 };
                // Loop indefinitely
                while (true)
                {
                    // We use va_arg to get values out of our ellipsis
                    // The first argument is the va_list we're using
                    // The second argument is the type of the value
                    int arg{ va_arg(list, int) };

                    // If this parameter is our sentinel value, stop looping
                    if (arg == -1)
                        break;

                    sum += arg;
                    ++count;
                }

                // Cleanup the va_list when we're done.
                va_end(list);

                return static_cast<double>(sum) / count;
            }

        6.3. Method 3: Use a decoder string : Method #3 involves passing a “decoder string” that tells the program how to interpret the parameters.

            // The ellipsis must be the last parameter
            double findAverage(std::string_view decoder, ...)
            {
                double sum{ 0 };

                // We access the ellipsis through a va_list, so let's declare one
                std::va_list list;

                // We initialize the va_list using va_start.  The first argument is
                // the list to initialize.  The second argument is the last non-ellipsis
                // parameter.
                va_start(list, decoder);

                for (auto codetype: decoder)
                {
                    switch (codetype)
                    {
                    case 'i':
                        sum += va_arg(list, int);
                        break;

                    case 'd':
                        sum += va_arg(list, double);
                        break;
                    }
                }

                // Cleanup the va_list when we're done.
                va_end(list);

                return sum / std::size(decoder);
            }

    7. Recommendations for safer use of ellipsis :

        - First, if possible, do not use ellipsis at all! Oftentimes, other reasonable solutions are available, even if they require slightly more work. For example, in our findAverage() program, we could have passed in a dynamically sized array of integers instead. This would have provided both strong type checking (to make sure the caller doesn’t try to do something nonsensical) while preserving the ability to pass a variable number of integers to be averaged.

        - Second, if you do use ellipsis, it is better if all values passed to the ellipses parameter are the same type (e.g. all int, or all double, not a mix of each). Intermixing different types vastly increases the possibility of the caller inadvertently passing in data of the wrong type and va_arg() producing a garbage result.

        - Third, using a count parameter or decoder string parameter is generally safer than using a sentinel value. This forces the user to pick an appropriate value for the count/decoder parameter, which ensures the ellipsis loop will terminate after a reasonable number of iterations even if it produces a garbage value.
    
    8. For advanced readers -  To improve upon ellipses-like functionality, C++11 introduced parameter packs and variadic templates, which offers functionality similar to ellipses, but with strong type checking. However, significant usability challenges impeded adoption of this feature. In C++17, fold expressions were added, which significantly improves the usability of parameter packs, to the point where they are now a viable option.


*/

#include <cstdarg> // needed to use ellipsis
// The ellipsis must be the last parameter
// count is how many additional arguments we're passing
double findAverage(int count, ...)
{
    int sum{ 0 };

    // We access the ellipsis through a va_list, so let's declare one
    std::va_list list;

    // We initialize the va_list using va_start.  The first argument is
    // the list to initialize.  The second argument is the last non-ellipsis
    // parameter.
    va_start(list, count);

    // Loop through all the ellipsis values
    for (int arg{ 0 }; arg < count; ++arg)
    {
         // We use va_arg to get values out of our ellipsis
         // The first argument is the va_list we're using
         // The second argument is the type of the value
         sum += va_arg(list, int);
    }

    // Cleanup the va_list when we're done.
    va_end(list);

    return static_cast<double>(sum) / count;
}

int main()
{
    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';

    return 0;
}