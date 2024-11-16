#include <iostream>
/* 
    Notes :  
    
    1.  Printing Derived classes : 
    
        class Base
        {
        public:
            virtual void print() const { std::cout << "Base"; }

            friend std::ostream& operator<<(std::ostream& out, const Base& b)
            {
                out << "Base";
                return out;
            }
        };

        class Derived : public Base
        {
        public:
            void print() const override { std::cout << "Derived"; }

            friend std::ostream& operator<<(std::ostream& out, const Derived& d)
            {
                out << "Derived";
                return out;
            }
        };

        int main()
        {
            Base b{};
            std::cout << b << '\n';

            Derived d{};
            std::cout << d << '\n';

            return 0;
        }

    2. Can we make operator<< virtual? 

        - If this issue is that operator<< isn’t virtual, can’t we simply make it virtual? The short answer is no. There are a number of reasons for this.

        - First, only member functions can be virtualized -- this makes sense, since only classes can inherit from other classes, and there’s no way to override a function that lives outside of a class (you can overload non-member functions, but not override them). Because we typically implement operator<< as a friend, and friends aren’t considered member functions, a friend version of operator<< is ineligible to be virtualized. (For a review of why we implement operator<< this way, please revisit lesson 21.5 -- Overloading operators using member functions).

        - Second, even if we could virtualize operator<< there’s the problem that the function parameters for Base::operator<< and Derived::operator<< differ (the Base version would take a Base parameter and the Derived version would take a Derived parameter). Consequently, the Derived version wouldn’t be considered an override of the Base version, and thus be ineligible for virtual function resolution.

    3. Solution : The answer, as it turns out, is surprisingly simple.

        - First, we set up operator<< as a friend in our base class as usual. But rather than have operator<< determine what to print, we will instead have it call a normal member function that can be virtualized! This virtual function will do the work of determining what to print for each class.

            class Base
            {
            public:
                // Here's our overloaded operator<<
                friend std::ostream& operator<<(std::ostream& out, const Base& b)
                {
                    // Call virtual function identify() to get the string to be printed
                    out << b.identify();
                    return out;
                }

                // We'll rely on member function identify() to return the string to be printed
                // Because identify() is a normal member function, it can be virtualized
                virtual std::string identify() const
                {
                    return "Base";
                }
            };

            class Derived : public Base
            {
            public:
                // Here's our override identify() function to handle the Derived case
                std::string identify() const override
                {
                    return "Derived";
                }
            };

            int main()
            {
                Base b{};
                std::cout << b << '\n';

                Derived d{};
                std::cout << d << '\n'; // note that this works even with no operator<< that explicitly handles Derived objects

                Base& bref{ d };
                std::cout << bref << '\n';

                return 0;
            }

    4. A more flexible solution : The above solution works great, but has two potential shortcomings:

        1. It makes the assumption that the desired output can be represented as a single std::string.
        
        2. Our identify() member function does not have access to the stream object.

        - The latter is problematic in cases where we need a stream object, such as when we want to print the value of a member variable that has an overloaded operator<<. Fortunately, it’s straightforward to modify the above example to resolve both of these issues. In the previous version, virtual function identify() returned a string to be printed by Base::operator<<. In this version, we’ll instead define virtual member function print() and delegate responsibility for printing directly to that function.

            class Base
            {
            public:
                // Here's our overloaded operator<<
                friend std::ostream& operator<<(std::ostream& out, const Base& b)
                {
                    // Delegate printing responsibility for printing to virtual member function print()
                    return b.print(out);
                }

                // We'll rely on member function print() to do the actual printing
                // Because print() is a normal member function, it can be virtualized
                virtual std::ostream& print(std::ostream& out) const
                {
                    out << "Base";
                    return out;
                }
            };

            // Some class or struct with an overloaded operator<<
            struct Employee
            {
                std::string name{};
                int id{};

                friend std::ostream& operator<<(std::ostream& out, const Employee& e)
                {
                    out << "Employee(" << e.name << ", " << e.id << ")";
                    return out;
                }
            };

            class Derived : public Base
            {
            private:
                Employee m_e{}; // Derived now has an Employee member

            public:
                Derived(const Employee& e)
                    : m_e{ e }
                {
                }

                // Here's our override print() function to handle the Derived case
                std::ostream& print(std::ostream& out) const override
                {
                    out << "Derived: ";

                    // Print the Employee member using the stream object
                    out << m_e;

                    return out;
                }
            };

            int main()
            {
                Base b{};
                std::cout << b << '\n';

                Derived d{ Employee{"Jim", 4}};
                std::cout << d << '\n'; // note that this works even with no operator<< that explicitly handles Derived objects

                Base& bref{ d };
                std::cout << bref << '\n';

                return 0;
            }



*/

class Base
{
public:
	// Here's our overloaded operator<<
	friend std::ostream& operator<<(std::ostream& out, const Base& b)
	{
		// Call virtual function identify() to get the string to be printed
		out << b.identify();
		return out;
	}

	// We'll rely on member function identify() to return the string to be printed
	// Because identify() is a normal member function, it can be virtualized
	virtual std::string identify() const
	{
		return "Base";
	}
};

class Derived : public Base
{
public:
	// Here's our override identify() function to handle the Derived case
	std::string identify() const override
	{
		return "Derived";
	}
};

int main()
{
	Base b{};
	std::cout << b << '\n';

	Derived d{};
	std::cout << d << '\n'; // note that this works even with no operator<< that explicitly handles Derived objects

	Base& bref{ d };
	std::cout << bref << '\n';

	return 0;
}