#include <iostream>

/*
    Notes : 

    1. With non-derived classes, constructors only have to worry about their own members. For example, consider Base. We can create a Base object like this:

        int main()
        {
            Base base{ 5 }; // use Base(int) constructor

            return 0;
        }
        
        - Here’s what actually happens when base is instantiated:

            1. Memory for base is set aside
            2. The appropriate Base constructor is called
            3. The member initializer list initializes variables
            4. The body of the constructor executes
            5. Control is returned to the caller

    2. Here’s what actually happens when derived is instantiated:

        1. Memory for derived is set aside (enough for both the Base and Derived portions)
        2. The appropriate Derived constructor is called
        3. The Base object is constructed first using the appropriate Base constructor. If no base constructor is specified, the default constructor will be used.
        4. The member initializer list initializes variables
        5. The body of the constructor executes
        6. Control is returned to the caller

    3. Initializing base class members : C++ prevents classes from initializing inherited member variables in the member initializer list of a constructor. In other words, the value of a member variable can only be set in a member initializer list of a constructor belonging to the same class as the variable.

        - Why does C++ do this? The answer has to do with const and reference variables. Consider what would happen if m_id were const. Because const variables must be initialized with a value at the time of creation, the base class constructor must set its value when the variable is created. However, when the base class constructor finishes, the derived class constructor’s member initializer lists are then executed. Each derived class would then have the opportunity to initialize that variable, potentially changing its value! By restricting the initialization of variables to the constructor of the class those variables belong to, C++ ensures that all variables are initialized only once.

        - In all of the examples so far, when we instantiate a Derived class object, the Base class portion has been created using the default Base constructor. Why does it always use the default Base constructor? Because we never told it to do otherwise! Fortunately, C++ gives us the ability to explicitly choose which Base class constructor will be called! To do this, simply add a call to the Base class constructor in the member initializer list of the derived class:

            class Derived: public Base
            {
            public:
                double m_cost {};

                Derived(double cost=0.0, int id=0)
                    : Base{ id } // Call Base(int) constructor with value id!
                    , m_cost{ cost }
                {
                }

                double getCost() const { return m_cost; }
            };

    4. In more detail, here’s what happens:

        1. Memory for derived is allocated.
        2. The Derived(double, int) constructor is called, where cost = 1.3, and id = 5.
        3. The compiler looks to see if we’ve asked for a particular Base class constructor. We have! So it calls Base(int) with id = 5.
        4. The base class constructor member initializer list sets m_id to 5.
        5. The base class constructor body executes, which does nothing.
        6. The base class constructor returns.
        7. The derived class constructor member initializer list sets m_cost to 1.3.
        8. The derived class constructor body executes, which does nothing.
        9. The derived class constructor returns.

        - This may seem somewhat complex, but it’s actually very simple. All that’s happening is that the Derived constructor is calling a specific Base constructor to initialize the Base portion of the object. Because m_id lives in the Base portion of the object, the Base constructor is the only constructor that can initialize that value.

    5. Now we can make our members private - As a quick refresher, public members can be accessed by anybody. Private members can only be accessed by member functions of the same class. Note that this means derived classes can not access private members of the base class directly! Derived classes will need to use access functions to access private members of the base class.

        class Base
        {
        private: // our member is now private
            int m_id {};

        public:
            Base(int id=0)
                : m_id{ id }
            {
            }

            int getId() const { return m_id; }
        };

        class Derived: public Base
        {
        private: // our member is now private
            double m_cost;

        public:
            Derived(double cost=0.0, int id=0)
                : Base{ id } // Call Base(int) constructor with value id!
                , m_cost{ cost }
            {
            }

            double getCost() const { return m_cost; }
        };

        int main()
        {
            Derived derived{ 1.3, 5 }; // use Derived(double, int) constructor
            std::cout << "Id: " << derived.getId() << '\n';
            std::cout << "Cost: " << derived.getCost() << '\n';

            return 0;
        }

    6. Destructors : When a derived class is destroyed, each destructor is called in the reverse order of construction. In the above example, when c is destroyed, the C destructor is called first, then the B destructor, then the A destructor. Warning : If your base class has virtual functions, your destructor should also be virtual, otherwise undefined behavior will result in certain cases. We cover this case in lesson 25.4 -- Virtual destructors, virtual assignment, and overriding virtualization.

    7. Summary : When constructing a derived class, the derived class constructor is responsible for determining which base class constructor is called. If no base class constructor is specified, the default base class constructor will be used. In that case, if no default base class constructor can be found (or created by default), the compiler will display an error. The classes are then constructed in order from most base to most derived.

*/

class base
{  
    public:
    
    int a;

    base(int x) : a(x) {}

};

class derived : public base
{
    int b;

    public:
        // derived(int x, int y) : a(x), b(y) {}

};

int main()
{
    return 0;
}