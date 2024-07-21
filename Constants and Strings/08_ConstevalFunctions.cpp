#include <iostream>
#include <type_traits>

/*
Note : 

1. A constexpr function is a function that is allowed to be called in a constant expression. The constexpr keyword is used to signal to the compiler and other developers that a function can be used in a constant expression.

2. Constexpr functions can be evaluated at compile time: 

When a function call is evaluated at compile-time, the compiler will calculate the return value of the function call at compile-time, and then replace the function call with the return value.

To evaluate at compile-time, two other things must also be true:

    1. The call to the constexpr function must have arguments that are known at compile time (e.g. are constant expressions).

    2. All statements and expressions within the constexpr function must be evaluatable at compile-time.

3. Constexpr functions can also be evaluated at runtime:

Constexpr functions can also be evaluated at runtime, in which case they will return a non-constexpr result.When a constexpr function evaluates at runtime, it evaluates just like a normal (non-constexpr) function would. In other words, the constexpr has no effect in this case.

4. Constexpr function calls in non-required constant expressions:

You might expect that a constexpr function would evaluate at compile-time whenever possible, but unfortunately this is not the case.
For example:

#include <iostream>

constexpr int getValue(int x)
{
    return x;
}

int main()
{
    int x { getValue(5) }; // may evaluate at runtime or compile-time

    return 0;
}

In the above example, because getValue() is constexpr, the call getValue(5) is a constant expression. However, because variable x is not constexpr, it does not require a constant expression initializer. So even though we’ve provided a constant expression initializer, the compiler is free to choose whether getValue(5) evaluates at runtime or compile-time.

Compile-time evaluation of constexpr functions is only guaranteed when a constant expression is required.

5. All constexpr functions should be evaluatable at compile-time, as they will be required to do so in contexts that require a constant expression.

Always test your constexpr functions in a context that requires a constant expression, as the constexpr function may work when evaluated at runtime but fail when evaluated at compile-time.

// non const expr
int getValue(int x)
{
    return x;
}

// This function can be evaluated at runtime
// When evaluated at compile-time, the function will produce a compilation error
// because the call to getValue(x) cannot be resolved at compile-time
constexpr int foo(int x)
{
    return getValue(x); // call to non-constexpr function here
}

int main()
{
    int x { foo(5) };           // okay: will evaluate at runtime
    constexpr int y { foo(5) }; // compile error: foo(5) can't evaluate at compile-time

    return 0;
}

6. The parameters of a constexpr function are not implicitly constexpr, nor may they be declared as constexpr.

7. Constexpr functions are implicitly inline :

When a constexpr function is evaluated at compile-time, the compiler must be able to see the full definition of the constexpr function prior to such function calls (so it can perform the evaluation itself). A forward declaration will not suffice in this case, even if the actual function definition appears later in the same compilation unit.

The compiler must be able to see the full definition of a constexpr (or consteval) function, not just a forward declaration.

8. Recap : 

1. Marking a function as constexpr means it can be used in a constant expression. It does not mean “will evaluate at compile-time”.
2. A constant expression (which may contain constexpr function calls) is only required to evaluate at compile-time in contexts where a constant expression is required.
3. In contexts that do not require a constant expression, the compiler may choose whether to evaluate a constant expression (which may contain constexpr function calls) at compile-time or at runtime.
4. A runtime (non-constant) expression (which may contain constexpr function calls or non-constexpr function calls) will evaluate at runtime.

9. std::is_constant_evaluated or if consteval

std::is_constant_evaluated() (defined in the <type_traits> header) returns a bool indicating whether the current function is executing in a constant-evaluated context. A constant-evaluated context (also called a constant context) is defined as one in which a constant expression is required (such as the initialization of a constexpr variable). So in cases where the compiler is required to evaluate a constant expression at compile-time std::is_constant_evaluated() will true as expected.

10. Consteval C++20

C++20 introduces the keyword consteval, which is used to indicate that a function must evaluate at compile-time, otherwise a compile error will result. Such functions are called immediate functions.

consteval int greater(int x, int y) // function is now consteval
{
    return (x > y ? x : y);
}

This will give either error or compile time evaluation.

11. Using consteval to make constexpr execute at compile-time 

The downside of consteval functions is that such functions can’t evaluate at runtime, making them less flexible than constexpr functions, which can do either. Therefore, it would still be useful to have a convenient way to force constexpr functions to evaluate at compile-time (even when the return value is being used where a constant expression is not required), so that we could have compile-time evaluation when possible, and runtime evaluation when we can’t.

// Uses abbreviated function template (C++20) and `auto` return type to make this function work with any type of value
// See 'related content' box below for more info (you don't need to know how these work to use this function)
consteval auto compileTimeEval(auto value)
{
    return value;
}

constexpr int greater(int x, int y) // function is constexpr
{
    return (x > y ? x : y);
}

int main()
{
    std::cout << greater(5, 6) << '\n';                  // may or may not execute at compile-time
    std::cout << compileTimeEval(greater(5, 6)) << '\n'; // will execute at compile-time

    int x { 5 };
    std::cout << greater(x, 6) << '\n';                  // we can still call the constexpr version at runtime if we wish

    return 0;
}


12. Constexpr/consteval functions can use non-const local variables. Constexpr/consteval functions can use function parameters and local variables as arguments in constexpr function calls

13. Why not constexpr every function?

There are a few reasons you may not want to constexpr a function:

    1. constexpr signals that a function can be used in a constant expression. If your function cannot be evaluated as part of a constant expression, it should not be marked as constexpr.
    2. constexpr is part of the interface of a function. Once a function is made constexpr, it can be called by other constexpr functions or used in contexts that require constant expressions. Removing the constexpr later will break such code.
    3. constexpr makes functions harder to debug because you can’t inspect them at runtime.

*/



