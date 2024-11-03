#include <iostream>
/* 
    Notes :  
    
    1. Overloading operators using a member function is very similar to overloading operators using a friend function. When overloading an operator using a member function:

        - The overloaded operator must be added as a member function of the left operand.
        - The left operand becomes the implicit *this object
        - All other operands become function parameters.

        Example : 

            class Cents
            {
                private:
                    int m_cents {};

                public:
                    Cents(int cents)
                        : m_cents { cents } { }

                    // Overload Cents + int
                    Cents operator+(int value) const;

                    int getCents() const { return m_cents; }
            };

            // note: this function is a member function!
            // the cents parameter in the friend version is now the implicit *this parameter
            Cents Cents::operator+ (int value) const
            {
                return Cents { m_cents + value };
            }

    2. So if we can overload an operator as a friend or a member, which should we use? In order to answer that question, there’s a few more things you’ll need to know.

        - Not everything can be overloaded as a friend function : The assignment (=), subscript ([]), function call (()), and member selection (->) operators must be overloaded as member functions, because the language requires them to be.

        - Not everything can be overloaded as a member function : We are not able to overload operator<< as a member function. Why not? Because the overloaded operator must be added as a member of the left operand. In this case, the left operand is an object of type std::ostream. std::ostream is fixed as part of the standard library. We can’t modify the class declaration to add the overload as a member function of std::ostream.

    3. When to use a normal, friend, or member function overload : 

        - In most cases, the language leaves it up to you to determine whether you want to use the normal/friend or member function version of the overload. However, one of the two is usually a better choice than the other.

        - When dealing with binary operators that don’t modify the left operand (e.g. operator+), the normal or friend function version is typically preferred, because it works for all parameter types (even when the left operand isn’t a class object, or is a class that is not modifiable). The normal or friend function version has the added benefit of “symmetry”, as all operands become explicit parameters (instead of the left operand becoming *this and the right operand becoming an explicit parameter).

        - When dealing with binary operators that do modify the left operand (e.g. operator+=), the member function version is typically preferred. In these cases, the leftmost operand will always be a class type, and having the object being modified become the one pointed to by *this is natural. Because the rightmost operand becomes an explicit parameter, there’s no confusion over who is getting modified and who is getting evaluated.

        - Unary operators are usually overloaded as member functions as well, since the member version has no parameters.

    4. The following rules of thumb can help you determine which form is best for a given situation:

        1. If you’re overloading assignment (=), subscript ([]), function call (()), or member selection (->), do so as a member function.
        
        2. If you’re overloading a unary operator, do so as a member function.
        
        3. If you’re overloading a binary operator that does not modify its left operand (e.g. operator+), do so as a normal function (preferred) or friend function.
        
        4. If you’re overloading a binary operator that modifies its left operand, but you can’t add members to the class definition of the left operand (e.g. operator<<, which has a left operand of type ostream), do so as a normal function (preferred) or friend function.
        
        5. If you’re overloading a binary operator that modifies its left operand (e.g. operator+=), and you can modify the definition of the left operand, do so as a member function.

*/

class paisa
{
    int _kitna;
    public:

    explicit paisa(int value) : _kitna(value){}

    int getPaisa() const
    {
        return _kitna;
    }

    paisa operator+(paisa &second) const
    {   
        return paisa(this->_kitna + second._kitna);
    }
};

int main()
{
    paisa p1{1};

    paisa p2{10};

    paisa p3{p1 + p2};

    std::cout<<"Value : "<<p3.getPaisa()<<std::endl;

    return 0;
}