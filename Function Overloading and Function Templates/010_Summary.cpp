#include <iostream>

/*
    Notes : 

    1. Function overloading allows us to create multiple functions with the same name, so long as each identically named function has different set of parameter types (or the functions can be otherwise differentiated). Such a function is called an overloaded function (or overload for short). Return types are not considered for differentiation.

    2. When resolving overloaded functions, if an exact match isn’t found, the compiler will favor overloaded functions that can be matched via numeric promotions over those that require numeric conversions. When a function call is made to function that has been overloaded, the compiler will try to match the function call to the appropriate overload based on the arguments used in the function call. This is called overload resolution.

    3. An ambiguous match occurs when the compiler finds two or more functions that can match a function call to an overloaded function and can’t determine which one is best.

    4. A default argument is a default value provided for a function parameter. Parameters with default arguments must always be the rightmost parameters, and they are not used to differentiate functions when resolving overloaded functions.

    5. Function templates allow us to create a function-like definition that serves as a pattern for creating related functions. In a function template, we use type template parameters as placeholders for any types we want to be specified later. The syntax that tells the compiler we’re defining a template and declares the template types is called a template parameter declaration.

    6. The process of creating functions (with specific types) from function templates (with template types) is called function template instantiation (or instantiation) for short. When this process happens due to a function call, it’s called implicit instantiation. An instantiated function is called a function instance (or instance for short, or sometimes a template function).

    7. Template argument deduction allows the compiler to deduce the actual type that should be used to instantiate a function from the arguments of the function call. Template argument deduction does not do type conversion.

    8. Template types are sometimes called generic types, and programming using templates is sometimes called generic programming.

    9. In C++20, when the auto keyword is used as a parameter type in a normal function, the compiler will automatically convert the function into a function template with each auto parameter becoming an independent template type parameter. This method for creating a function template is called an abbreviated function template.

    10. A non-type template parameter is a template parameter with a fixed type that serves as a placeholder for a constexpr value passed in as a template argument.

*/

int main()
{

    return 0;
}