/*
Notes:

1. A constant is a value that may not be changed during the program’s execution. C++ supports two types of constants: named constants, and literals.

2. A named constant is a constant value that is associated with an identifier. A Literal constant is a constant value not associated with an identifier.

3. A variable whose value can not be changed is called a constant variable. The const keyword can be used to make a variable constant. Constant variables must be initialized. Avoid using const when passing by value or returning by value.

4. A type qualifier is a keyword that is applied to a type that modifies how that type behaves. As of C++23, C++ only supports const and volatile as type qualifiers.

5. A constant expression is an expression that can be evaluated at compile-time. An expression that is not a constant expression is sometimes called a runtime expression.

6. A compile-time constant is a constant whose value is known at compile-time. A runtime constant is a constant whose initialization value isn’t known until runtime.

7. A constexpr variable must be a compile-time constant, and initialized with a constant expression. Function parameters cannot be constexpr.

8. Literals are values inserted directly into the code. Literals have types, and literal suffixes can be used to change the type of a literal from the default type.

9. A magic number is a literal (usually a number) that either has an unclear meaning or may need to be changed later. Don’t use magic numbers in your code. Instead, use symbolic constants.

10. The conditional operator (?:) (also sometimes called the arithmetic if operator) is a ternary operator (an operator that takes 3 operands). Given a conditional operation of the form c ? x : y, if conditional c evaluates to true then x will be evaluated, otherwise y will be evaluated. The conditional operator typically needs to be parenthesized as follows:

    1. Parenthesize the entire conditional operator when used in a compound expression (an expression with other operators).
    
    2. For readability, parenthesize the condition if it contains any operators (other than the function call operator).

11. Inline expansion is a process where a function call is replaced by the code from the called function’s definition. A function that is declared using the inline keyword is called an inline function.

    Inline functions and variables have two primary requirements:

    1. The compiler needs to be able to see the full definition of an inline function or variable in each translation unit where the function is used (a forward declaration will not suffice on its own). The definition can occur after the point of use if a forward declaration is also provided.

    2. Every definition for an inline function or variable must be identical, otherwise undefined behavior will result.

    In modern C++, the term inline has evolved to mean “multiple definitions are allowed”. Thus, an inline function is one that is allowed to be defined in multiple files. C++17 introduced inline variables, which are variables that are allowed to be defined in multiple files.

    Inline functions and variables are particularly useful for header-only libraries, which are one or more header files that implement some capability (no .cpp files are included).


12. A constexpr function is a function whose return value may be computed at compile-time. To make a function a constexpr function, we simply use the constexpr keyword in front of the return type. Constexpr functions are only guaranteed to be evaluated at compile-time when used in a context that requires a constant expression. Otherwise they may be evaluated at compile-time (if eligible) or runtime.

13. A consteval function is a function that must evaluate at compile-time.
    Constexpr functions and consteval functions are implicitly inline.

14. A string is a collection of sequential characters that is used to represent text (such as names, words, and sentences). String literals are always placed between double quotes. String literals in C++ are C-style strings, which have a strange type that is hard to work with.
    std::string offers an easy and safe way to deal with text strings. std::string lives in the <string> header. std::string is expensive to initialize (or assign to) and copy.

15. std::string_view provides read-only access to an existing string (a C-style string literal, a std::string, or a char array) without making a copy. A std::string_view that is viewing a string that has been destroyed is sometimes called a dangling view. When a std::string is modified, all views into that std::string are invalidated, meaning those views are now invalid. Using an invalidated view (other than to revalidate it) will produce undefined behavior.

    Because C-style string literals exist for the entire program, it is okay to set a std::string_view to a C-style string literal, and even return such a std::string_view from a function.

16. A substring is a contiguous sequence of characters within an existing string.

*/