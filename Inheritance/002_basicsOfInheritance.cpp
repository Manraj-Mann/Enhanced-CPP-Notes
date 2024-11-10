#include <iostream>

/*
    1. Inheritance in C++ takes place between classes. In an inheritance (is-a) relationship, the class being inherited from is called the parent class, base class, or superclass, and the class doing the inheriting is called the child class, derived class, or subclass.

    2. A child class inherits both behaviors (member functions) and properties (member variables) from the parent (subject to some access restrictions that we’ll cover in a future lesson). These variables and functions become members of the derived class.

        class Person
        {
        public:
            std::string m_name{};
            int m_age{};

            Person(std::string_view name = "", int age = 0)
                : m_name{name}, m_age{age}
            {
            }

            const std::string& getName() const { return m_name; }
            int getAge() const { return m_age; }

        };

        // Employee publicly inherits from Person
        class Employee: public Person
        {
        public:
            double m_hourlySalary{};
            long m_employeeID{};

            Employee(double hourlySalary = 0.0, long employeeID = 0)
                : m_hourlySalary{hourlySalary}, m_employeeID{employeeID}
            {
            }

            void printNameAndSalary() const
            {
                std::cout << m_name << ": " << m_hourlySalary << '\n';
            }
        };

    3. Inheritance chains : It’s possible to inherit from a class that is itself derived from another class. There is nothing noteworthy or special when doing so -- everything proceeds as in the examples above. All Supervisor objects inherit the functions and variables from both Employee and Person, and add their own m_overseesIDs member variable. By constructing such inheritance chains, we can create a set of reusable classes that are very general (at the top) and become progressively more specific at each level of inheritance.


    4. Why is this kind of inheritance useful?

        - Inheriting from a base class means we don’t have to redefine the information from the base class in our derived classes. We automatically receive the member functions and member variables of the base class through inheritance, and then simply add the additional functions or member variables we want. This not only saves work, but also means that if we ever update or modify the base class (e.g. add new functions, or fix a bug), all of our derived classes will automatically inherit the changes!

        - For example, if we ever added a new function to Person, then Employee, Supervisor, and BaseballPlayer would automatically gain access to it. If we added a new variable to Employee, then Supervisor would also gain access to it. This allows us to construct new classes in an easy, intuitive, and low-maintenance way!

    5. Conclusion : Inheritance allows us to reuse classes by having other classes inherit their members. In future lessons, we’ll continue to explore how this works.


*/
int main()
{
    return 0;
}