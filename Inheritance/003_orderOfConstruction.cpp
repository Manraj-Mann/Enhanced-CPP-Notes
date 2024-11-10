#include <iostream>

/*

    Notes : 

    1. First, let’s introduce some new classes that will help us illustrate some important points.

        class Base
        {
        public:
            int m_id {};

            Base(int id=0)
                : m_id { id }
            {
            }

            int getId() const { return m_id; }
        };

        class Derived: public Base
        {
        public:
            double m_cost {};

            Derived(double cost=0.0)
                : m_cost { cost }
            {
            }

            double getCost() const { return m_cost; }
        };

    2. Because Derived inherits functions and variables from Base, you may assume that the members of Base are copied into Derived. However, this is not true. Instead, we can consider Derived as a two part class: one part Derived, and one part Base.

        - Base b; => Base is a non-derived class because it does not inherit from any other classes. C++ allocates memory for Base, then calls Base’s default constructor to do the initialization.

        - Derived derived; => As mentioned above, Derived is really two parts: a Base part, and a Derived part. When C++ constructs derived objects, it does so in phases. First, the most-base class (at the top of the inheritance tree) is constructed. Then each child class is constructed in order, until the most-child class (at the bottom of the inheritance tree) is constructed last.

        - This makes sense: logically, a child can not exist without a parent. It’s also the safe way to do things: the child class often uses variables and functions from the parent, but the parent class knows nothing about the child. Instantiating the parent class first ensures those variables are already initialized by the time the derived class is created and ready to use them.

    3. Order of construction for inheritance chains - SAME AS ABOVE

    4. Conclusion : C++ constructs derived classes in phases, starting with the most-base class (at the top of the inheritance tree) and finishing with the most-child class (at the bottom of the inheritance tree). As each class is constructed, the appropriate constructor from that class is called to initialize that part of the class.

    - You will note that our example classes in this section have all used base class default constructors (for simplicity). In the next lesson, we will take a closer look at the role of constructors in the process of constructing derived classes (including how to explicitly choose which base class constructor you want your derived class to use).


*/

int main()
{
    return 0;
}