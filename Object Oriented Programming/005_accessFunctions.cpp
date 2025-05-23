#include <iostream>
/* 
    Notes :  
    
    1. Access functions - An access function is a trivial public member function whose job is to retrieve or change the value of a private member variable.

        - Access functions come in two flavors: getters and setters. Getters (also sometimes called accessors) are public member functions that return the value of a private member variable. Setters (also sometimes called mutators) are public member functions that set the value of a private member variable.

        - Getters are usually made const, so they can be called on both const and non-const objects. Setters should be non-const, so they can modify the data members.

        Example : 

            class Date
            {
            private:
                int m_year { 2020 };
                int m_month { 10 };
                int m_day { 14 };

            public:
                void print()
                {
                    std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
                }

                int getYear() const { return m_year; }        // getter for year
                void setYear(int year) { m_year = year; }     // setter for year

                int getMonth() const  { return m_month; }     // getter for month
                void setMonth(int month) { m_month = month; } // setter for month

                int getDay() const { return m_day; }          // getter for day
                void setDay(int day) { m_day = day; }         // setter for day
            };

    2. Access function naming - There is no common convention for naming access functions. However, there are a few naming conventions that are more popular than others. Prefixed with “get” and “set”.

    3. Getters should return by value or by const lvalue reference - Getters should provide “read-only” access to data. Therefore, the best practice is that they should return by either value (if making a copy of the member is inexpensive) or by const lvalue reference (if making a copy of the member is expensive).

    4. Access functions concerns - You create your classes, consider the following:

        - If your class has no invariants and requires a lot of access functions, consider using a struct (whose data members are public) and providing direct access to members instead.
        
        - Prefer implementing behaviors or actions instead of access functions. For example, instead of a setAlive(bool) setter, implement a kill() and a revive() function.
        
        - Only provide access functions in cases where the public would reasonably need to get or set the value of an individual member.


*/

class Date
{
private:
    int m_year { 2020 };
    int m_month { 10 };
    int m_day { 14 };

public:
    void print()
    {
        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
    }

    int getYear() const { return m_year; }        // getter for year
    void setYear(int year) { m_year = year; }     // setter for year

    int getMonth() const  { return m_month; }     // getter for month
    void setMonth(int month) { m_month = month; } // setter for month

    int getDay() const { return m_day; }          // getter for day
    void setDay(int day) { m_day = day; }         // setter for day
};

int main()
{
    Date d{};
    d.setYear(2021);
    std::cout << "The year is: " << d.getYear() << '\n';

    return 0;
}