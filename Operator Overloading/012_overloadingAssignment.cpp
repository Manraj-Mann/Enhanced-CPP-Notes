#include <iostream>
/* 
    Notes :  
    
    1. The copy assignment operator (operator=) is used to copy values from one object to another already existing object.

    2. Copy assignment vs Copy constructor :  The purpose of the copy constructor and the copy assignment operator are almost equivalent -- both copy one object to another. However, the copy constructor initializes new objects, whereas the assignment operator replaces the contents of existing objects.

    3. Overloading the assignment operator :  Overloading the copy assignment operator (operator=) is fairly straightforward, with one specific caveat that we’ll get to. The copy assignment operator must be overloaded as a member function.

        Example : 

            class Fraction
            {
            private:
                int m_numerator { 0 };
                int m_denominator { 1 };

            public:
                // Default constructor
                Fraction(int numerator = 0, int denominator = 1 )
                    : m_numerator { numerator }, m_denominator { denominator }
                {
                    assert(denominator != 0);
                }

                // Copy constructor
                Fraction(const Fraction& copy)
                    : m_numerator { copy.m_numerator }, m_denominator { copy.m_denominator }
                {
                    // no need to check for a denominator of 0 here since copy must already be a valid Fraction
                    std::cout << "Copy constructor called\n"; // just to prove it works
                }

                // Overloaded assignment
                Fraction& operator= (const Fraction& fraction);

                friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);

            };

            std::ostream& operator<<(std::ostream& out, const Fraction& f1)
            {
                out << f1.m_numerator << '/' << f1.m_denominator;
                return out;
            }

            // A simplistic implementation of operator= (see better implementation below)
            Fraction& Fraction::operator= (const Fraction& fraction)
            {
                // do the copy
                m_numerator = fraction.m_numerator;
                m_denominator = fraction.m_denominator;

                // return the existing object so we can chain this operator
                return *this;
            }

            int main()
            {
                Fraction fiveThirds { 5, 3 };
                Fraction f;
                f = fiveThirds; // calls overloaded assignment
                std::cout << f;

                return 0;
            }

    4. Issues due to self-assignment : In this particular example, the self-assignment causes each member to be assigned to itself, which has no overall impact, other than wasting time. In most cases, a self-assignment doesn’t need to do anything at all! However, in cases where an assignment operator needs to dynamically assign memory, self-assignment can actually be dangerous.

    5. Detecting and handling self-assignment : Fortunately, we can detect when self-assignment occurs. By checking if the address of our implicit object is the same as the address of the object being passed in as a parameter, we can have our assignment operator just return immediately without doing any other work. Because this is just a pointer comparison, it should be fast, and does not require operator== to be overloaded.

        Example: 

        // self-assignment check
        if (this == &object)
            return *this;

    6. When not to handle self-assignment : Typically the self-assignment check is skipped for copy constructors. Because the object being copy constructed is newly created, the only case where the newly created object can be equal to the object being copied is when you try to initialize a newly defined object with itself. Second, the self-assignment check may be omitted in classes that can naturally handle self-assignment. 

    7. The copy and swap idiom : A better way to handle self-assignment issues is via what’s called the copy and swap idiom. 

        - Any class that manages a resource (a wrapper, like a smart pointer) needs to implement The Big Three. While the goals and implementation of the copy-constructor and destructor are straightforward, the copy-assignment operator is arguably the most nuanced and difficult.

        - The copy-and-swap idiom is the solution, and elegantly assists the assignment operator in achieving two things: avoiding code duplication, and providing a strong exception guarantee.

        - Conceptually, it works by using the copy-constructor's functionality to create a local copy of the data, then takes the copied data with a swap function, swapping the old data with the new data. The temporary copy then destructs, taking the old data with it. We are left with a copy of the new data. In order to use the copy-and-swap idiom, we need three things: a working copy-constructor, a working destructor (both are the basis of any wrapper, so should be complete anyway), and a swap function.

        - A swap function is a non-throwing function that swaps two objects of a class, member for member. We might be tempted to use std::swap instead of providing our own, but this would be impossible; std::swap uses the copy-constructor and copy-assignment operator within its implementation, and we'd ultimately be trying to define the assignment operator in terms of itself!

    8. The implicit copy assignment operator : Unlike other operators, the compiler will provide an implicit public copy assignment operator for your class if you do not provide a user-defined one. This assignment operator does memberwise assignment (which is essentially the same as the memberwise initialization that default copy constructors do).


*/

class Point
{
    private:

        int _x{};
        int _y{};
        int _z{};

    public:


        Point operator=(Point &p)
        {
            if(this == &p)
            {
                return *this;
            }

            this->_x = p._x;
            this->_y = p._y;
            this->_z = p._z;

            return *this;
        }

        Point(int x, int y , int z) : _x(x) , _y(y) , _z(z){}

        friend std::ostream& operator<<(std::ostream &out , const Point &p)
        {
            out<<"Point ( "<<p._x<<" , "<<p._y<<" , "<<p._z<<" ) ";
            return out;
        }

};

int main()
{
    Point p{1 , 2 , 4};

    std::cout<<p<<std::endl;

    Point p1 = p;

    std::cout<<p1<<std::endl;

    Point p2{3 ,4 ,5};

    p2 = p;

    std::cout<<p2<<std::endl;




    return 0;
}