#include <iostream>
/* 
    Notes :  
    
    1. Modifying the data members of const objects is disallowed - 

        struct Date
        {
            int year {};
            int month {};
            int day {};

            void incrementDay()
            {
                ++day;
            }
        };

        const Date today { 2020, 10, 14 }; // const

        // today.day += 1;        // compile error: can't modify member of const object
        // today.incrementDay();  // compile error: can't call member function that modifies member of const object

    2. Const objects may not call non-const member functions - 

        struct Date
        {
            int year {};
            int month {};
            int day {};

            void print()
            {
                std::cout << year << '/' << month << '/' << day;
            }
        };

        int main()
        {
            const Date today { 2020, 10, 14 }; // const

            today.print();  // compile error: can't call non-const member function

            return 0;
        }

        Even though print() does not try to modify a member variable, our call to today.print() is still a const violation. This happens because the print() member function itself is not declared as const. The compiler won’t let us call a non-const member function on a const object.

    3. Const member functions : To address the above issue, we need to make print() a const member function. A const member function is a member function that guarantees it will not modify the object or call any non-const member functions (as they may modify the object).

    4. Const member functions may be called on non-const objects - 

        Date today { 2020, 10, 14 }; // non-const
        today.print();  // ok: can call const member function on non-const object

        - Because const member functions can be called on both const and non-const objects, if a member function does not modify the state of the object, it should be made const.

    5. Const objects via pass by const reference - 

        - Although instantiating const local variables is one way to create const objects, a more common way to get a const object is by passing an object to a function by const reference.

        Example : 

            struct Date
            {
                int year {};
                int month {};
                int day {};

                void print() const // now const
                {
                    std::cout << year << '/' << month << '/' << day;
                }
            };

            void doSomething(const Date& date)
            {
                date.print();
            }

            int main()
            {
                Date today { 2020, 10, 14 }; // non-const
                today.print();

                doSomething(today);

                return 0;
            }
    
    6. Member function const and non-const overloading - 

        - Finally, although it is not done very often, it is possible to overload a member function to have a const and non-const version of the same function. This works because the const qualifier is considered part of the function’s signature, so two functions which differ only in their const-ness are considered distinct.

        - Example : 

            struct Something
            {
                void print()
                {
                    std::cout << "non-const\n";
                }

                void print() const
                {
                    std::cout << "const\n";
                }
            };

*/

struct Date
{
    int year {};
    int month {};
    int day {};

    void incrementDay()
    {
        ++day;
    }

    void print()
    {
        std::cout << year << '/' << month << '/' << day;
    }

    void printConst() const 
    {
        std::cout << "Const : "<<year << '/' << month << '/' << day<<std::endl;
    }

    void printConst() 
    {
        std::cout << "Non-Const : "<<year << '/' << month << '/' << day<<std::endl;
    }
};


int main()
{
    const Date today { 2020, 10, 14 }; // const

    // today.day += 1;        // compile error: can't modify member of const object
    // today.incrementDay();  // compile error: can't call member function that modifies member of const object

    // today.print();  // compile error: can't call non-const member function

    today.printConst();

    Date aaj { 2020, 10, 14 }; // const

    aaj.printConst();
    

    return 0;
}