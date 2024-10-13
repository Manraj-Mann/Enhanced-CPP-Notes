#include <iostream>
/* 
    Notes :  
    
    1. Temporary class objects - A temporary object (sometimes called an anonymous object or an unnamed object) is an object that has no name and exists only for the duration of a single expression.

    There are two common ways to create temporary class type objects:

        class IntPair
        {
        private:
            int m_x{};
            int m_y{};

        public:
            IntPair(int x, int y)
                : m_x { x }, m_y { y }
            {}

            int x() const { return m_x; }
            int y() const{ return m_y; }
        };

        void print(IntPair p)
        {
            std::cout << "(" << p.x() << ", " << p.y() << ")\n";
        }

        int main()
        {
            // Case 1: Pass variable
            IntPair p { 3, 4 };
            print(p);

            // Case 2: Construct temporary IntPair and pass to function
            print(IntPair { 5, 6 } );

            // Case 3: Implicitly convert { 7, 8 } to a temporary Intpair and pass to function
            print( { 7, 8 } );

            return 0;
        }
        
        In case 2, we’re telling the compiler to construct an IntPair object, and initializing it with { 5, 6 }. Because this object has no name, it is a temporary. The temporary object is then passed to parameter p of function print(). When the function call returns, the temporary object is destroyed.

        In case 3, we’re also creating a temporary IntPair object to pass to function print(). However, because we have not explicitly specified what type to construct, the compiler will deduce the necessary type (IntPair) from the function parameter, and then implicitly convert { 7, 8 } to an IntPair object.

        To summarize:

        IntPair p { 1, 2 }; // create named object p initialized with value { 1, 2 }
        IntPair { 1, 2 };   // create temporary object initialized with value { 1, 2 }
        { 1, 2 };           // compiler will try to convert value { 1, 2 } to temporary object matching parameter type



    2. Temporary objects and return by value : 

        When a function returns by value, the object that is returned is a temporary object (initialized using the value or object identified in the return statement).

        Here are some examples:

        class IntPair
        {
        private:
            int m_x{};
            int m_y{};

        public:
            IntPair(int x, int y)
                : m_x { x }, m_y { y }
            {}

            int x() const { return m_x; }
            int y() const { return m_y; }
        };

        void print(IntPair p)
        {
            std::cout << "(" << p.x() << ", " << p.y() << ")\n";
        }

        // Case 1: Create named variable and return
        IntPair ret1()
        {
            IntPair p { 3, 4 };
            return p; // returns temporary object (initialized using p)
        }

        // Case 2: Create temporary IntPair and return
        IntPair ret2()
        {
            return IntPair { 5, 6 }; // returns temporary object (initialized using another temporary object)
        }

        // Case 3: implicitly convert { 7, 8 } to IntPair and return
        IntPair ret3()
        {
            return { 7, 8 }; // returns temporary object (initialized using another temporary object)
        }

        int main()
        {
            print(ret1());
            print(ret2());
            print(ret3());

            return 0;
        }

        In case 1, when we return p, a temporary object is created and initialized using p.


    3. A few notes : 

        - First, just as in the case of an int, when used in an expression, a temporary class object is an rvalue. Thus, such objects can only be used where rvalue expressions are accepted.

        - Second, temporary objects are created at the point of definition, and destroyed at the end of the full expression in which they are defined . A full expression is an expression that is not a subexpression.

    4. static_cast vs explicit instantiation of a temporary object : 

            char c { 'a' };

            std::cout << static_cast<int>( c ) << '\n'; // static_cast returns a temporary int direct-initialized with value of c
            std::cout << int { c } << '\n';             // explicitly creates a temporary int list-initialized with value c

        static_cast<int>(c) returns a temporary int that is direct-initialized with the value of c. int { c } creates a temporary int that is list-initialized with the value of c. Either way, we get a temporary int initialized with the value of c, which is what we want.

           std::string_view sv { "Hello" };
        

        void printString(const std::string &s)
        {
            std::cout << s << '\n';
        }

        // We want to print sv using the printString() function

        //    printString(sv); // compile error: a std::string_view won't implicitly convert to a std::string

        printString( static_cast<std::string>(sv) ); // Case 1: static_cast returns a temporary std::string direct-initialized with sv
        printString( std::string { sv } );           // Case 2: explicitly creates a temporary std::string list-initialized with sv
        printString( std::string ( sv ) );           // Case 3: C-style cast returns temporary std::string direct-initialized with sv (avoid this one!)

        In case 1, static_cast<std::string>(sv) invokes the static_cast operator to cast sv to a std::string. This returns a temporary std::string that has been direct-initialized using sv, which is then used as the argument for the function call.

        In case 2, std::string { sv } creates a temporary std::string that is list-initialized using sv. Since this is an explicit construction, the conversion is allowed. This temporary is then used as the argument for the function call.

        In case 3, std::string ( sv ) use a C-style cast to cast sv to a std::string. Although this works here, C-style casting can be dangerous in general and should be avoided. Notice how similar this looks to the prior case!

    5. Best practice

        As a quick rule of thumb: Prefer static_cast when converting to a fundamental type, and a list-initialized temporary when converting to a class type.

        Prefer static_cast when to create a temporary object when any of the following are true:

            - We need to performing a narrowing conversion.
            - We want to make it really obvious that we’re converting to a type that will result in some different behavior (e.g. a char to an int).
            - We want to use direct-initialization for some reason (e.g. to avoid list constructors taking precedence).
        
        Prefer creating a new object (using list initialization) to create a temporary object when any of the following are true:

            - We want to use list-initialization (e.g. for the protection against narrowing conversions, or because we need to invoke a list constructor).
            - We need to provide additional arguments to a constructor to facilitate the conversion.


*/
int main()
{
    return 0;
}