constexpr double calcCircumference(double radius) // now a constexpr function
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}

// constexpr double setvale(double radius) // now a constexpr function
// {
//     std::cin>>radius;
//     constexpr double pi { 3.14159265359 };
//     return 2.0 * pi * radius;
// }

int getValue()
{
    return 1;
}

// constexpr int example(int a)
// {
//     constexpr int value{a};

//     return 2 * value;
// }

constexpr int greater(int x, int y)
{
    return (x > y ? x : y);
}

constexpr void doSomething()
{
    
}

void doSomethingElse()
{
    
}

// constexpr int someFunction()
// {
//     if (std::is_constant_evaluated()) // if evaluating in constant context
//         doSomething();
//     else
//         doSomethingElse();
    
//     return 1;
// }



int main()
{
    // constexpr int value{getValue()}; .// error due to inability of evaluation of getValue at compile time

    constexpr double c {calcCircumference(9)};
    std::cout<<"Circum : "<<c<<std::endl;

    // int radius;
    // std::cin>>radius;

    // constexpr double p{calcCircumference(radius)};
    // std::cout<<"Circum 2 : "<<p<<std::endl;

    // above will give an error : error: the value of ‘radius’ is not usable in a constant expression

    // constexpr double k{setvale(1)}; // error : The function call should also not contain any runtime expression

    // constexpr int a {1};
    // std::cout<<"value : "<<example(a)<<std::endl; // error : refer to pount 6


    // ---------------------------------------

    
    constexpr int g { greater(5, 6) };              // case 1: always evaluated at compile-time
    std::cout << g << " is greater!\n";

    std::cout << greater(5, 6) << " is greater!\n"; // case 2: may be evaluated at either runtime or compile-time

    int x{ 5 }; // not constexpr but value is known at compile-time
    std::cout << greater(x, 6) << " is greater!\n"; // case 3: likely evaluated at runtime

    std::cin >> x;
    std::cout << greater(x, 6) << " is greater!\n"; // case 4: always evaluated at runtime

    // someFunction();

    // c++ 23
    // if consteval {
    //     // This block is executed only at compile time
    //     std::cout << "This code is executed at compile time.\n";
    // } 
    // else {
    //     // This block is executed only at run time
    //     std::cout << "This code is executed at run time.\n";
    // }





    return 0;
}