#include <iostream>
/* 
    Notes :  
    
    1. Class template argument deduction (CTAD) C++17 - Starting in C++17, when instantiating an object from a class template, the compiler can deduce the template types from the types of the object’s initializer (this is called class template argument deduction or CTAD for short). For example:

        std::pair<int, int> p1{ 1, 2 }; // explicitly specify class template std::pair<int, int> (C++11 onward)
        std::pair p2{ 1, 2 };           // CTAD used to deduce std::pair<int, int> from the initializers (C++17)

    2. CTAD is only performed if no template argument list is present. Therefore, both of the following are errors: 

        std::pair<> p1 { 1, 2 };    // error: too few template arguments, both arguments not deduced
        std::pair<int> p2 { 3, 4 }; // error: too few template arguments, second argument not deduced

    3. Template argument deduction guides C++17  - 

        - In most cases, CTAD works right out of the box. However, in certain cases, the compiler may need a little extra help understanding how to deduce the template arguments properly.You may be surprised to find that the following program (which is almost identical to the example that uses std::pair above) doesn’t compile in C++17 (only):

            // define our own Pair type
            template <typename T, typename U>
            struct Pair
            {
                T first{};
                U second{};
            };

            int main()
            {
                Pair<int, int> p1{ 1, 2 }; // ok: we're explicitly specifying the template arguments
                Pair p2{ 1, 2 };           // compile error in C++17 (okay in C++20)

            }

        - If you compile this in C++17, you’ll likely get some error about “class template argument deduction failed” or “cannot deduce template arguments” or “No viable constructor or deduction guide”. This is because in C++17, CTAD doesn’t know how to deduce the template arguments for aggregate class templates. To address this, we can provide the compiler with a deduction guide, which tells the compiler how to deduce the template arguments for a given class template.

            // Here's a deduction guide for our Pair (needed in C++17 only)
            // Pair objects initialized with arguments of type T and U should deduce to Pair<T, U>
            template <typename T, typename U>
            Pair(T, U) -> Pair<T, U>;

        - First, we use the same template type definition as in our Pair class. This makes sense, because if our deduction guide is going to tell the compiler how to deduce the types for a Pair<T, U>, we have to define what T and U are (template types). Second, on the right hand side of the arrow, we have the type that we’re helping the compiler to deduce. In this case, we want the compiler to be able to deduce template arguments for objects of type Pair<T, U>, so that’s exactly what we put here. Finally, on the left side of the arrow, we tell the compiler what kind of declaration to look for. In this case, we’re telling it to look for a declaration of some object named Pair with two arguments (one of type T, the other of type U). We could also write this as Pair(T t, U u) (where t and u are the names of the parameters, but since we don’t use t and u, we don’t need to give them names).

    4. Tip - C++20 added the ability for the compiler to automatically generate deduction guides for aggregates, so deduction guides should only need to be provided for C++17 compatibility. Because of this, the version of Pair without the deduction guides should compile in C++20.

    std::pair (and other standard library template types) come with pre-defined deduction guides, which is why our example above that uses std::pair compiles fine in C++17 without us having to provide deduction guides ourselves.

    Non-aggregates don’t need deduction guides in C++17 because the presence of a constructor serves the same purpose.

    5. Type template parameters with default values - 

        Just like function parameters can have default arguments, template parameters can be given default values. These will be used when the template parameter isn’t explicitly specified and can’t be deduced.

            template <typename T=int, typename U=int> // default T and U to type int
            struct Pair
            {
                T first{};
                U second{};
            };

            template <typename T, typename U>
            Pair(T, U) -> Pair<T, U>;

        Pair<int, int> p1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
        Pair p2{ 1, 2 };           // CTAD used to deduce Pair<int, int> from the initializers (C++17)

        Pair p3;                   // uses default Pair<int, int>


    6. CTAD doesn’t work with non-static member initialization - When initializing the member of a class type using non-static member initialization, CTAD will not work in this context. All template arguments must be explicitly specified:

        struct Foo
        {
            std::pair<int, int> p1{ 1, 2 }; // ok, template arguments explicitly specified
            std::pair p2{ 1, 2 };           // compile error, CTAD can't be used in this context
        };

        std::pair p3{ 1, 2 };           // ok, CTAD can be used here

    7. CTAD doesn’t work with function parameters - CTAD stands for class template argument deduction, not class template parameter deduction, so it will only deduce the type of template arguments, not template parameters.

    Therefore, CTAD can’t be used in function parameters.

        void print(std::pair p) // compile error, CTAD can't be used here
        {
            std::cout << p.first << ' ' << p.second << '\n';
        }

    In such cases, you should use a template instead:

        template <typename T, typename U>
        void print(std::pair<T, U> p)
        {
            std::cout << p.first << ' ' << p.second << '\n';
        }

*/
#include <utility> // for std::pair


template <typename T=int, typename U=int> // default T and U to type int
struct Pair
{
    T first{};
    U second{};
};

template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;


struct Foo
{
    std::pair<int, int> p1{ 1, 2 }; // ok, template arguments explicitly specified
    std::pair p2{ 1, 2 };           // compile error, CTAD can't be used in this context
};

int main()
{
    Pair<int, int> p1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
    Pair p2{ 1, 2 };           // CTAD used to deduce Pair<int, int> from the initializers (C++17)

    Pair p3;                   // uses default Pair<int, int>

    std::pair p4{ 1, 2 };           // ok, CTAD can be used here

    return 0;
}