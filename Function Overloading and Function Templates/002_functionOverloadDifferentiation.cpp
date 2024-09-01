#include <iostream>

/*
    Notes : 

    1. How overloaded functions are differentiated - 

    => Number of parameters 	-> Used of Differentiation [ Yes ].	
    => Type of parameters	    -> Used of Differentiation [ Yes ]. { Excludes typedefs, type aliases, and const qualifier on value parameters. Includes ellipses. }
    => Return Type              -> Not used.

    2. For member functions, additional function-level qualifiers are also considered:

        Function-level qualifier	Used for overloading
        1. const or volatile	         Yes
        2. Ref-qualifiers	              Yes
        
        As an example, a const member function can be differentiated from an otherwise identical non-const member function (even if they share the same set of parameters).

    3. "Overloading based on number of parameters" - An overloaded function is differentiated so long as each overloaded function has a different number of parameters. For example:

        int add(int x, int y)
        {
            return x + y;
        }

        int add(int x, int y, int z)
        {
            return x + y + z;
        }
        
        The compiler can easily tell that a function call with two integer parameters should go to add(int, int) and a function call with three integer parameters should go to add(int, int, int).

    4. "Overloading based on type of parameters" - 

        A function can also be differentiated so long as each overloaded function’s list of parameter types is distinct. For example, all of the following overloads are differentiated:

        - int add(int x, int y); // integer version
        - double add(double x, double y); // floating point version
        - double add(int x, double y); // mixed version
        - double add(double x, int y); // mixed version

    5. The use of typedef's will not differentiate : 

        typedef int Height; // typedef
        using Age = int; // type alias

        void print(int value);
        void print(Age value); // not differentiated from print(int)
        void print(Height value); // not differentiated from print(int)

    6. For parameters passed by value, the const qualifier is also not considered. Therefore, the following functions are not considered to be differentiated:

        void print(int);
        void print(const int); // not differentiated from print(int)

    7. We haven’t covered ellipsis yet, but ellipsis parameters are considered to be a unique type of parameter:

        - void foo(int x, int y);
        - void foo(int x, ...); // differentiated from foo(int, int)
        
        Thus a call to foo(4, 5) will match to foo(int, int), not foo(int, ...).

    8. The return type of a function is not considered for differentiation - 

        A function’s return type is not considered when differentiating overloaded functions.

        This was an intentional choice, as it ensures the behavior of a function call can be determined independently from the rest of the expression, making understanding complex expressions much simpler. Put another way, we can always determine which version of a function will be called based solely on the arguments in the function call. If return values were used for differentiation, then we wouldn’t have an easy syntactic way to tell which overload of a function was being called -- we’d also have to understand how the return value was being used, which requires a lot more analysis.


    9. Type signature

        A function’s type signature (generally called a signature) is defined as the parts of the function header that are used for differentiation of the function. In C++, this includes the function name, number of parameters, parameter type, and function-level qualifiers. It notably does not include the return type.

*/

class MyClass {
public:
    // Non-const member function
    void show() {
        std::cout << "Non-const show()" << std::endl;
    }

    // Const member function
    void show() const {
        std::cout << "Const show()" << std::endl;
    }
};


int add(int x, int y)
{
    return x + y;
}

int add(int x, int y, int z)
{
    return x + y + z;
}


// typedef int Height; // typedef
// using Age = int; // type alias

// void print(int value);
// void print(Age value); // not differentiated from print(int)
// void print(Height value); // not differentiated from print(int)

int main() {

    MyClass obj;
    const MyClass constObj;

    // Calls the non-const version
    obj.show();

    // Calls the const version
    constObj.show();

    std::cout<<"Add function call"<<std::endl;
    std::cout<<"add - "<<add(1 , 2)<<std::endl;


    return 0;
}