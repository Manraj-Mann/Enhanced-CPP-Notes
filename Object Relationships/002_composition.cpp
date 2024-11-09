#include <iostream>

/*

    Notes : 

    1. Object composition : This process of building complex objects from simpler ones is called object composition.  When we build classes with data members, we’re essentially constructing a complex object from simpler parts, which is object composition. For this reason, structs and classes are sometimes referred to as composite types.

    2. Types of object composition : There are two basic subtypes of object composition: composition and aggregation. 

    3. Composition : 

        - To qualify as a composition, an object and a part must have the following relationship:

            - The part (member) is part of the object (class)
            - The part (member) can only belong to one object (class) at a time
            - The part (member) has its existence managed by the object (class)
            - The part (member) does not know about the existence of the object (class)

        - In a composition relationship, the object is responsible for the existence of the parts. Most often, this means the part is created when the object is created, and destroyed when the object is destroyed. But more broadly, it means the object manages the part’s lifetime in such a way that the user of the object does not need to get involved. For example, when a body is created, the heart is created too. When a person’s body is destroyed, their heart is destroyed too. Because of this, composition is sometimes called a “death relationship”.

        - And finally, the part doesn’t know about the existence of the whole. Your heart operates blissfully unaware that it is part of a larger structure. We call this a unidirectional relationship, because the body knows about the heart, but not the other way around.

        - Our ubiquitous Fraction class is a great example of a composition:

            class Fraction
            {
            private:
                int m_numerator;
                int m_denominator;

            public:
                Fraction(int numerator=0, int denominator=1)
                    : m_numerator{ numerator }, m_denominator{ denominator }
                {
                }
            };

        - This class has two data members: a numerator and a denominator. The numerator and denominator are part of the Fraction (contained within it). They can not belong to more than one Fraction at a time. The numerator and denominator don’t know they are part of a Fraction, they just hold integers. When a Fraction instance is created, the numerator and denominator are created. When the fraction instance is destroyed, the numerator and denominator are destroyed as well.

        - While object composition models has-a type relationships (a body has-a heart, a fraction has-a denominator), we can be more precise and say that composition models “part-of” relationships (a heart is part-of a body, a numerator is part of a fraction). Composition is often used to model physical relationships, where one object is physically contained inside another
        
        - The parts of an object composition can be singular or multiplicative -- for example, a heart is a singular part of the body, but a body contains 10 fingers (which could be modeled as an array).

    4. Implementing compositions : 

        - Compositions are one of the easiest relationship types to implement in C++. They are typically created as structs or classes with normal data members. Because these data members exist directly as part of the struct/class, their lifetimes are bound to that of the class instance itself.

        - Compositions that need to do dynamic allocation or deallocation may be implemented using pointer data members. In this case, the composition class should be responsible for doing all necessary memory management itself (not the user of the class).

        - In general, if you can design a class using composition, you should design a class using composition. Classes designed using composition are straightforward, flexible, and robust (in that they clean up after themselves nicely).

    5. More examples : First, let’s design the point class. Our creature is going to live in a 2d world, so our point class will have 2 dimensions, X and Y. We will assume the world is made up of discrete squares, so these dimensions will always be integers.

        class Point2D
        {
        private:
            int m_x;
            int m_y;

        public:
            // A default constructor
            Point2D()
                : m_x{ 0 }, m_y{ 0 }
            {
            }

            // A specific constructor
            Point2D(int x, int y)
                : m_x{ x }, m_y{ y }
            {
            }

            // An overloaded output operator
            friend std::ostream& operator<<(std::ostream& out, const Point2D& point)
            {
                out << '(' << point.m_x << ", " << point.m_y << ')';
                return out;
            }

            // Access functions
            void setPoint(int x, int y)
            {
                m_x = x;
                m_y = y;
            }

        };

    6. Variants on the composition theme : Although most compositions directly create their parts when the composition is created and directly destroy their parts when the composition is destroyed, there are some variations of composition that bend these rules a bit. The key point here is that the composition should manage its parts without the user of the composition needing to manage anything.

    7. Composition and class members : A good rule of thumb is that each class should be built to accomplish a single task. That task should either be the storage and manipulation of some kind of data (e.g. Point2D, std::string), OR the coordination of its members (e.g. Creature). Ideally not both.

    
*/
int main()
{
    return 0;
}