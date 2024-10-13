#include <iostream>
/* 
    Notes : Class initialization and copy elision

    **Note : -fno-elide-constructors use this flag to disable copy elision.
    
    1. We discuss 6 basic types of initialization for objects with fundamental types:

        int a;         // no initializer (default initialization)
        int b = 5;     // initializer after equals sign (copy initialization)
        int c( 6 );    // initializer in parentheses (direct initialization)

        // List initialization methods (C++11)
        int d { 7 };   // initializer in braces (direct list initialization)
        int e = { 8 }; // initializer in braces after equals sign (copy list initialization)
        int f {};      // initializer is empty braces (value initialization)

    2. Key insight:

        There are three key differences between the initialization forms:

        - List initialization disallows narrowing conversions.
        - Copy initialization only considers non-explicit constructors/conversion functions.
        - List initialization prioritizes matching list constructors over other matching constructors. 

    3. Unnecessary copies : 

            class Something
            {
                int m_x{};

            public:
                Something(int x)
                    : m_x{ x }
                {
                    std::cout << "Normal constructor\n";
                }

                Something(const Something& s)
                    : m_x { s.m_x }
                {
                    std::cout << "Copy constructor\n";
                }

                void print() const { std::cout << "Something(" << m_x << ")\n"; }
            };

            - In the initialization of variable s above, we first construct a temporary Something, initialized with value 5 (which uses the Something(int) constructor). This temporary is then used to initialize s. Because the temporary and s have the same type (they are both Something objects), the Something(const Something&) copy constructor would normally be called here to copy the values in the temporary into s. The end result is that s is initialized with value 5.

            - Without any optimizations, the above program would print:

                Normal constructor
                Copy constructor
                Something(5)

    4. Copy elision - Since the compiler is free to rewrite statements to optimize them, one might wonder if the compiler can optimize away the unnecessary copy and treat Something s { Something{5} }; as if we had written Something s { 5 } in the first place.

        => "The answer is yes, and the process of doing so is called copy elision. Copy elision is a compiler optimization technique that allows the compiler to remove unnecessary copying of objects. In other words, in cases where the compiler would normally call a copy constructor, the compiler is free to rewrite the code to avoid the call to the copy constructor altogether. When the compiler optimizes away a call to the copy constructor, we say the constructor has been elided"

        => Unlike other types of optimization, copy elision is exempt from the “as-if” rule. That is, copy elision is allowed to elide the copy constructor even if the copy constructor has side effects (such as printing text to the console)! This is why copy constructors should not have side effects other than copying -- if the compiler elides the call to the copy constructor, the side effects won’t execute, and the observable behavior of the program will change!

    5. Copy elision in pass by value and return by value - 

        - The copy constructor is normally called when an argument of the same type as the parameter is passed by value or return by value is used. However, in certain cases, these copies may be elided. The following program demonstrates some of these cases:

            class Something
            {
            public:
                Something() = default;
                Something(const Something&)
                {
                    std::cout << "Copy constructor called\n";
                }
            };

            Something rvo()
            {
                return Something{}; // calls Something() and copy constructor
            }

            Something nrvo()
            {
                Something s{}; // calls Something()
                return s;      // calls copy constructor
            }

            int main()
            {
                std::cout << "Initializing s1\n";
                Something s1 { rvo() }; // calls copy constructor

                std::cout << "Initializing s2\n";
                Something s2 { nrvo() }; // calls copy constructor

                    return 0;
            }

        - In C++14 or older, with copy elision disabled, the above program would call the copy constructor 4 times:

            - Once when rvo returns Something to main.
            - Once when the return value of rvo() is used to initialize s1.
            - Once when nrvo returns s to main.
            - Once when the return value of nrvo() is used to initialize s2.

        - However, due to copy elision, it’s likely that your compiler will elide most or all of these copy constructor calls. Visual Studio 2022 elides 3 cases (it doesn’t elide the case where nrvo() returns by value), and GCC elides all 4.

    6. Mandatory copy elision in C++17 - 

        - Prior to C++17, copy elision was strictly an optional optimization that compilers could make. In C++17, copy elision became mandatory in some cases. In these cases, copy elision will be performed automatically (even if you tell your compiler not to perform copy elision).

        - Running the same example as above in C++17 or newer, the copy constructor calls that would otherwise occur when rvo() returns and when s1 is initialized with that value are required to be elided. The initialization of s2 with nvro() is not a mandatory elision case, and thus the 2 copy constructor calls that occur here may or may not be elided depending on your compiler and optimization settings.

        - In optional elision cases, an accessible copy constructor must be available (e.g. not deleted), even if the actual call to the copy constructor is elided.

        - In mandatory elision cases, an accessible copy constructor need not be available (in other words, mandatory elision can happen even if the copy constructor is deleted).

*/


class Foo
{
public:

    // Default constructor
    Foo()
    {
        std::cout << "Foo()\n";
    }

    // Normal constructor
    Foo(int x)
    {
        std::cout << "Foo(int) " << x << '\n';
    }

    // Copy constructor
    Foo(const Foo&)
    {
        std::cout << "Foo(const Foo&)\n";
    }
};


class Something
{
public:
	Something() = default;
	Something(const Something&)
	{
		std::cout << "Copy constructor called\n";
	}
};

Something rvo()
{
	return Something{}; // calls Something() and copy constructor
}

Something nrvo()
{
	Something s{}; // calls Something()
	return s;      // calls copy constructor
}

int main()
{
    // Calls Foo() default constructor
    Foo f1;           // default initialization
    Foo f2{};         // value initialization (preferred)

    // Calls foo(int) normal constructor
    Foo f3 = 3;       // copy initialization (non-explicit constructors only)
    Foo f4(4);        // direct initialization
    Foo f5{ 5 };      // direct list initialization (preferred)
    Foo f6 = { 6 };   // copy list initialization (non-explicit constructors only)

    // Calls foo(const Foo&) copy constructor
    Foo f7 = f3;      // copy initialization
    Foo f8(f3);       // direct initialization
    Foo f9{ f3 };     // direct list initialization (preferred)
    Foo f10 = { f3 }; // copy list initialization


    std::cout << "Initializing s1\n";
	Something s1 { rvo() }; // calls copy constructor

	std::cout << "Initializing s2\n";
	Something s2 { nrvo() }; // calls copy constructor


    return 0;
}