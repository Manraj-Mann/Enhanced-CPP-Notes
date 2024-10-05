#include <iostream>
/* 
    Notes :  
    
    1. We introduced the challenge of having to create a separate (overloaded) function for each different set of types we want to work with:

        // function to calculate the greater of two int values
        int max(int x, int y)
        {
            return (x < y) ? y : x;
        }

        // almost identical function to calculate the greater of two double values
        // the only difference is the type information
        double max(double x, double y)
        {
            return (x < y) ? y : x;
        }
    
    2. Aggregate types have similar challenges - We run into similar challenges with aggregate types (both structs/classes/unions and arrays).

        struct Pair
        {
            int first{};
            int second{};
        };


        struct Pair // compile error: erroneous redefinition of Pair
        {
            double first{};
            double second{};
        };

        constexpr int max(Pair p)
        {
            return (p.first < p.second ? p.second : p.first);
        }

        constexpr double max(Pair p) // compile error: overloaded function differs only by return type
        {
            return (p.first < p.second ? p.second : p.first);
        }

    3. Class templates - Much like a function template is a template definition for instantiating functions, a class template is a template definition for instantiating class types.

        template <typename T>
        struct Pair
        {
            T first{};
            T second{};
        };

        Pair<int> p1{ 5, 6 };        // instantiates Pair<int> and creates object p1
        std::cout << p1.first << ' ' << p1.second << '\n';

        Just like with function templates, we start a class template definition with a template parameter declaration. We begin with the template keyword. Next, we specify all of the template types that our class template will use inside angled brackets (<>). For each template type that we need, we use the keyword typename (preferred) or class (not preferred), followed by the name of the template type (e.g. T). In this case, since both of our members will be the same type, we only need one template type.

            template <typename T>
            struct Pair
            {
                T first{};
                T second{};
            };

        - Next, we define our struct like usual, except we can use our template type (T) wherever we want a templated type that will be replaced with a real type later. That’s it! We’re done with the class template definition.

            // A declaration for our Pair class template
            // (we don't need the definition any more since it's not used)
            template <typename T>
            struct Pair;

            // Explicitly define what Pair<int> looks like
            template <> // tells the compiler this is a template type with no template parameters
            struct Pair<int>
            {
                int first{};
                int second{};
            };

            // Explicitly define what Pair<double> looks like
            template <> // tells the compiler this is a template type with no template parameters
            struct Pair<double>
            {
                double first{};
                double second{};
            };

        - The above example makes use of a feature called class template specialization

    4.  Using our class template in a function - 

        template <typename T>
        struct Pair
        {
            T first{};
            T second{};
        };

        template <typename T>
        constexpr T max(Pair<T> p)
        {
            return (p.first < p.second ? p.second : p.first);
        }

    5. Class templates with template type and non-template type members - 

        Class templates can have some members using a template type and other members using a normal (non-template) type. For example:

        template <typename T>
        struct Foo
        {
            T first{};    // first will have whatever type T is replaced with
            int second{}; // second will always have type int, regardless of what type T is
        };
    
    6. Class templates with multiple template types - 

        Class templates can also have multiple template types. For example, if we wanted the two members of our Pair class to be able to have different types, we can define our Pair class template with two template types:

        template <typename T, typename U>
        struct Pair
        {
            T first{};
            U second{};
        };

        template <typename T, typename U>
        void print(Pair<T, U> p)
        {
            std::cout << '[' << p.first << ", " << p.second << ']';
        }

        Pair<int, double> p1{ 1, 2.3 }; // a pair holding an int and a double
        print(p2);

    7. Making a function template work with more than one class type - 

            template <typename T, typename U>
            void print(Pair<T, U> p)
            {
                std::cout << '[' << p.first << ", " << p.second << ']';
            }

        Because we’ve explicitly defined the function parameter as a Pair<T, U>, only arguments of type Pair<T, U> (or those that can be converted to a Pair<T, U>) will match. This is ideal if we only want to be able to call our function with a Pair<T, U> argument.

        In some cases, we may write function templates that we want to use with any type that will successfully compile. To do that, we simply use a type template parameter as the function parameter instead.

            template <typename T, typename U>
            struct Pair
            {
                T first{};
                U second{};
            };

            struct Point
            {
                int first{};
                int second{};
            };

            template <typename T>
            void print(T p) // type template parameter will match anything
            {
                std::cout << '[' << p.first << ", " << p.second << ']'; // will only compile if type has first and second members
            }

    8. std::pair - Because working with pairs of data is common, the C++ standard library contains a class template named std::pair (in the <utility> header) that is defined identically to the Pair class template with multiple template types in the preceding section. In fact, we can swap out the pair struct we developed for std::pair:

        template <typename T, typename U>
        void print(std::pair<T, U> p)
        {
            std::cout << '[' << p.first << ", " << p.second << ']';
        }

        std::pair<int, double> p1{ 1, 2.3 }; // a pair holding an int and a double

    9. Using class templates in multiple files - 

        Just like function templates, class templates are typically defined in header files so they can be included into any code file that needs them. Both template definitions and type definitions are exempt from the one-definition rule, so this won’t cause problems:

            pair.h
            #ifndef PAIR_H
            #define PAIR_H

            template <typename T>
            struct Pair
            {
                T first{};
                T second{};
            };

            template <typename T>
            constexpr T max(Pair<T> p)
            {
                return (p.first < p.second ? p.second : p.first);
            }

            #endif

            foo.cpp

            #include "pair.h"
            #include <iostream>

            void foo()
            {
                Pair<int> p1{ 1, 2 };
                std::cout << max(p1) << " is larger\n";
            }

            main.cpp

            #include "pair.h"
            #include <iostream>

            void foo(); // forward declaration for function foo()

            int main()
            {
                Pair<double> p2 { 3.4, 5.6 };
                std::cout << max(p2) << " is larger\n";

                foo();

                return 0;
            }


*/

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair<int> p1{ 5, 6 };
    std::cout << max<int>(p1) << " is larger\n"; // explicit call to max<int>

    Pair<double> p2{ 1.2, 3.4 };
    std::cout << max(p2) << " is larger\n"; // call to max<double> using template argument deduction (prefer this)
    return 0;
}