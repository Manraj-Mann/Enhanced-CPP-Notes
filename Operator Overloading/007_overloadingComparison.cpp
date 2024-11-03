#include <iostream>
/* 
    Notes :  
    
    1. Overloading these comparison operators is comparatively simple (see what I did there?), as they follow the same patterns as we’ve seen in overloading other operators. Because the comparison operators are all binary operators that do not modify their left operands, we will make our overloaded comparison operators friend functions.

        class Car
        {
        private:
            std::string m_make;
            std::string m_model;

        public:
            Car(std::string_view make, std::string_view model)
                : m_make{ make }, m_model{ model }
            {
            }

            friend bool operator== (const Car& c1, const Car& c2);
            friend bool operator!= (const Car& c1, const Car& c2);
        };

        bool operator== (const Car& c1, const Car& c2)
        {
            return (c1.m_make == c2.m_make &&
                    c1.m_model == c2.m_model);
        }

        bool operator!= (const Car& c1, const Car& c2)
        {
            return (c1.m_make != c2.m_make ||
                    c1.m_model != c2.m_model);
        }
    
    2. Here’s a different example overloading all 6 logical comparison operators:

        class Cents
        {
        private:
            int m_cents;

        public:
            Cents(int cents)
            : m_cents{ cents }
            {}

            friend bool operator== (const Cents& c1, const Cents& c2);
            friend bool operator!= (const Cents& c1, const Cents& c2);

            friend bool operator< (const Cents& c1, const Cents& c2);
            friend bool operator> (const Cents& c1, const Cents& c2);

            friend bool operator<= (const Cents& c1, const Cents& c2);
            friend bool operator>= (const Cents& c1, const Cents& c2);
        };

        bool operator== (const Cents& c1, const Cents& c2)
        {
            return c1.m_cents == c2.m_cents;
        }

        bool operator!= (const Cents& c1, const Cents& c2)
        {
            return c1.m_cents != c2.m_cents;
        }

        bool operator> (const Cents& c1, const Cents& c2)
        {
            return c1.m_cents > c2.m_cents;
        }

        bool operator< (const Cents& c1, const Cents& c2)
        {
            return c1.m_cents < c2.m_cents;
        }

        bool operator<= (const Cents& c1, const Cents& c2)
        {
            return c1.m_cents <= c2.m_cents;
        }

        bool operator>= (const Cents& c1, const Cents& c2)
        {
            return c1.m_cents >= c2.m_cents;
        }

    3. Minimizing comparative redundancy : In the example above, note how similar the implementation of each of the overloaded comparison operators are. Overloaded comparison operators tend to have a high degree of redundancy, and the more complex the implementation, the more redundancy there will be.

        Fortunately, many of the comparison operators can be implemented using the other comparison operators:

            - operator!= can be implemented as !(operator==)
            - operator> can be implemented as operator< with the order of the parameters flipped
            - operator>= can be implemented as !(operator<)
            - operator<= can be implemented as !(operator>)

        This means that we only need to implement logic for operator== and operator<, and then the other four comparison operators can be defined in terms of those two! Here’s an updated Cents example illustrating this:
            
            class Cents
            {
            private:
                int m_cents;

            public:
                Cents(int cents)
                    : m_cents{ cents }
                {}

                friend bool operator== (const Cents& c1, const Cents& c2) { return c1.m_cents == c2.m_cents; }
                friend bool operator!= (const Cents& c1, const Cents& c2) { return !(operator==(c1, c2)); }

                friend bool operator< (const Cents& c1, const Cents& c2) { return c1.m_cents < c2.m_cents; }
                friend bool operator> (const Cents& c1, const Cents& c2) { return operator<(c2, c1); }

                friend bool operator<= (const Cents& c1, const Cents& c2) { return !(operator>(c1, c2)); }
                friend bool operator>= (const Cents& c1, const Cents& c2) { return !(operator<(c1, c2)); }

            };

    4. The spaceship operator <=> C++20 : C++20 introduces the spaceship operator (operator<=>), which allows us to reduce the number of comparison functions we need to write down to 2 at most, and sometimes just 1!

    
*/
int main()
{
    return 0;
}