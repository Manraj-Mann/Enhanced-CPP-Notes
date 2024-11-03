#include <iostream>
/* 
    Notes :  Overloading unary operators +, -, and !
    
    1. Overloading unary operators : Unlike the operators you’ve seen so far, the positive (+), negative (-) and logical not (!) operators all are unary operators, which means they only operate on one operand. Because they only operate on the object they are applied to, typically unary operator overloads are implemented as member functions. All three operators are implemented in an identical manner.

        Example : 

            class Cents
            {
            private:
                int m_cents {};

            public:
                Cents(int cents): m_cents{cents} {}

                // Overload -Cents as a member function
                Cents operator-() const;

                int getCents() const { return m_cents; }
            };

            // note: this function is a member function!
            Cents Cents::operator-() const
            {
                return -m_cents; // since return type is a Cents, this does an implicit conversion from int to Cents using the Cents(int) constructor
            }

    2. This should be straightforward. Our overloaded negative operator (-) is a unary operator implemented as a member function, so it takes no parameters (it operates on the *this object). It returns a Cents object that is the negation of the original Cents value. Because operator- does not modify the Cents object, we can (and should) make it a const function (so it can be called on const Cents objects).

    3. Extending the concept, we can say that operator! should evaluate to true if the state of the object is “false”, “zero”, or whatever the default initialization state is.

*/

class paisa
{
    int _kitna;
    
    public:

    paisa(int val) : _kitna(val) {}

    int getPaisa() const
    {
        return _kitna;
    }

    bool operator!() const
    {
        return _kitna == 0;
    }

    paisa operator-() const
    {
        return -_kitna;
    }

    paisa operator+() const
    {
        return +_kitna;
    }

};
int main()
{
    paisa p{10};

    if(!p)
    {
        std::cout<<"Paisa is 0 !"<<std::endl;
    }
    else
    {   
        std::cout<<"Paisa is not 0 !"<<std::endl;
    }

    std::cout<<"negative : "<<(-p).getPaisa()<<std::endl;

    paisa p1{-10};

    std::cout<<"no operation : "<<(+p1).getPaisa()<<std::endl;


    return 0;
}