#include <iostream>

/*
    Notes : 

    1. Function templates are not actually functions -- their code isn’t compiled or executed directly. Instead, function templates have one job: to generate functions (that are compiled and executed).

    2. The process of creating functions (with specific types) from function templates (with template types) is called "function template instantiation" (or instantiation for short). When a function is instantiated due to a function call, it’s called "implicit instantiation". A function that is instantiated from a template is technically called a "specialization", but in common language is often called a "function instance". The template from which a specialization is produced is called a primary template. Function instances are normal functions in all regards.

    3. The term “specialization” is more often used to refer to explicit specialization, which allows us to explicitly define a specialization (rather than have it implicitly instantiated from the primary template). 

    4. A function template is only instantiated the first time a function call is made in each translation unit.

        Example of expansion : 

        // a declaration for our function template (we don't need the definition any more)
        template <typename T>
        T max(T x, T y);

        template<>
        int max<int>(int x, int y) // the generated function max<int>(int, int)
        {
            return (x < y) ? y : x;
        }

        template<>
        double max<double>(double x, double y) // the generated function max<double>(double, double)
        {
            return (x < y) ? y : x;
        }

    5. Template argument deduction : In cases where the type of the arguments match the actual type we want, we do not need to specify the actual type -- instead, we can use template argument deduction to have the compiler deduce the actual type that should be used from the argument types in the function call.

        For example, instead of making a function call like this:

        std::cout << max<int>(1, 2) << '\n'; // specifying we want to call max<int>
        
        We can do one of these instead:

        std::cout << max<>(1, 2) << '\n';
        std::cout << max(1, 2) << '\n';

    6. The difference between the two cases has to do with how the compiler resolves the function call from a set of overloaded functions. In the top case (with the empty angled brackets), the compiler will only consider max<int> template function overloads when determining which overloaded function to call. In the bottom case (with no angled brackets), the compiler will consider both max<int> template function overloads and max non-template function overloads.

    => Favor the normal function call syntax when making calls to a function instantiated from a function template (unless you need the function template version to be preferred over a matching non-template function).

    7. Instantiated functions may not always make sense semantically - The compiler will successfully compile an instantiated function template as long as it makes sense syntactically. However, the compiler does not have any way to check that such a function actually makes sense semantically.

    std::cout << addOne("Hello, world!") << '\n';

    The compiler will instantiate and compile function templates that do not make sense semantically as long as they are syntactically valid. It is your responsibility to make sure you are calling such function templates with arguments that make sense.

    8. We can tell the compiler that instantiation of function templates with certain arguments should be disallowed. This is done by using function template specialization, which allow us to overload an function template for a specific set of template arguments, along with = delete, which tells the compiler that any use of the function should emit a compilation error.

        // Use function template specialization to tell the compiler that addOne(const char*) should emit a compilation error
        // const char* will match a string literal
        template <>
        const char* addOne(const char* x) = delete;

    9. Using function templates in multiple files : 

        Consider the following program, which doesn’t work correctly: 

        - add.cpp:

            template <typename T>
            T addOne(T x) // function template definition
            {
                return x + 1;
            }

        - main.cpp 

            template <typename T>
            T addOne(T x); // function template forward declaration

        If addOne were a non-template function, this program would work fine: In main.cpp, the compiler would be satisfied with the forward declaration of addOne, and the linker would connect the call to addOne() in main.cpp to the function definition in add.cpp. But because addOne is a template, this program doesn’t work, and we get a linker error:

        => error LNK2019: unresolved external symbol "int __cdecl addOne<int>(int)" (??$addOne@H@@YAHH@Z) referenced in function _main

        In main.cpp, we call addOne<int> and addOne<double>. However, since the compiler can’t see the definition for function template addOne, it can’t instantiate those functions inside main.cpp. It does see the forward declaration for addOne though, and will assume those functions exist elsewhere and will be linked in later.

        When the compiler goes to compile add.cpp, it will see the definition for function template addOne. However, there are no uses of this template in add.cpp, so the compiler will not instantiate anything. The end result is that the linker is unable to connect the calls to addOne<int> and addOne<double> in main.cpp to the actual functions, because those functions were never instantiated.

        If add.cpp had instantiated those functions, the program would have compiled and linked just fine. But such solutions are fragile and should be avoided: if the code in add.cpp was later changed so those functions are no longer instantiated, the program would again fail to link. Or if main.cpp called a different version of addOne (such as addOne<float>) that was not instantiated in add.cpp, we run into the same problem.

    10. The most conventional way to address this issue is to put all your template code in a header (.h) file instead of a source (.cpp) file:

        - add.h

            #ifndef ADD_H
            #define ADD_H

            template <typename T>
            T addOne(T x) // function template definition
            {
                return x + 1;
            }

            #endif

        That way, any files that need access to the template can #include the relevant header, and the template definition will be copied by the preprocessor into the source file. The compiler will then be able to instantiate any functions that are needed.

    11. You may be wondering why this doesn’t cause a violation of the one-definition rule (ODR). The ODR says that types, templates, inline functions, and inline variables are allowed to have identical definitions in different files. So there is no problem if the template definition is copied into multiple files (as long as each definition is identical).

    But what about the instantiated functions themselves? If a function is instantiated in multiple files, how does that not cause a violation of the ODR? The answer is that functions implicitly instantiated from templates are implicitly inline. And as you know, inline functions can be defined in multiple files, so long as the definition is identical in each.

    Template definitions are exempt from the part of the one-definition rule that requires only one definition per program, so it is not a problem to have the same template definition #included into multiple source files. And functions implicitly instantiated from function templates are implicitly inline, so they can be defined in multiple files, so long as each definition is identical.

    The templates themselves are not inline, as the concept of inline only applies to variables and functions.

    => Templates that are needed in multiple files should be defined in a header file, and then #included wherever needed. This allows the compiler to see the full template definition and instantiate the template when needed.

    12. Generic programming - 

        Because template types can be replaced with any actual type, template types are sometimes called generic types. And because templates can be written agnostically of specific types, programming with templates is sometimes called generic programming. Whereas C++ typically has a strong focus on types and type checking, in contrast, generic programming lets us focus on the logic of algorithms and design of data structures without having to worry so much about type information.

    13. Use function templates to write generic code that can work with a wide variety of types whenever you have the need.

*/

template <typename T>
T max(T x, T y)
{
    std::cout << "called max<int>(int, int)\n";
    return (x < y) ? y : x;
}

template <typename T>
T addOne(T x)
{
    return x + 1;
}

// Use function template specialization to tell the compiler that addOne(const char*) should emit a compilation error
// const char* will match a string literal
template <>
const char* addOne(const char* x) = delete;


int max(int x, int y)
{
    std::cout << "called max(int, int)\n";
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // calls max<int>(int, int)
    std::cout << max<>(1, 2) << '\n';    // deduces max<int>(int, int) (non-template functions not considered)
    std::cout << max(1, 2) << '\n';      // calls max(int, int)

    // std::cout << addOne("Hello, world!") << '\n'; // not work addOne




    return 0;
}
