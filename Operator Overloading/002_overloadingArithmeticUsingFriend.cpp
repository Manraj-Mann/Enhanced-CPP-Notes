#include <iostream>
/* 
    Notes :  
    
    1. Some of the most commonly used operators in C++ are the arithmetic operators -- that is, the plus operator (+), minus operator (-), multiplication operator (*), and division operator (/). Note that all of the arithmetic operators are binary operators -- meaning they take two operands -- one on each side of the operator. All four of these operators are overloaded in the exact same way.

    2. It turns out that there are three different ways to overload operators: 
    
        1. the member function way, 
        2. the friend function way, and 
        3. the normal function way. 
        
        - In this lesson, we’ll cover the friend function way (because it’s more intuitive for most binary operators). 
        
        - Next lesson, we’ll discuss the normal function way. Finally, in a later lesson in this chapter, we’ll cover the member function way. And, of course, we’ll also summarize when to use each in more detail.

    3. Overloading operators using friend functions - 

        class Cents
        {
        private:
            int m_cents {};

        public:
            Cents(int cents) : m_cents{ cents } { }
            int getCents() const { return m_cents; }
        };

        - The following example shows how to overload operator plus (+) in order to add two “Cents” objects together:

            class Cents
            {
            private:
                int m_cents {};

            public:
                Cents(int cents) : m_cents{ cents } { }

                // add Cents + Cents using a friend function
                friend Cents operator+(const Cents& c1, const Cents& c2);

                int getCents() const { return m_cents; }
            };

            // note: this function is not a member function!
            Cents operator+(const Cents& c1, const Cents& c2)
            {
                // use the Cents constructor and operator+(int, int)
                // we can access m_cents directly because this is a friend function
                return c1.m_cents + c2.m_cents;
            }

        - Overloading the plus operator (+) is as simple as declaring a function named operator+, giving it two parameters of the type of the operands we want to add, picking an appropriate return type, and then writing the function.

    4. Friend functions can be defined inside the class - Even though friend functions are not members of the class, they can still be defined inside the class if desired:

        class Cents
        {
        private:
            int m_cents {};

        public:
            explicit Cents(int cents) : m_cents{ cents } { }

            // add Cents + Cents using a friend function
                // This function is not considered a member of the class, even though the definition is inside the class
            friend Cents operator+(const Cents& c1, const Cents& c2)
            {
                // use the Cents constructor and operator+(int, int)
                // we can access m_cents directly because this is a friend function
                return Cents { c1.m_cents + c2.m_cents };
            }

            int getCents() const { return m_cents; }
        };

    5. Overloading operators for operands of different types - Often it is the case that you want your overloaded operators to work with operands that are different types. For example, if we have Cents(4), we may want to add the integer 6 to this to produce the result Cents(10).

        - When C++ evaluates the expression x + y, x becomes the first parameter, and y becomes the second parameter. When x and y have the same type, it does not matter if you add x + y or y + x -- either way, the same version of operator+ gets called. However, when the operands have different types, x + y does not call the same function as y + x.

        - For example, Cents(4) + 6 would call operator+(Cents, int), and 6 + Cents(4) would call operator+(int, Cents). Consequently, whenever we overload binary operators for operands of different types, we actually need to write two functions -- one for each case. Here is an example of that:
    
            class Cents
            {
            private:
                int m_cents {};

            public:
                explicit Cents(int cents) : m_cents{ cents } { }

                // add Cents + int using a friend function
                friend Cents operator+(const Cents& c1, int value);

                // add int + Cents using a friend function
                friend Cents operator+(int value, const Cents& c1);


                int getCents() const { return m_cents; }
            };

            // note: this function is not a member function!
            Cents operator+(const Cents& c1, int value)
            {
                // use the Cents constructor and operator+(int, int)
                // we can access m_cents directly because this is a friend function
                return Cents { c1.m_cents + value };
            }

            // note: this function is not a member function!
            Cents operator+(int value, const Cents& c1)
            {
                // use the Cents constructor and operator+(int, int)
                // we can access m_cents directly because this is a friend function
                return Cents { c1.m_cents + value };
            }
    
    6. Another example : 

        class MinMax
        {
        private:
            int m_min {}; // The min value seen so far
            int m_max {}; // The max value seen so far

        public:
            MinMax(int min, int max)
                : m_min { min }, m_max { max }
            { }

            int getMin() const { return m_min; }
            int getMax() const { return m_max; }

            friend MinMax operator+(const MinMax& m1, const MinMax& m2);
            friend MinMax operator+(const MinMax& m, int value);
            friend MinMax operator+(int value, const MinMax& m);
        };

        MinMax operator+(const MinMax& m1, const MinMax& m2)
        {
            // Get the minimum value seen in m1 and m2
            int min{ m1.m_min < m2.m_min ? m1.m_min : m2.m_min };

            // Get the maximum value seen in m1 and m2
            int max{ m1.m_max > m2.m_max ? m1.m_max : m2.m_max };

            return MinMax { min, max };
        }

        MinMax operator+(const MinMax& m, int value)
        {
            // Get the minimum value seen in m and value
            int min{ m.m_min < value ? m.m_min : value };

            // Get the maximum value seen in m and value
            int max{ m.m_max > value ? m.m_max : value };

            return MinMax { min, max };
        }

        MinMax operator+(int value, const MinMax& m)
        {
            // calls operator+(MinMax, int)
            return m + value;
        }


    7. Implementing operators using other operators

        In the above example, note that we defined operator+(int, MinMax) by calling operator+(MinMax, int) (which produces the same result). This allows us to reduce the implementation of operator+(int, MinMax) to a single line, making our code easier to maintain by minimizing redundancy and making the function simpler to understand.

        It is often possible to define overloaded operators by calling other overloaded operators. You should do so if and when doing so produces simpler code. In cases where the implementation is trivial (e.g. a single line) it may or may not be worth doing this.


*/

class paisa
{
    private:

    int _kitna {};

    public:

    paisa(int kitna) : _kitna(kitna){}

    int getPaisa() const 
    {
        return _kitna;
    };

    // friend function to overload + operator
    friend paisa operator+(paisa &firstPaisa , paisa &secondPaisa);

    // friend function to overload - operator
    friend paisa operator-(paisa &firstPaisa , paisa &secondPaisa);

    friend paisa operator+( const int i , const paisa &paisa);

};

// defining the + operator 
paisa operator+(paisa &firstPaisa , paisa &secondPaisa)
{
    return firstPaisa._kitna + secondPaisa._kitna;
}

// defining the - operator
paisa operator-(paisa &firstPaisa , paisa &secondPaisa)
{
    return paisa(firstPaisa._kitna - secondPaisa._kitna);
}

paisa operator+(const int i , const paisa &paisa)
{
    return i + paisa._kitna;
}

int main()
{
    paisa p1{1};
    paisa p2{10};


    paisa p3{p1 + p2};

    paisa p4{p2 - p1};

    paisa p5{100 + p2};


    std::cout<<"Paisa 3 : "<<p3.getPaisa()<<std::endl;
    std::cout<<"Paisa 4 : "<<p4.getPaisa()<<std::endl;
    std::cout<<"Paisa 5 : "<<p5.getPaisa()<<std::endl;


    return 0;
}