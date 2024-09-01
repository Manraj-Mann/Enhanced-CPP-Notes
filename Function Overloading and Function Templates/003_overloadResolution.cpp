#include <iostream>

/*

    Notes : 

    1. However, having a set of differentiated overloaded functions is only half of the picture. When any function call is made, the compiler must also ensure that a matching function declaration can be found.

    2. With overloaded functions, there can be many functions that can potentially match a function call. Since a function call can only resolve to one of them, the compiler has to determine which overloaded function is the best match. The process of matching function calls to a specific overloaded function is called "overload resolution".

    Check follows : 

        void print(int x)
        {
            std::cout << x << '\n';
        }

        void print(double d)
        {
            std::cout << d << '\n';
        }

        print('a'); // char does not match int or double, so what happens?
        print(5L); // long does not match int or double, so what happens?

    
    3. Resolving overloaded function calls - 

        => When a function call is made to an overloaded function, the compiler steps through a sequence of rules to determine which (if any) of the overloaded functions is the best match - 

        => At each step, the compiler applies a bunch of different type conversions to the argument(s) in the function call. 
        
        For each conversion applied, the compiler checks if any of the overloaded functions are now a match. After all the different type conversions have been applied and checked for matches, the step is done. The result will be one of three possible outcomes:

        1. No matching functions were found. The compiler moves to the next step in the sequence.
        
        2. A single matching function was found. This function is considered to be the best match. The matching process is now complete, and subsequent steps are not executed.
        
        3. More than one matching function was found. The compiler will issue an ambiguous match compile error. We’ll discuss this case further in a bit.
        
        If the compiler reaches the end of the entire sequence without finding a match, it will generate a compile error that no matching overloaded function could be found for the function call.

    4. The argument matching sequence - 

        Step 1 - The compiler tries to find an exact match. This happens in two phases. 
        
            - First, the compiler will see if there is an overloaded function where the type of the arguments in the function call exactly matches the type of the parameters in the overloaded functions. 

                void foo(int)
                {
                }

                void foo(double)
                {
                }

                int main()
                {
                    foo(0);   // exact match with foo(int)
                    foo(3.4); // exact match with foo(double)

                    return 0;
                }

            - Second, the compiler will apply a number of trivial conversions to the arguments in the function call. The trivial conversions are a set of specific conversion rules that will modify types (without modifying the value) for purposes of finding a match. These include:

                - lvalue to rvalue conversions
                - qualification conversions (e.g. non-const to const)
                - non-reference to reference conversions

            Example : 

                void foo(const int)
                {
                }

                void foo(const double&)
                {
                }

                int main()
                {
                    int x { 1 };
                    foo(x); // x trivially converted from int to const int

                    double d { 2.3 };
                    foo(d); // d trivially converted from double to const double&

                    return 0;
                }

        Step 2 -  If no exact match is found, the compiler tries to find a match by applying numeric promotion to the argument(s). If, after numeric promotion, a match is found, the function call is resolved.

            void foo(int)
            {
            }

            void foo(double)
            {
            }

            int main()
            {
                foo('a');  // promoted to match foo(int)
                foo(true); // promoted to match foo(int)
                foo(4.5f); // promoted to match foo(double)

                return 0;
            }

        Step 3 - If no match is found via numeric promotion, the compiler tries to find a match by applying numeric conversions to the arguments.

                void foo(double)
                {
                }

                void foo(std::string)
                {
                }

                int main()
                {
                    foo('a'); // 'a' converted to match foo(double)

                    return 0;
                }

            Matches made by applying numeric promotions take precedence over any matches made by applying numeric conversions.

        Step 4 - If no match is found via numeric conversion, the compiler tries to find a match through any user-defined conversions. Although we haven’t covered user-defined conversions yet, certain types (e.g. classes) can define conversions to other types that can be implicitly invoked.

            class X // this defines a new type called X
            {
            public:
                operator int() { return 0; } // Here's a user-defined conversion from X to int
            };

            void foo(int)
            {
            }

            void foo(double)
            {
            }

            int main()
            {
                X x; // Here, we're creating an object of type X (named x)
                foo(x); // x is converted to type int using the user-defined conversion from X to int

                return 0;
            }

            The constructor of a class also acts as a user-defined conversion from other types to that class type, and can be used during this step to find matching functions.

        Step 5 - If no match is found via user-defined conversion, the compiler will look for a matching function that uses ellipsis.

        Step 6 - If no matches have been found by this point, the compiler gives up and will issue a compile error about not being able to find a matching function.

    5. Ambiguous matches - With overloaded functions, there is a third possible outcome: an ambiguous match may be found. An ambiguous match occurs when the compiler finds two or more functions that can be made to match in the same step. When this occurs, the compiler will stop matching and issue a compile error stating that it has found an ambiguous function call.

    If the compiler finds multiple matches in a given step, an ambiguous function call will result. This means no match from a given step is considered to be better than any other match from the same step.

    6. Resolving ambiguous matches - Because ambiguous matches are a compile-time error, an ambiguous match needs to be disambiguated before your program will compile. 
    
        There are a few ways to resolve ambiguous matches:

        1. The best way is simply to define a new overloaded function that takes parameters of exactly the type you are trying to call the function with. Then C++ will be able to find an exact match for the function call.

        2. Alternatively, explicitly cast the ambiguous argument(s) to match the type of the function you want to call. 

            int x{ 0 };
            foo(static_cast<unsigned int>(x)); // will call foo(unsigned int)

        3. If your argument is a literal, you can use the literal suffix to ensure your literal is interpreted as the correct type:

            foo(0u); // will call foo(unsigned int) since 'u' suffix is unsigned int, so this is now an exact match

        
    7. Matching for functions with multiple arguments - 

        If there are multiple arguments, the compiler applies the matching rules to each argument in turn. Function chosen must provide a better match than all the other candidate functions for at least one parameter, and no worse for all of the other parameters.

*/


class X // this defines a new type called X
{
public:
    operator int() { return 0; } // Here's a user-defined conversion from X to int
};

void foo(int)
{
}

void foo(double)
{
}

int main()
{
    X x; // Here, we're creating an object of type X (named x)
    foo(x); // x is converted to type int using the user-defined conversion from X to int

    return 0;
}