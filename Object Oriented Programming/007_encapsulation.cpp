#include <iostream>
/* 
    Notes :  
    
    1. The interface of a class type defines how a user of the class type will interact with objects of the class type. Because only public members can be accessed from outside of the class type, the public members of a class type form its interface. For this reason, an interface composed of public members is sometimes called a public interface.

    2. The implementation of a class type consists of the code that actually makes the class behave as intended. This includes both the member variables that store data, and the bodies of the member functions that contain the program logic and manipulate the member variables.

    3. Data hiding (encapsulation) - In programming, data hiding (also called information hiding or data abstraction) is a technique used to enforce the separation of interface and implementation by hiding the implementation of a program-defined data type from users.

    4. How to implement data hiding - 

        - First, we ensure the data members of the class type are private (so that the user can not directly access them). The statements inside the bodies of member functions are already not directly accessible to users, so we don’t need to do anything else there.

        - Second, we ensure the member functions are public, so that the user can call them.

    5. Data hiding make classes easier to use, and reduces complexity - 

        - To use an encapsulated class, you don’t need to know how it is implemented. You only need to understand its interface: what member functions are publicly available, what arguments they take, and what values they return.

        - Example : 

            int main()
            {
                std::string_view sv{ "Hello, world!" };
                std::cout << sv.length();

                return 0;
            }

            - In this short program, the details of how std::string_view is implemented is not exposed to us. We don’t get to see how many data members a std::string_view has, what they are named, or what type they are. We don’t know how the length() member function is returning the length of the string being viewed.

    6. Data hiding allows us to maintain invariants - 

        Consider the following program:

        struct Employee // members are public by default
        {
            std::string name{ "John" };
            char firstInitial{ 'J' }; // should match first initial of name

            void print() const
            {
                std::cout << "Employee " << name << " has first initial " << firstInitial << '\n';
            }
        };

        int main()
        {
            Employee e{}; // defaults to "John" and 'J'
            e.print();

            e.name = "Mark"; // change employee's name to "Mark"
            e.print(); // prints wrong initial

            return 0;
        }

        - When we give users direct access to the implementation of a class, they become responsible for maintaining all invariants -- which they may not do (either correctly, or at all). Putting this burden on the user adds a lot of complexity.

        class Employee // members are private by default
        {
            std::string m_name{};
            char m_firstInitial{};

        public:
            void setName(std::string_view name)
            {
                m_name = name;
                m_firstInitial = name.front(); // use std::string::front() to get first letter of `name`
            }

            void print() const
            {
                std::cout << "Employee " << m_name << " has first initial " << m_firstInitial << '\n';
            }
        };

        int main()
        {
            Employee e{};
            e.setName("John");
            e.print();

            e.setName("Mark");
            e.print();

            return 0;
        }

    7. Data hiding allows us to do better error detection (and handling) - The point here is that we can detect the misuse, and then handle it however we think is most appropriate. How we best handle such cases effectively is a topic for another day.

    8. Data hiding makes it possible to change implementation details without breaking existing programs 

    9. Classes with interfaces are easier to debug - And finally, encapsulation can help you debug a program when something goes wrong. Often when a program does not work correctly, it is because one of our member variables has been given an incorrect value. If everyone is able to set the member variable directly, tracking down which piece of code actually modified the member variable to the wrong value can be difficult. This can involve breakpointing every statement that modifies the member variable -- and there can be lots of them.

    However, if a member can only be changed through a single member function, then you can simply breakpoint that single function and watch as each caller changes the value. This can make it much easier to determine who the culprit is.

    10. Prefer non-member functions to member functions - Prefer implementing functions as non-members when possible (especially functions that contain application specific data or logic).

    Here’s three similar examples, in order from worst to best:

        class Yogurt
        {
            std::string m_flavor{ "vanilla" };

        public:
            void setFlavor(std::string_view flavor)
            {
                m_flavor = flavor;
            }

            const std::string& getFlavor() const { return m_flavor; }

            // Worst: member function print() uses direct access to m_flavor when getter exists
            void print() const
            {
                std::cout << "The yogurt has flavor " << m_flavor << '\n';
            }
        };

        int main()
        {
            Yogurt y{};
            y.setFlavor("cherry");
            y.print();

            return 0;
        }

        - The above is the worst version. The print() member function directly accesses m_flavor when a getter for the flavor already exists. If the class implementation is ever updated, print() will also probably to be modified. The string printed by print() is application-specific (another application using this class may want to print something else, which will require cloning or modifying the class).

        class Yogurt
        {
            std::string m_flavor{ "vanilla" };

        public:
            void setFlavor(std::string_view flavor)
            {
                m_flavor = flavor;
            }

            const std::string& getFlavor() const { return m_flavor; }

            // Better: member function print() has no direct access to members
            void print(std::string_view prefix) const
            {
                std::cout << prefix << ' ' << getFlavor() << '\n';
            }
        };

        - The above version is better, but still not great. print() is still a member function, but at least it now does not directly access any data members. If the class implementation is ever updated, print() will need to be evaluated to determine whether it needs an update (but it will not). The prefix for the print() function is now parameterized, which allows us to move the prefix into non-member function main(). But the function still imposes constraints on how things are printed (e.g. it always prints as prefix, space, flavor, newline). If that does not meet the needs of a given application, another function will need to be added.

        class Yogurt
        {
            std::string m_flavor{ "vanilla" };

        public:
            void setFlavor(std::string_view flavor)
            {
                m_flavor = flavor;
            }

            const std::string& getFlavor() const { return m_flavor; }
        };

        // Best: non-member function print() is not part of the class interface
        void print(const Yogurt& y)
        {
                std::cout << "The yogurt has flavor " << y.getFlavor() << '\n';
        }

    11. The order of class member declaration - 

        There are two schools of thought here:

        - List your private members first, and then list your public member functions. This follows the traditional style of declare-before-use. Anybody looking at your class code will see how you’ve defined your data members before they are used, which can make reading through and understanding implementation details easier.
        
        - List your public members first, and put your private members down at the bottom. Because someone who uses your class is interested in the public interface, putting your public members first makes the information they need up top, and puts the implementation details (which are least important) last.
        In modern C++, the second method (public members go first) is more commonly recommended, especially for code that will be shared with other developers.

        - Best practice : Declare public members first, protected members next, and private members last. This spotlights the public interface and de-emphasizes implementation details.

*/
int main()
{
    return 0;
}