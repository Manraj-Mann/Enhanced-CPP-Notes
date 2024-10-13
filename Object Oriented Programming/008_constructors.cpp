#include <iostream>
/* 
    Notes :  
    
    1. Constructors - A constructor is a special member function that is automatically called after a non-aggregate class type object is created.
    
        - When a non-aggregate class type object is defined, the compiler looks to see if it can find an accessible constructor that is a match for the initialization values provided by the caller (if any).

    2. - If an accessible matching constructor is found, memory for the object is allocated, and then the constructor function is called.
       - If no accessible matching constructor can be found, a compilation error will be generated.

    3. Many new programmers are confused about whether constructors create the objects or not. They do not -- the compiler sets up the memory allocation for the object prior to the constructor call. The constructor is then called on the uninitialized object. However, if a matching constructor cannot be found for a set of initializers, the compiler will error. So while constructors don’t create objects, the lack of a matching constructor will prevent creation of an object.

    4. Constructor implicit conversion of arguments - constructor will match any call whose arguments are implicitly convertible.

    5. Constructors should not be const - A constructor needs to be able to initialize the object being constructed -- therefore, a constructor must not be const.

        class Something
        {
        private:
            int m_x{};

        public:
            Something() // constructors must be non-const
            {
                m_x = 5; // okay to modify members in non-const constructor
            }

            int getX() const { return m_x; } // const
        };

        int main()
        {
            const Something s{}; // const object, implicitly invokes (non-const) constructor

            std::cout << s.getX(); // prints 5

            return 0;
        }

        - Normally a non-const member function can’t be invoked on a const object. However, because the constructor is invoked implicitly, a non-const constructor can be invoked on a const object.

    6. Constructors vs setters - Constructors are designed to initialize an entire object at the point of instantiation. Setters are designed to assign a value to a single member of an existing object.

    7. Member initialization via a member initialization list - To have a constructor initialize members, we do so using a member initializer list (often called a “member initialization list”). Do not confuse this with the similarly named “initializer list” that is used to initialize aggregates with a list of values.

        Foo(int x, int y)
        : m_x { x }, m_y { y } // here's our member initialization list
        {
            std::cout << "Foo(" << x << ", " << y << ") constructed\n";
        }

    8. Member initializer list formatting - 

        Foo(int x, int y)
            : m_x { x }
            , m_y { y }
        {
        }

    9. Member initialization order - Because the C++ standard says so, the members in a member initializer list are always initialized in the order in which they are defined inside the class (not in the order they are defined in the member initializer list).

    10. Member initializer list vs default member initializers - 

        Members can be initialized in a few different ways:

        - If a member is listed in the member initializer list, that initialization value is used
        - Otherwise, if the member has a default member initializer, that initialization value is used
        - Otherwise, the member is default initialized.
        
        This means that if a member has both a default member initializer and is listed in the member initializer list for the constructor, the member initializer list value takes precedence.

        class Foo
        {
        private:
            int m_x{};    // default member initializer (will be ignored)
            int m_y{ 2 }; // default member initializer (will be used)
            int m_z;      // no initializer

        public:
            Foo(int x)
                : m_x{ x } // member initializer list
            {
                std::cout << "Foo constructed\n";
            }

            void print() const
            {
                std::cout << "Foo(" << m_x << ", " << m_y << ", " << m_z << ")\n";
            }
        };

    11. Constructor function bodies - The bodies of constructors functions are most often left empty. This is because we primarily use constructor for initialization, which is done via the member initializer list. If that is all we need to do, then we don’t need any statements in the body of the constructor.

    However, because the statements in the body of the constructor execute after the member initializer list has executed, we can add statements to do any other setup tasks required.

        class Foo
        {
        private:
            int m_x{ 0 };
            int m_y{ 1 };

        public:
            Foo(int x, int y)
            {
                m_x = x; // incorrect: this is an assignment, not an initialization
                m_y = y; // incorrect: this is an assignment, not an initialization
            }

            void print() const
            {
                std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
            }
        };

        - Prefer using the member initializer list to initialize your members over assigning values in the body of the constructor.

    12. When constructors fail (a prelude) - 

        In that lesson, we suggested 4 strategies for dealing with such errors:

        Resolve the error within the function.
        
            - Pass the error back to the caller to deal with.
            - Halt the program.
            - Throw an exception.
            - In most cases, we don’t have enough information to resolve such issues entirely within the constructor. So fixing the issue is generally not an option.

        With non-member and non-special member functions, we can pass an error back to the caller to deal with. But constructors have no return value, so we don’t have a good way to do that. In some cases, we can add an isValid() member function (or an overloaded conversion to bool) that returns whether the object is currently in a valid state or not. For example, an isValid() function for Fraction would return true when m_denominator != 0.0. But this means the caller has to remember to actually call the function any time a new Fraction is created. And having semantically invalid objects that are accessible is likely to lead to bugs. So while this is better than nothing, it’s not that great of an option.

        In certain types of programs, we can just halt the entire program and let the user rerun the program with the proper inputs… but in most cases, that’s just not acceptable. So probably not.

        And that leaves throwing an exception. Exceptions abort the construction process entirely, which means the user never gets access to a semantically invalid object. So in most cases, throwing an exception is the best thing to do in these situations.

        If exceptions aren’t possible or desired (either because you’ve decided not to use them or because you haven’t learned about them yet), there is one other reasonable option. Instead of letting the user create the class directly, provide a function that either returns an instance of the class or something that indicates failure.

        - In the following example, our createFraction() function returns a std::optional<Fraction> that optionally contains a valid Fraction. If it does, then we can use that Fraction. If not, then the caller can detect that and deal with it. We cover std::optional

            class Fraction
            {
            private:
                int m_numerator { 0 };
                int m_denominator { 1 };

                // private constructor can't be called by public
                Fraction(int numerator, int denominator):
                    m_numerator { numerator }, m_denominator { denominator }
                {
                }

            public:
                // Allow this function to access private members
                friend std::optional<Fraction> createFraction(int numerator, int denominator);
            };

            std::optional<Fraction> createFraction(int numerator, int denominator)
            {
                if (denominator == 0.0)
                    return {};

                return Fraction{numerator, denominator};
            }



*/

class Something
{
private:
    int m_x{};

public:
    Something() // constructors must be non-const
    {
        m_x = 5; // okay to modify members in non-const constructor
    }

    int getX() const { return m_x; } // const
};

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y)
        : m_x { x }, m_y { y } // here's our member initialization list
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};


int main()
{
    const Something s{}; // const object, implicitly invokes (non-const) constructor

    std::cout << s.getX(); // prints 5

    return 0;
}