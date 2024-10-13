#include <iostream>
/* 
    Notes :  
    
    1. When a class contains multiple constructors, it’s extremely common for the code in each constructor to be similar if not identical, with lots of repetition. We’d similarly like to remove constructor redundancy where possible.

        class Employee
        {
        private:
            std::string m_name{};
            int m_id{ 0 };

        public:
            Employee(std::string_view name)
                : m_name{ name }
            {
                std::cout << "Employee " << m_name << " created\n";
            }

            Employee(std::string_view name, int id)
                : m_name{ name }, m_id{ id }
            {
                std::cout << "Employee " << m_name << " created\n";
            }
        };

    2. Constructors are allowed to call other functions, including other member functions of the class. So we could refactor like this:

        class Employee
        {
        private:
            std::string m_name{};
            int m_id{ 0 };

            void printCreated() const
            {
                std::cout << "Employee " << m_name << " created\n";
            }

        public:
            Employee(std::string_view name)
                : m_name{ name }
            {
                printCreated();
            }

            Employee(std::string_view name, int id)
                : m_name{ name }, m_id{ id }
            {
                printCreated();
            }
        };

    3. The obvious solution doesn’t work - Analogous to how we had function B() call function A() in the example above, the obvious solution would be to have one of the Employee constructors call the other constructor. But this will not work as intended, because constructors are not designed to be called directly from the body of another function (including other constructors)!

        For example, you might think to try this:

            class Employee
            {
            private:
                std::string m_name{};
                int m_id{ 0 };

            public:
                Employee(std::string_view name)
                    : m_name{ name }
                {
                    std::cout << "Employee " << m_name << " created\n";
                }

                Employee(std::string_view name, int id)
                    : m_name{ name }, m_id{ id }
                {
                    Employee(name); // compile error
                }
            };
        
        - This doesn’t work, and will result in a compilation error.

        - A more dangerous case occurs when we try to explicitly call a constructor without any arguments. This does not perform a function call to the default constructor -- rather, it creates a temporary (unnamed) object and value initializes it! Here’s a silly example that demonstrates:

            struct Foo
            {
                int x{};
                int y{};

            public:
                Foo()
                {
                    x = 5;
                }

                Foo(int value): y { value }
                {
                    // intent: call Foo() function
                    // actual: value initializes nameless temporary Foo (which is then discarded)
                    Foo(); // note: this is the equivalent of writing Foo{}
                }
            };

        - In this example, the Foo(int) constructor has statement Foo(), expecting to call the Foo() constructor and assign member x the value 5. However, this syntax actually creates an unnamed temporary Foo and then value initializes it (the same as if we had written Foo{}). When the x = 5 statement executes, it is the x member of the temporary Foo that is assigned a value. Because the temporary object is not used, once it has finished construction, it is discarded.

        - Warning : Constructors should not be called directly from the body of another function. Doing so will either result in a compilation error, or will value initialize a temporary object and then discard it (which likely isn’t what you want).

    4. Delegating constructors - Constructors are allowed to delegate (transfer responsibility for) initialization to another constructor from the same class type. This process is sometimes called constructor chaining and such constructors are called delegating constructors.

    - To make one constructor delegate initialization to another constructor, simply call the constructor in the member initializer list. Applied to our example above:

        class Employee
        {
        private:
            std::string m_name{};
            int m_id{ 0 };

        public:
            Employee(std::string_view name)
                : Employee{ name, 0 } // delegate initialization to Employee(std::string_view, int) constructor
            {
            }

            Employee(std::string_view name, int id)
                : m_name{ name }, m_id{ id } // actually initializes the members
            {
                std::cout << "Employee " << m_name << " created\n";
            }

        };

    - The downside of this method is that it sometimes requires duplication of initialization values. In the delegation to the Employee(std::string_view, int) constructor, we need an initialization value for the int parameter. We had to hardcode literal 0, as there is no way to reference the default member initializer.

    - A few additional notes about delegating constructors. First, a constructor that delegates to another constructor is not allowed to do any member initialization itself. So your constructors can delegate or initialize, but not both.

    - Second, it’s possible for one constructor to delegate to another constructor, which delegates back to the first constructor. This forms an infinite loop, and will cause your program to run out of stack space and crash. You can avoid this by ensuring all of your constructors resolve to a non-delegating constructor.

    5. Reducing constructors using default arguments - 

        - Default values can also sometimes be used to reduce multiple constructors into fewer constructors. For example, by putting a default value on our id parameter, we can create a single Employee constructor that requires a name argument but will optionally accept an id argument:

        class Employee
        {
        private:
            std::string m_name{};
            int m_id{ 0 }; // default member initializer

        public:

            Employee(std::string_view name, int id = 0) // default argument for id
                : m_name{ name }, m_id{ id }
            {
                std::cout << "Employee " << m_name << " created\n";
            }
        };

        - Since default values must be attached to the rightmost parameters in a function call, a good practice when defining classes is to define members for which a user must provide initialization values for first (and then make those the leftmost parameters of the constructor). Members for which the user can optionally provide (because the default values are acceptable) should be defined second (and then make those the rightmost parameters of the constructor).


        - Members for which the user must provide initialization values should be defined first (and as the leftmost parameters of the constructor). Members for which the user can optionally provide initialization values (because the default values are acceptable) should be defined second (and as the rightmost parameters of the constructor).

    6. A conundrum: Redundant constructors vs redundant default values - 

        - In the above examples, we used delegating constructors and then default arguments to reduce constructor redundancy. But both of these methods required us to duplicate initialization values for our members in various places. Unfortunately, there is currently no way to specify that a delegating constructor or default argument should use the default member initializer value.

        - There are various opinions about whether it is better to have fewer constructors (with duplication of initialization values) or more constructors (with no duplication of initialization values). Our opinion is that it’s usually more straightforward to have fewer constructors, even if it results in duplication of initialization values.

        - When we have an initialization value that is used in multiple places (e.g. as a default member initializer and a default argument for a constructor parameter), we can instead define a named constant and use that wherever our initialization value is needed. This allows the initialization value to be defined in one place.

        The best way to do this is to use a static constexpr member inside the class:

            class Employee
            {
            private:
                static constexpr int default_id { 0 }; // define a named constant with our desired initialization value

                std::string m_name{};
                int m_id{ default_id }; // we can use it here

            public:

                Employee(std::string_view name, int id = default_id) // and we can use it here
                    : m_name{ name }, m_id{ id }
                {
                    std::cout << "Employee " << m_name << " created\n";
                }
            };


*/
int main()
{
    return 0;
}