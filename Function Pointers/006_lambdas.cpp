#include <iostream>
/* 
    Notes :  
    
    1. Lambdas are anonymous functions : A lambda expression (also called a lambda or closure) allows us to define an anonymous function inside another function. The nesting is important, as it allows us both to avoid namespace naming pollution, and to define the function as close to where it is used as possible (providing additional context).

        - The syntax for lambdas is one of the weirder things in C++, and takes a bit of getting used to. Lambdas take the form:

            [ captureClause ] ( parameters ) -> returnType
            {
                statements;
            }
        
        - The capture clause can be empty if no captures are needed.
        - The parameter list can be empty if no parameters are required. It can also be omitted entirely unless a return type is specified.
        - The return type is optional, and if omitted, auto will be assumed (thus using type deduction used to determine the return type). While we previously noted that type deduction for function return types should be avoided, in this context, it’s fine to use (because these functions are typically so trivial).

        - Example : 

            void printCaller(std::function<bool(int)> func)
            {
                bool done = func(4);
                std::cout<<(done ? "done" : "not done")<<std::endl;
            }
            int main()
            {
                printCaller(
                    [](int a)-> bool
                    {
                        std::cout<<"Caller  : "<<a<<std::endl;
                        return true;
                    }
                );
                return 0;
            }

        - Following the best practice of defining things in the smallest scope and closest to first use, lambdas are preferred over normal functions when we need a trivial, one-off function to pass as an argument to some other function.

    2. Type of a lambda : In the above example, we defined a lambda right where it was needed. This use of a lambda is sometimes called a function literal.

        - However, writing a lambda in the same line as it’s used can sometimes make code harder to read. Much like we can initialize a variable with a literal value (or a function pointer) for use later, we can also initialize a lambda variable with a lambda definition and then use it later. A named lambda along with a good function name can make code easier to read.

        - We can improve the readability of this as follows:

            // Good: Instead, we can store the lambda in a named variable and pass it to the function.
            auto isEven{
            [](int i)
            {
                return (i % 2) == 0;
            }
            };

            return std::all_of(array.begin(), array.end(), isEven);

    3. Storing a lambda in a variable provides a way for us to give the lambda a useful name, which can help make our code more readable. Storing a lambda in a variable also provides us with a way to use that lambda more than once. But what is the type of lambda isEven? As it turns out, lambdas don’t have a type that we can explicitly use. When we write a lambda, the compiler generates a unique type just for the lambda that is not exposed to us.

        - In actuality, lambdas aren’t functions (which is part of how they avoid the limitation of C++ not supporting nested functions). They’re a special kind of object called a "functor". "Functors are objects that contain an overloaded operator() that make them callable like a function".

        - Although we don’t know the type of a lambda, there are several ways of storing a lambda for use post-definition. If the lambda has an empty capture clause (nothing between the hard brackets []), we can use a regular function pointer. std::function or type deduction via the auto keyword will also work (even if the lambda has a non-empty capture clause).

            using fType = std::function<int(int , int)>;
            fType f = [](int a, int b)->int
                    { 
                        std::cout<<"int , int called"; 
                        return a + b;
                    };

            // A regular function pointer. Only works with an empty capture clause (empty []).
            double (*addNumbers1)(double, double){
                [](double a, double b) {
                return a + b;
                }
            };

    4. The only way of using the lambda’s actual type is by means of auto. auto also has the benefit of having no overhead compared to std::function.

        - What if we want to pass a lambda to a function? There are 4 options:

            // Case 1: use a `std::function` parameter
            void repeat1(int repetitions, const std::function<void(int)>& fn)
            {
                for (int i{ 0 }; i < repetitions; ++i)
                    fn(i);
            }

            // Case 2: use a function template with a type template parameter
            template <typename T>
            void repeat2(int repetitions, const T& fn)
            {
                for (int i{ 0 }; i < repetitions; ++i)
                    fn(i);
            }

            // Case 3: use the abbreviated function template syntax (C++20)
            void repeat3(int repetitions, const auto& fn)
            {
                for (int i{ 0 }; i < repetitions; ++i)
                    fn(i);
            }

            // Case 4: use function pointer (only for lambda with no captures)
            void repeat4(int repetitions, void (*fn)(int))
            {
                for (int i{ 0 }; i < repetitions; ++i)
                    fn(i);
            }

        - When storing a lambda in a variable, use auto as the variable’s type.

    5. Generic lambdas - For the most part, lambda parameters work by the same rules as regular function parameters. One notable exception is that since C++14 we’re allowed to use auto for parameters (note: in C++20, regular functions are able to use auto for parameters too). When a lambda has one or more auto parameter, the compiler will infer what parameter types are needed from the calls to the lambda.

        - Because lambdas with one or more auto parameter can potentially work with a wide variety of types, they are called generic lambdas.

            Example : 

              constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
                    "January",
                    "February",
                    "March",
                    "April",
                    "May",
                    "June",
                    "July",
                    "August",
                    "September",
                    "October",
                    "November",
                    "December"
                };

                // Search for two consecutive months that start with the same letter.
                const auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
                                                    [](const auto& a, const auto& b) {
                                                        return a[0] == b[0];
                                                    }) };

                // Make sure that two months were found.
                if (sameLetter != months.end())
                {
                    // std::next returns the next iterator after sameLetter
                    std::cout << *sameLetter << " and " << *std::next(sameLetter)
                            << " start with the same letter\n";
                }

            => In the above example, we use auto parameters to capture our strings by const reference. Because all string types allow access to their individual characters via operator[], we don’t need to care whether the user is passing in a std::string, C-style string, or something else. This allows us to write a lambda that could accept any of these, meaning if we change the type of months later, we won’t have to rewrite the lambda.

        - However, auto isn’t always the best choice. Consider:

            Example : 

                constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
                    "January",
                    "February",
                    "March",
                    "April",
                    "May",
                    "June",
                    "July",
                    "August",
                    "September",
                    "October",
                    "November",
                    "December"
                };

                // Count how many months consist of 5 letters
                const auto fiveLetterMonths{ std::count_if(months.begin(), months.end(),
                                                    [](std::string_view str) {
                                                        return str.length() == 5;
                                                    }) };

                std::cout << "There are " << fiveLetterMonths << " months with 5 letters\n";

            => In this example, using auto would infer a type of const char*. C-style strings aren’t easy to work with (apart from using operator[]). In this case, we prefer to explicitly define the parameter as a std::string_view, which allows us to work with the underlying data much more easily (e.g. we can ask the string view for its length, even if the user passed in a C-style array).

    6. Constexpr lambdas - As of C++17, lambdas are implicitly constexpr if the result satisfies the requirements of a constant expression. This generally requires two things:

        = The lambda must either have no captures, or all captures must be constexpr.
        = The functions called by the lambda must be constexpr. 
        
        Note that many standard library algorithms and math functions weren’t made constexpr until C++20 or C++23.
        
        In the above example, our lambda would not be implicitly constexpr in C++17 but it would be in C++20 (as std::count_if was made constexpr in C++20). This means in C++20 we can make fiveLetterMonths constexpr:

            constexpr auto fiveLetterMonths{ std::count_if(months.begin(), months.end(),
                                                [](std::string_view str) {
                                                return str.length() == 5;
                                                }) };
    
    7. When a function template contains a static local variable, each function instantiated from that template will receive its own independent static local variable. This may cause issues if that is not expected.

        template <typename T>
        void increment() {
            static int counter = 0; // Static local variable
            ++counter;
            std::cout << "Type: " << typeid(T).name() << ", Counter: " << counter << '\n';
        }
    
    8. Generic lambdas work the same way: a unique lambda will be generated for each different type that auto resolves to. The following example shows how one generic lambda turns into two distinct lambdas:

    9. Return type deduction and trailing return types : 

        - If return type deduction is used, a lambda’s return type is deduced from the return-statements inside the lambda, and all return statements in the lambda must return the same type (otherwise the compiler won’t know which one to prefer).

        Example :
        
            auto divide{ [](int x, int y, bool intDivision) { // note: no specified return type
                if (intDivision)
                return x / y; // return type is int
                else
                return static_cast<double>(x) / y; // ERROR: return type doesn't match previous return type
            } };

            std::cout << divide(3, 2, true) << '\n';

        - This produces a compile error because the return type of the first return statement (int) doesn’t match the return type of the second return statement (double).

        - In the case where we’re returning different types, we have two options:
        
            1. Do explicit casts to make all the return types match, or
            
            2. explicitly specify a return type for the lambda, and let the compiler do implicit conversions.

    10. Standard library function objects - 

        - For common operations (e.g. addition, negation, or comparison) you don’t need to write your own lambdas, because the standard library comes with many basic callable objects that can be used instead. These are defined in the <functional> header.

        bool greater(int a, int b)
        {
        // Order @a before @b if @a is greater than @b.
        return a > b;
        }

        // Pass greater to std::sort
        std::sort(arr.begin(), arr.end(), greater);

        // Pass std::greater to std::sort
        // std::sort(arr.begin(), arr.end(), std::greater{}); // note: need curly braces to instantiate object

    11. Conclusion 
    
        - Lambdas and the algorithm library may seem unnecessarily complicated when compared to a solution that uses a loop. However, this combination can allow some very powerful operations in just a few lines of code, and can be more readable than writing your own loops. On top of that, the algorithm library features powerful and easy-to-use parallelism, which you won’t get with loops. Upgrading source code that uses library functions is easier than upgrading code that uses loops.

        - Lambdas are great, but they don’t replace regular functions for all cases. Prefer regular functions for non-trivial and reusable cases.

        - When used in the context of a lambda, auto is just a shorthand for a template parameter.

*/

