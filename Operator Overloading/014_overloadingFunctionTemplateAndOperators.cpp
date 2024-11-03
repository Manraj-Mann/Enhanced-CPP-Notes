#include <iostream>
/* 
    Notes :  
    
    1. Operators, function calls, and function templates : In this lesson, we’ll take a look at a few examples where our instantiated functions won’t compile because our actual class types don’t support those operators, and show how we can define those operators so that the instantiated functions will then compile.

        - To get around this problem, simply overload operator< for any class we wish to use max with:

            class Cents
            {
                private:
                    int m_cents {};
                    
                public:
                    Cents(int cents)
                        : m_cents { cents }
                    {
                    }

                    friend bool operator< (const Cents& c1, const Cents& c2)
                    {
                        return (c1.m_cents < c2.m_cents);
                    }

                    friend std::ostream& operator<< (std::ostream& ostr, const Cents& c)
                    {
                        ostr << c.m_cents;
                        return ostr;
                    }
            };

            template <typename T>
            const T& max(const T& x, const T& y)
            {
                return (x < y) ? y : x;
            }

            int main()
            {
                Cents nickel{ 5 };
                Cents dime { 10 };

                Cents bigger { max(nickel, dime) };
                std::cout << bigger << " is bigger\n";

                return 0;
            }

    2. Another example : Let’s do one more example of a function template not working because of missing overloaded operators.

        template <typename T>
        T average(const T* myArray, int numValues)
        {
            T sum { 0 };
            for (int count { 0 }; count < numValues; ++count)
                sum += myArray[count];

            sum /= numValues;
            return sum;
        }

        class Cents
        {
        private:
            int m_cents {};
        public:
            Cents(int cents)
                : m_cents { cents }
            {
            }

            friend std::ostream& operator<< (std::ostream& out, const Cents& cents)
            {
                out << cents.m_cents << " cents ";
                return out;
            }

            Cents& operator+= (const Cents &cents)
            {
                m_cents += cents.m_cents;
                return *this;
            }

            Cents& operator/= (int x)
            {
                m_cents /= x;
                return *this;
            }
        };

        int main()
        {
            Cents centsArray[] { Cents { 5 }, Cents { 10 }, Cents { 15 }, Cents { 14 } };
            std::cout << average(centsArray, 4) << '\n';

            return 0;
        }

*/
int main()
{
    return 0;
}