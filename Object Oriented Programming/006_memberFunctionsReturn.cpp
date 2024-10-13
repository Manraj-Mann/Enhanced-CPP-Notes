#include <iostream>
/* 
    Notes :  
    
    1. “The object being returned by reference must exist after the function returns”. This means we should not return local variables by reference, as the reference will be left dangling after the local variable is destroyed. However, it is generally okay to return by reference either function parameters passed by reference, or variables with static duration (either static local variables or global variables), as they will generally not be destroyed after the function returns.

    2. Returning data members by value can be expensive - 

        class Employee
        {
            std::string m_name{};

        public:
            void setName(std::string_view name) { m_name = name; }
            std::string getName() const { return m_name; } //  getter returns by value
        };

        In this example, the getName() access function returns std::string m_name by value.

        While this is the safest thing to do, it also means that an expensive copy of m_name will be made every time getName() is called. Since access functions tend to be called a lot, this is generally not the best choice.

    3. Returning data members by lvalue reference - 

        - Member functions can also return data members by (const) lvalue reference.

        - Data members have the same lifetime as the object containing them. Since member functions are always called on an object, and that object must exist in the scope of the caller, it is generally safe for a member function to return a data member by (const) lvalue reference (as the member being returned by reference will still exist in the scope of the caller when the function returns).

        Example : 

            class Employee
            {
                std::string m_name{};

            public:
                void setName(std::string_view name) { m_name = name; }
                const std::string& getName() const { return m_name; } //  getter returns by const reference
            };

        - It is okay to return a (const) lvalue reference to a data member. The implicit object (containing the data member) still exists in the scope of the caller after the function returns, so any returned references will be valid.

    4. The return type of a member function returning a reference to a data member should match the data member’s type - 

        - In general, the return type of a member function returning by reference should match the type of the data member being returned. In the above example, m_name is of type std::string, so getName() returns const std::string&.

        - Returning a std::string_view would require a temporary std::string_view to be created and returned every time the function was called. That’s needlessly inefficient. If the caller wants a std::string_view, they can do the conversion themselves.

        - For getters, using auto to have the compiler deduce the return type from the member being returned is a useful way to ensure that no conversions occur:

            class Employee
            {
                std::string m_name{};

            public:
                void setName(std::string_view name) { m_name = name; }
                const auto& getName() const { return m_name; } // uses `auto` to deduce return type from m_name
            };

    5. Rvalue implicit objects and return by reference - 

        - But what if our implicit object is an rvalue instead (such as the return value of some function that returns by value)? Rvalue objects are destroyed at the end of the full expression in which they are created. When an rvalue object is destroyed, any references to members of that rvalue will be invalidated and left dangling, and use of such references will produce undefined behavior.

        - Therefore, a reference to a member of an rvalue object can only be safely used within the full expression where the rvalue object is created.

        - An rvalue object is destroyed at the end of the full expression in which it is created. Any references to members of the rvalue object are left dangling at that point. A reference to a member of an rvalue object can only be safely used within the full expression where the rvalue object is created.

        Example : 

            class Employee
            {
                std::string m_name{};

            public:
                void setName(std::string_view name) { m_name = name; }
                const std::string& getName() const { return m_name; } //  getter returns by const reference
            };

            // createEmployee() returns an Employee by value (which means the returned value is an rvalue)
            Employee createEmployee(std::string_view name)
            {
                Employee e;
                e.setName(name);
                return e;
            }

            int main()
            {
                // Case 1: okay: use returned reference to member of rvalue class object in same expression
                std::cout << createEmployee("Frank").getName();

                // Case 2: bad: save returned reference to member of rvalue class object for use later
                const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
                std::cout << ref; // undefined behavior

                // Case 3: okay: copy referenced value to local variable for use later
                std::string val { createEmployee("Hans").getName() }; // makes copy of referenced member
                std::cout << val; // okay: val is independent of referenced member

                return 0;
            }
    
    6. Using member functions that return by reference safely - 

        - Despite the potential danger with rvalue implicit objects, it is conventional for getters to return types that are expensive to copy by const reference, not by value.

        - Prefer to use the return value of a member function that returns by reference immediately, to avoid issues with dangling references when the implicit object is an rvalue.

    7. Do not return non-const references to private data members : Because a reference acts just like the object being referenced, a member function that returns a non-const reference provides direct access to that member (even if the member is private).

        class Foo
        {
        private:
            int m_value{ 4 }; // private member

        public:
            int& value() { return m_value; } // returns a non-const reference (don't do this)
        };

        int main()
        {
            Foo f{};                // f.m_value is initialized to default value 4
            f.value() = 5;          // The equivalent of m_value = 5
            std::cout << f.value(); // prints 5

            return 0;
        }

    8. Const member functions can’t return non-const references to data members - 

*/

#include <string_view>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(std::string_view name)
{
	Employee e;
	e.setName(name);
	return e;
}

int main()
{
	// Case 1: okay: use returned reference to member of rvalue class object in same expression
	std::cout << createEmployee("Frank").getName();

	// Case 2: bad: save returned reference to member of rvalue class object for use later
	const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
	std::cout << ref; // undefined behavior

	// Case 3: okay: copy referenced value to local variable for use later
	std::string val { createEmployee("Hans").getName() }; // makes copy of referenced member
	std::cout << val; // okay: val is independent of referenced member

	return 0;
}