#include <iostream>
/* 
    Notes :  

    * Note : " Use -fno-elide-constructors while compiling to disable copy elision "
    
    1. The copy constructor - A copy constructor is a constructor that is used to initialize an object with an existing object of the same type. After the copy constructor executes, the newly created object should be a copy of the object passed in as the initializer.

        class Fraction
        {
        private:
            int m_numerator{ 0 };
            int m_denominator{ 1 };

        public:
            // Default constructor
            Fraction(int numerator=0, int denominator=1)
                : m_numerator{numerator}, m_denominator{denominator}
            {
            }

            void print() const
            {
                std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
            }
        };

        int main()
        {
            Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
            Fraction fCopy { f }; // What constructor is used here?

            f.print();
            fCopy.print();

            return 0;
        }

    2. An implicit copy constructor - If you do not provide a copy constructor for your classes, C++ will create a public implicit copy constructor for you. In the above example, the statement Fraction fCopy { f }; is invoking the implicit copy constructor to initialize fCopy with f. By default, the implicit copy constructor will do memberwise initialization. This means each member will be initialized using the corresponding member of the class passed in as the initializer. In the example above, fCopy.m_numerator is initialized using f.m_numerator (which has value 5), and fCopy.m_denominator is initialized using f.m_denominator (which has value 3).

    3. Defining your own copy constructor - 

        class Fraction
        {
        private:
            int m_numerator{ 0 };
            int m_denominator{ 1 };

        public:
            // Default constructor
            Fraction(int numerator=0, int denominator=1)
                : m_numerator{numerator}, m_denominator{denominator}
            {
            }

            // Copy constructor
            Fraction(const Fraction& fraction)
                // Initialize our members using the corresponding member of the parameter
                : m_numerator{ fraction.m_numerator }
                , m_denominator{ fraction.m_denominator }
            {
                std::cout << "Copy constructor called\n"; // just to prove it works
            }

            void print() const
            {
                std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
            }
        };

        - The copy constructor we defined above is functionally equivalent to the one we’d get by default, except we’ve added an output statement to prove the copy constructor is actually being called. This copy constructor is invoked when fCopy is initialized with f.

        - A copy constructor should not do anything other than copy an object. This is because the compiler may optimize the copy constructor out in certain cases. If you are relying on the copy constructor for some behavior other than just copying, that behavior may or may not occur. 

    4. Prefer the implicit copy constructor - Unlike the implicit default constructor, which does nothing (and thus is rarely what we want), the memberwise initialization performed by the implicit copy constructor is usually exactly what we want. Therefore, in most cases, using the implicit copy constructor is perfectly fine.

    5. The copy constructor’s parameter must be a reference - It is a requirement that the parameter of a copy constructor be an lvalue reference or const lvalue reference. Because the copy constructor should not be modifying the parameter, using a const lvalue reference is preferred.

    6. Pass by value and the copy constructor - When an object is passed by value, the argument is copied into the parameter. When the argument and parameter are the same class type, the copy is made by implicitly invoking the copy constructor.

        class Fraction
        {
        private:
            int m_numerator{ 0 };
            int m_denominator{ 1 };

        public:
            // Default constructor
            Fraction(int numerator = 0, int denominator = 1)
                : m_numerator{ numerator }, m_denominator{ denominator }
            {
            }

            // Copy constructor
            Fraction(const Fraction& fraction)
                : m_numerator{ fraction.m_numerator }
                , m_denominator{ fraction.m_denominator }
            {
                std::cout << "Copy constructor called\n";
            }

            void print() const
            {
                std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
            }
        };

    7. Return by value and the copy constructor - We noted that return by value creates a temporary object (holding a copy of the return value) that is passed back to the caller. When the return type and the return value are the same class type, the temporary object is initialized by implicitly invoking the copy constructor.

        class Fraction
        {
        private:
            int m_numerator{ 0 };
            int m_denominator{ 1 };

        public:
            // Default constructor
            Fraction(int numerator = 0, int denominator = 1)
                : m_numerator{ numerator }, m_denominator{ denominator }
            {
            }

            // Copy constructor
            Fraction(const Fraction& fraction)
                : m_numerator{ fraction.m_numerator }
                , m_denominator{ fraction.m_denominator }
            {
                std::cout << "Copy constructor called\n";
            }

            void print() const
            {
                std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
            }
        };

        void printFraction(Fraction f) // f is pass by value
        {
            f.print();
        }

        Fraction generateFraction(int n, int d)
        {
            Fraction f{ n, d };
            return f;
        }

        When generateFraction returns a Fraction back to main, a temporary Fraction object is created and initialized using the copy constructor.

        Because this temporary is used to initialize Fraction f2, this invokes the copy constructor again to copy the temporary into f2.

        And when f2 is passed to printFraction(), the copy constructor is called a third time.

        Thus, on the author’s machine, this example prints:

            Copy constructor called
            Copy constructor called
            Copy constructor called
            Fraction(1, 2)

        - If you compile and execute the above example, you may find that only two calls to the copy constructor occur. This is a compiler optimization known as copy elision.

    8. Using = default to generate a default copy constructor - If a class has no copy constructor, the compiler will implicitly generate one for us. If we prefer, we can explicitly request the compiler create a default copy constructor for us using the = default syntax:

        // Explicitly request default copy constructor
        Fraction(const Fraction& fraction) = default;

    9. Using = delete to prevent copies - Occasionally we run into cases where we do not want objects of a certain class to be copyable. We can prevent this by marking the copy constructor function as deleted, using the = delete syntax:

        // Delete the copy constructor so no copies can be made
        Fraction(const Fraction& fraction) = delete;

        - You can also prevent the public from making copies of class object by making the copy constructor private (as private functions can’t be called by the public). However, a private copy constructor can still be called from other members of the class, so this solution is not advised unless that is desired.

        - The rule of three is a well known C++ principle that states that if a class requires a user-defined copy constructor, destructor, or copy assignment operator, then it probably requires all three. In C++11, this was expanded to the rule of five, which adds the move constructor and move assignment operator to the list.

        - Not following the rule of three/rule of five is likely to lead to malfunctioning code. We’ll revisit the rule of three and rule of five when we cover dynamic memory allocation.

*/

class Fraction
{
    private:
        int m_numerator{ 0 };
        int m_denominator{ 1 };

    public:
        // Default constructor
        Fraction(int numerator = 0, int denominator = 1)
            : m_numerator{ numerator }, m_denominator{ denominator }
        {
        }

        // Copy constructor
        Fraction(const Fraction& fraction)
            : m_numerator{ fraction.m_numerator }
            , m_denominator{ fraction.m_denominator }
        {
            std::cout << "Copy constructor called\n";
        }

        void print() const
        {
            std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
        }
};

void printFraction(Fraction f) // f is pass by value
{
    f.print();
}

Fraction generateFraction(int n, int d)
{
    Fraction f{ n, d };
    return f;
}
int main()
{
    Fraction f2 { generateFraction(1, 2) }; // Fraction is returned using copy constructor

    printFraction(f2); // f2 is copied into the function parameter using copy constructor

    return 0;
}