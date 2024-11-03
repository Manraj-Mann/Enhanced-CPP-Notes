#include <iostream>
/* 
    Notes :  
    
    1. To make things easier, we can provide a user-defined conversion by overloading the int typecast. This will allow us to convert our Cents class directly into an int. The following example shows how this is done:

        class Cents
        {
        private:
            int m_cents{};
        public:
            Cents(int cents=0)
                : m_cents{ cents }
            {
            }

            // Overloaded int cast
            operator int() const { return m_cents; }

            int getCents() const { return m_cents; }
            void setCents(int cents) { m_cents = cents; }
        };

    2. There are three things to note:

        = To overload the function that casts our class to an int, we write a new function in our class called operator int(). Note that there is a space between the word operator and the type we are casting to. Such functions must be non-static members.
        
        = User-defined conversions do not have parameters, as there is no way to pass arguments explicitly to them. They do still have a hidden *this parameter, pointing to the implicit object (which is the object to be converted)
        
        = User-defined conversions do not declare a return type. The name of the conversion (e.g. int) is used as the return type, as it is the only return type allowed. This prevents redundancy.

    3. Such typecasts can also be invoked explicitly via static_cast:

        std::cout << static_cast<int>(cents);

    4. Explicit typecasts - Just like we can make constructors explicit so that they can’t be used for implicit conversions, we can also make our overloaded typecasts explicit for the same reason. Explicit typecasts can only be invoked explicitly (e.g. during non-copy initialization or by using an explicit cast like static_cast).


*/

class Cents
{
private:
    int m_cents{};
public:
    Cents(int cents=0)
        : m_cents{ cents }
    {
    }

    // Overloaded int cast
    operator int() const { return m_cents; }

    int getCents() const { return m_cents; }
    void setCents(int cents) { m_cents = cents; }
};
int main()
{
    Cents s;

    int i = s;

    return 0;
}