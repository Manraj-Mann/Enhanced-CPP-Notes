#include <iostream>

/*
    Notes : 

    1. Calling a base class function : When a member function is called on a derived class object, the compiler first looks to see if any function with that name exists in the derived class. If so, all overloaded functions with that name are considered, and the function overload resolution process is used to determine whether there is a best match. If not, the compiler walks up the inheritance chain, checking each parent class in turn in the same way.

    2. Redefining behaviors : 

        class Base
        {
        public:
            Base() { }

            void identify() const { std::cout << "Base::identify()\n"; }
        };

        class Derived: public Base
        {
        public:
            Derived() { }

            void identify() const { std::cout << "Derived::identify()\n"; }
        };

        int main()
        {
            Base base {};
            base.identify();

            Derived derived {};
            derived.identify();

            return 0;
        }

        - Note that when you redefine a function in the derived class, the derived function does not inherit the access specifier of the function with the same name in the base class. It uses whatever access specifier it is defined under in the derived class. Therefore, a function that is defined as private in the base class can be redefined as public in the derived class, or vice-versa!

    3. Adding to existing functionality : Sometimes we don’t want to completely replace a base class function, but instead want to add additional functionality to it when called with a derived object. In the above example, note that Derived::identify() completely hides Base::identify()! This may not be what we want. It is possible to have our derived function call the base version of the function of the same name (in order to reuse code) and then add additional functionality to it.

        class Base
        {
        public:
            Base() { }

            void identify() const { std::cout << "Base::identify()\n"; }
        };

        class Derived: public Base
        {
        public:
            Derived() { }

            void identify() const
            {
                std::cout << "Derived::identify()\n";
                Base::identify(); // note call to Base::identify() here
            }
        };

        int main()
        {
            Base base {};
            base.identify();

            Derived derived {};
            derived.identify();

            return 0;
        }

    4. Friend Function Resolution : There’s one bit of trickiness that we can run into when trying to call friend functions in base classes, such as operator<<. Because friend functions of the base class aren’t actually part of the base class, using the scope resolution qualifier won’t work. Instead, we need a way to make our Derived class temporarily look like the Base class so that the right version of the function can be called.

        class Base
        {
        public:
            Base() { }

            friend std::ostream& operator<< (std::ostream& out, const Base&)
            {
                out << "In Base\n";
                return out;
            }
        };

        class Derived: public Base
        {
        public:
            Derived() { }

            friend std::ostream& operator<< (std::ostream& out, const Derived& d)
            {
                out << "In Derived\n";
                // static_cast Derived to a Base object, so we call the right version of operator<<
                out << static_cast<const Base&>(d);
                return out;
            }
        };

        int main()
        {
            Derived derived {};

            std::cout << derived << '\n';

            return 0;
        }

    5. Overload resolution in derived classes : As noted at the top of the lesson, the compiler will select the best matching function from the most-derived class with at least one function with that name.

        - Consider the following example : 

            class Base
            {
            public:
                void print(int)    { std::cout << "Base::print(int)\n"; }
                void print(double) { std::cout << "Base::print(double)\n"; }
            };

            class Derived: public Base
            {
            public:
                void print(double) { std::cout << "Derived::print(double)"; } // this function added
            };


            int main()
            {
                Derived d{};
                d.print(5); // calls Derived::print(double), not Base::print(int)

                return 0;
            }

        - For the call d.print(5), the compiler finds one function named print() in Derived, therefore it will only consider functions in Derived when trying to determine what function to resolve to. This function is also the best matching function in Derived for this function call. Therefore, this calls Derived::print(double).

        - Since Base::print(int) has a parameter that is a better match for int argument 5 than Derived::print(double), you may have been expecting this function call to resolve to Base::print(int). But because d is a Derived, there is at least one print() function in Derived, and Derived is more derived than Base, the functions in Base are not even considered.

        - A better option is to use a using-declaration in Derived to make all Base functions with a certain name visible from within Derived:

            class Base
            {
            public:
                void print(int)    { std::cout << "Base::print(int)\n"; }
                void print(double) { std::cout << "Base::print(double)\n"; }
            };

            class Derived: public Base
            {
            public:
                using Base::print; // make all Base::print() functions eligible for overload resolution
                void print(double) { std::cout << "Derived::print(double)"; }
            };


            int main()
            {
                Derived d{};
                d.print(5); // calls Base::print(int), which is the best matching function visible in Derived

                return 0;
            }

        - By putting the using-declaration using Base::print; inside Derived, we are telling the compiler that all Base functions named print should be visible in Derived, which will cause them to be eligible for overload resolution. As a result, Base::print(int) is selected over Derived::print(double).

*/
int main()
{
    return 0;
}