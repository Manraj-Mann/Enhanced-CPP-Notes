#include <iostream>
/* 
    Notes : Virtual destructors, virtual assignment, and overriding virtualization 
    
    1. Virtual destructors : 

        - Although C++ provides a default destructor for your classes if you do not provide one yourself, it is sometimes the case that you will want to provide your own destructor (particularly if the class needs to deallocate memory). You should always make your destructors virtual if you’re dealing with inheritance. Consider the following example:

            class Base
            {
            public:
                ~Base() // note: not virtual
                {
                    std::cout << "Calling ~Base()\n";
                }
            };

            class Derived: public Base
            {
            private:
                int* m_array {};

            public:
                Derived(int length)
                : m_array{ new int[length] }
                {
                }

                ~Derived() // note: not virtual (your compiler may warn you about this)
                {
                    std::cout << "Calling ~Derived()\n";
                    delete[] m_array;
                }
            };

            int main()
            {
                Derived* derived { new Derived(5) };
                Base* base { derived };

                delete base;

                return 0;
            }

        - Because base is a Base pointer, when base is deleted, the program looks to see if the Base destructor is virtual. It’s not, so it assumes it only needs to call the Base destructor. We can see this in the fact that the above example prints:

            Calling ~Base()

        - However, we really want the delete function to call Derived’s destructor (which will call Base’s destructor in turn), otherwise m_array will not be deleted. We do this by making Base’s destructor virtual:

            class Base
            {
            public:
                virtual ~Base() // note: virtual
                {
                    std::cout << "Calling ~Base()\n";
                }
            };

            class Derived: public Base
            {
            private:
                int* m_array {};

            public:
                Derived(int length)
                : m_array{ new int[length] }
                {
                }

                virtual ~Derived() // note: virtual
                {
                    std::cout << "Calling ~Derived()\n";
                    delete[] m_array;
                }
            };

            int main()
            {
                Derived* derived { new Derived(5) };
                Base* base { derived };

                delete base;

                return 0;
            }

        - Whenever you are dealing with inheritance, you should make any explicit destructors virtual. As with normal virtual member functions, if a base class function is virtual, all derived overrides will be considered virtual regardless of whether they are specified as such. It is not necessary to create an empty derived class destructor just to mark it as virtual. Note that if you want your base class to have a virtual destructor that is otherwise empty, you can define your destructor this way:

            virtual ~Base() = default; // generate a virtual default destructor


    2. Virtual assignment - It is possible to make the assignment operator virtual. However, unlike the destructor case where virtualization is always a good idea, virtualizing the assignment operator really opens up a bag full of worms and gets into some advanced topics outside of the scope of this tutorial. Consequently, we are going to recommend you leave your assignments non-virtual for now, in the interest of simplicity.

    3. Ignoring virtualization - Very rarely you may want to ignore the virtualization of a function. For example, consider the following code:

            class Base
            {
            public:
                virtual ~Base() = default;
                virtual std::string_view getName() const { return "Base"; }
            };

            class Derived: public Base
            {
            public:
                virtual std::string_view getName() const { return "Derived"; }
            };

        - There may be cases where you want a Base pointer to a Derived object to call Base::getName() instead of Derived::getName(). To do so, simply use the scope resolution operator:

            int main()
            {
                Derived derived {};
                const Base& base { derived };

                // Calls Base::getName() instead of the virtualized Derived::getName()
                std::cout << base.Base::getName() << '\n';

                return 0;
            }

    4. Should we make all destructors virtual?

        - This is a common question asked by new programmers. As noted in the top example, if the base class destructor isn’t marked as virtual, then the program is at risk for leaking memory if a programmer later deletes a base class pointer that is pointing to a derived object. One way to avoid this is to mark all your destructors as virtual. But should you?

        - It’s easy to say yes, so that way you can later use any class as a base class -- but there’s a performance penalty for doing so (a virtual pointer added to every instance of your class). So you have to balance that cost, as well as your intent.

        - We’d suggest the following: If a class isn’t explicitly designed to be a base class, then it’s generally better to have no virtual members and no virtual destructor. The class can still be used via composition. If a class is designed to be used as a base class and/or has any virtual functions, then it should always have a virtual destructor.

*/
int main()
{
    return 0;
}