#include <functional>
#include <algorithm>
#include <array>
#include <string_view>

void printCaller(std::function<bool(int)> func)
{
    bool done = func(4);
    std::cout<<(done ? "done" : "not done")<<std::endl;
}


int nonconstexpr(int &a)
{
    // std::cin>>a;
    return ++a;
}
constexpr int isconstexpr(int &a)
{
    return ++a;
}

template <typename T>
void increment() {
    static int counter = 0; // Static local variable
    ++counter;
    std::cout << "Type: " << typeid(T).name() << ", Counter: " << counter << '\n';
}

struct greater
{
    public:

    constexpr bool operator ()(const auto & a , const auto &b)
    {
        return a > b;
    }
};

int main()
{
    printCaller(
        [](int a)-> bool
        {
            std::cout<<"Caller  : "<<a<<std::endl;
            return true;
        }
    );

    using fType = std::function<int(int , int)>;


    fType f = [](int a, int b)->int
                { 
                    std::cout<<"int , int called"<<std::endl; 
                    return a + b;
                };

    double (*dTor)(double , double )
    {
        [](double a, double b){ return a + b;}
    };

    std::cout<<"D = "<<dTor( 10.1 , 12.3)<<std::endl;
    std::cout<<"F = "<<f( 10.1 , 12.3)<<std::endl;

    constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    // Search for two consecutive months that start with the same letter.
    const auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
                                        [](const auto& a, const auto& b) {
                                            return a[0] == b[0];
                                        }) };

    // Make sure that two months were found.
    if (sameLetter != months.end())
    {
        // std::next returns the next iterator after sameLetter
        std::cout << *sameLetter << " and " << *std::next(sameLetter)
                << " start with the same letter\n";
    }


    const auto functor {

        [](int a) -> auto
        {
            return a;
        }
        
    };

    std::cout<<"Functor : "<<functor(1)<<std::endl;

    constexpr auto constCaller {

        [](int &a)
        {
            return isconstexpr(a);
        }
    };

    int p = 0;
    std::cout<<"Value from caller : "<<constCaller(p)<<std::endl;


    increment<int>();
    increment<double>();
    increment<int>();

    // Print a value and count how many times @print has been called.
    auto print{
        [](auto value) {
        static int callCount{ 0 };
        std::cout << callCount++ << ": " << value << '\n';
        }
    };

    print("hello"); // 0: hello
    print("world"); // 1: world

    print(1); // 0: 1
    print(2); // 1: 2

    print("ding dong"); // 2: ding dong
    print("ding docker"); // 3: ding docker

    // auto divide{ [](int x, int y, bool intDivision) 
    // { // note: no specified return type
    //     if (intDivision)
    //         return x / y; // return type is int
    //     else
    //         return static_cast<double>(x) / y; // ERROR: return type doesn't match previous return type
    // } };

    auto divide{ 
        
        [](int x, int y, bool intDivision) -> double
        { // note: no specified return type
            if (intDivision)
                return x / y; // return type is int expilictly casted to double
            else
                return static_cast<double>(x) / y; 
        }
    };

    std::cout << divide(3, 2, true) << '\n';
    std::cout << divide(3, 2, false) << '\n';
    

    std::array arr{ 13, 90, 99, 5, 40, 80 };
    std::sort(arr.begin(), arr.end(), greater{});

    std::cout<<"Values : ";
    for(auto i : arr)
    {
        std::cout<<i<<" ";
    }


    return 0;
}