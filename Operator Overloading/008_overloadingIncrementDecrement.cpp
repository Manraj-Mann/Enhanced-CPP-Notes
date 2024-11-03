#include <iostream>
/* 
    Notes :  
    
    1. Overloading the increment (++) and decrement (--) operators is pretty straightforward, with one small exception. There are actually two versions of the increment and decrement operators: a prefix increment and decrement (e.g. ++x; --y;) and a postfix increment and decrement (e.g. x++; y--;).

    2. Overloading prefix increment and decrement : Prefix increment and decrement are overloaded exactly the same as any normal unary operator. We’ll do this one by example:

        class Digit
        {
            private:
                int m_digit{};
            public:
                Digit(int digit=0)
                    : m_digit{digit}
                {
                }

                Digit& operator++();
                Digit& operator--();

                friend std::ostream& operator<< (std::ostream& out, const Digit& d);
        };

        Digit& Digit::operator++()
        {
            // If our number is already at 9, wrap around to 0
            if (m_digit == 9)
                m_digit = 0;
            // otherwise just increment to next number
            else
                ++m_digit;

            return *this;
        }

        Digit& Digit::operator--()
        {
            // If our number is already at 0, wrap around to 9
            if (m_digit == 0)
                m_digit = 9;
            // otherwise just decrement to next number
            else
                --m_digit;

            return *this;
        }

        std::ostream& operator<< (std::ostream& out, const Digit& d)
        {
            out << d.m_digit;
            return out;
        }

    3. The postfix operators, on the other hand, need to return the state of the object before it is incremented or decremented. This leads to a bit of a conundrum -- if we increment or decrement the object, we won’t be able to return the state of the object before it was incremented or decremented. On the other hand, if we return the state of the object before we increment or decrement it, the increment or decrement will never be called.

    4. The typical way this problem is solved is to use a temporary variable that holds the value of the object before it is incremented or decremented. Then the object itself can be incremented or decremented. And finally, the temporary variable is returned to the caller. In this way, the caller receives a copy of the object before it was incremented or decremented, but the object itself is incremented or decremented. Note that this means the return value of the overloaded operator must be a non-reference, because we can’t return a reference to a local variable that will be destroyed when the function exits. Also note that this means the postfix operators are typically less efficient than the prefix operators because of the added overhead of instantiating a temporary variable and returning by value instead of reference.


*/

class number
{
    int _value;

    public:

    number(int value) : _value(value) {}

    number& operator++()
    {
        if(_value % 9 == 0)
            _value = 0;
        else
            ++_value;

        return *this;
    }

    number& operator--()
    {
        if(_value == 0)
            _value = 9;
        else
            --_value;

        return *this;
    }

    number operator++(int)
    {
        number temp{*this};

        ++(*this);

        return temp;
    }

    number operator--(int)
    {
        number temp{*this};

        --(*this);

        return temp;
    }

    friend std::ostream& operator<< (std::ostream &out , const number & num);

};

std::ostream& operator<<(std::ostream &out , const number &num)
{
    out<<num._value;
    return out;
}
int main()
{
    number num{100};

    std::cout<<"Value : "<<num<<std::endl;

    ++num;

    std::cout<<"Value : "<<num<<std::endl;

    --num;

    std::cout<<"Value : "<<num<<std::endl;

    std::cout<<"Before : "<<(num++)<<" After : "<<num<<std::endl;
    std::cout<<"Before : "<<(num--)<<" After : "<<num<<std::endl;


    return 0;
}