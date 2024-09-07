#include <iostream>


/*
    Notes : 

    1. The properties of an expression - To help determine how expressions should evaluate and where they can be used, all expressions in C++ have two properties: a type and a value category.

    2. Type : The type of an expression is equivalent to the type of the value, object, or function that results from the evaluated expression. 

    3. Note that the type of an expression must be determinable at compile time (otherwise type checking and type deduction wouldn’t work) -- however, the value of an expression may be determined at either compile time (if the expression is constexpr) or runtime (if the expression is not constexpr).

    4. Why error : 

        - x = 5; // valid: we can assign 5 to x
        - 5 = x; // error: can not assign value of x to literal value 5

        - The answer lies in the second property of expressions: the value category. The value category of an expression (or subexpression) indicates whether an expression resolves to a value, a function, or an object of some kind.

    5. Prior to C++11, there were only two possible value categories: lvalue and rvalue. In C++11, three additional value categories (glvalue, prvalue, and xvalue) were added to support a new feature called move semantics.

    6. l-value : is an expression that evaluates to an identifiable object or function (or bit-field).The term “identity” is used by the C++ standard, but is not well-defined. An entity (such as an object or function) that has an identity can be differentiated from other similar entities (typically by comparing the addresses of the entity).Entities with identities can be accessed via an identifier, reference, or pointer, and typically have a lifetime longer than a single expression or statement.

    Example : 

        - int x { 5 };
        - int y { x }; // x is an lvalue expression

    In the above program, the expression x is an lvalue expression as it evaluates to variable x (which has an identifier).

    => Since the introduction of constants into the language, lvalues come in two subtypes: a modifiable lvalue is an lvalue whose value can be modified. A non-modifiable lvalue is an lvalue whose value can’t be modified (because the lvalue is const or constexpr).

    Example : 

        - int y { x }; // x is a modifiable lvalue expression
        - const double e { d }; // d is a non-modifiable lvalue expression

    7. r-value : is an expression that is not an lvalue. Rvalue expressions evaluate to a value. Commonly seen rvalues include literals (except C-style string literals, which are lvalues) and the return value of functions and operators that return by value. Rvalues aren’t identifiable (meaning they have to be used immediately), and only exist within the scope of the expression in which they are used.

    Example : 

            - int x{ 5 }; // 5 is an rvalue expression
            - const double d{ 1.2 }; // 1.2 is an rvalue expression

            - int y { x }; // x is a modifiable lvalue expression
            - const double e { d }; // d is a non-modifiable lvalue expression
            - int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)

            - int w { x + 1 }; // x + 1 is an rvalue expression
            - int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression

    8. Key insight : 

        - L value expressions evaluate to an identifiable object.
        - R value expressions evaluate to a value.

        In C++11, rvalues are broken into two subtypes: prvalues and xvalues, so the rvalues we’re talking about here are the sum of both of those categories.

    9. Tip - If you’re not sure whether an expression is an lvalue or rvalue, try taking its address using operator&, which requires its operand to be an lvalue. If &(expression); compiles, expression must be an lvalue:

        int x { 5 };
        &x; // compiles: x is an lvalue expression
        &5; // doesn't compile: 5 is an rvalue expression
        &foo(); // doesn't compile: foo() is an rvalue expression

    A C-style string literal is an lvalue because C-style strings (which are C-style arrays) decay to a pointer. The decay process only works if the array is an lvalue (and thus has an address that can be stored in the pointer). C++ inherited this for backwards compatibility.

    Example : 

        std::cout<<"Address : ";
        std::cout<<&"hello"<<std::endl;


    10. Lvalue to rvalue conversion - 

        int x { 5 };
        int y { x }; // x is an lvalue expression

        If x is an lvalue expression that evaluates to variable x, then how does y end up with value 5?

        - The answer is that lvalue expressions will implicitly convert to rvalue expressions in contexts where an rvalue is expected but an lvalue is provided. The initializer for an int variable is expected to be an rvalue expression. Thus lvalue expression x undergoes an lvalue-to-rvalue conversion, which evaluates to value 5, which is then used to initialize y.

        int x{ 1 };
        int y{ 2 };

        x = y; // y is a modifiable lvalue, not an rvalue, but this is legal

        - In this case, y is an lvalue expression, but it undergoes an lvalue-to-rvalue conversion, which evaluates to the value of y (2), which is then assigned to x.

    11. A rule of thumb to identify lvalue and rvalue expressions:

        => Lvalue expressions are those that evaluate to functions or identifiable objects (including variables) that persist beyond the end of the expression.
        
        => Rvalue expressions are those that evaluate to values, including literals and temporary objects that do not persist beyond the end of the expression.

*/

int main()
{   
    std::cout<<"Address : ";
    std::cout<<&"hello"<<std::endl;

    return 0;
}