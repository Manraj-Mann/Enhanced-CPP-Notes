#include <iostream>
/* 
    Notes :  
    
    1. We discussed how calling access functions that return references to data members can be dangerous when the implicit object is an rvalue. Here’s a quick recap:

        class Employee
        {
        private:
            std::string m_name{};

        public:
            Employee(std::string_view name): m_name { name } {}
            const std::string& getName() const { return m_name; } //  getter returns by const reference
        };

        // createEmployee() returns an Employee by value (which means the returned value is an rvalue)
        Employee createEmployee(std::string_view name)
        {
            Employee e { name };
            return e;
        }

        int main()
        {
            // Case 1: okay: use returned reference to member of rvalue class object in same expression
            std::cout << createEmployee("Frank").getName() << '\n';

            // Case 2: bad: save returned reference to member of rvalue class object for use later
            const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
            std::cout << ref << '\n'; // undefined behavior

            return 0;
        }

        - In case 2, the rvalue object returned from createEmployee("Garbo") is destroyed after initializing ref, leaving ref referencing a data member that was just destroyed. Subsequent use of ref exhibits undefined behavior.

    2. This presents somewhat of a conundrum : 

        - If our getName() function returns by value, this is safe when our implicit object is an rvalue, but makes an expensive and unnecessary copy when our implicit object is an lvalue (which is the most common case).
        
        - If our getName() function returns by const reference, this is efficient (as no copy of the std::string is made), but can be misused when the implicit object is an rvalue (resulting in undefined behavior).

        - Since member functions are typically called on lvalue implicit objects, the conventional choice is to return by const reference and simply avoid misusing the returned reference in cases where the implicit object is an rvalue.

    3. Ref qualifiers : To help address such issues, C++11 introduced a little known feature called a ref-qualifier that allows us to overload a member function based on whether it is being called on an lvalue or an rvalue implicit object. Using this feature, we can create two versions of getName() -- one for the case where our implicit object is an lvalue, and one for the case where our implicit object is an rvalue.

    4. Some notes about ref-qualified member functions : 

        - First, for a given function, non-ref-qualified overloads and ref-qualified overloads cannot coexist. Use one or the other.

        - Second, similar to how a const lvalue reference can bind to an rvalue, if only a const lvalue-qualified function exists, it will accept either lvalue or rvalue implicit objects.

        - Third, either qualified overload can be explicitly deleted (using = delete), which prevents calls to that function. For example, deleting the rvalue-qualified version prevents use of the function with rvalue implicit objects.

    5. So why don’t we recommend using ref-qualifiers? 

    While ref-qualifiers are neat, there are some downsides to using them in this way.

        - Adding rvalue overloads to every getter that returns a reference adds clutter to the class, to mitigate against a case that isn’t that common and is easily avoidable with good habits.
        
        - Having an rvalue overload return by value means we have to pay for the cost of a copy (or move) even in cases where we could have used a reference safely (e.g. in case 1 of the example at the top of the lesson).



*/
int main()
{
    return 0;
}