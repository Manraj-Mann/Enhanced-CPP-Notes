#include <iostream>


/*
    Notes : 

    1. The object being returned by reference must exist after the function returns.

    2. Lifetime extension doesn’t work across function boundaries. Reference lifetime extension does not work across function boundaries.

    3. Don’t return non-const static local variables by reference

        const int& getNextId()
        {
            static int s_x{ 0 }; // note: variable is non-const
            ++s_x; // generate the next id
            return s_x; // and return a reference to it
        }

        const int& id1 { getNextId() }; // id1 is a reference
        const int& id2 { getNextId() }; // id2 is a reference

        This program prints:

        22

        This happens because id1 and id2 are referencing the same object (the static variable s_x), so when anything (e.g. getNextId()) modifies that value, all references are now accessing the modified value.

    4. Assigning/initializing a normal variable with a returned reference makes a copy - 

        const int& getNextId()
        {
            static int s_x{ 0 };
            ++s_x;
            return s_x;
        }

        const int id1 { getNextId() }; // id1 is a normal variable now and receives a copy of the value returned by reference from getNextId()
        const int id2 { getNextId() }; // id2 is a normal variable now and receives a copy of the value returned by reference from getNextId()

    5. It’s okay to return reference parameters by reference - 

        // Takes two std::string objects, returns the one that comes first alphabetically
        const std::string& firstAlphabetical(const std::string& a, const std::string& b)
        {
            return (a < b) ? a : b; // We can use operator< on std::string to determine which comes first alphabetically
        }
        
        std::string hello { "Hello" };
	    std::string world { "World" };

	    std::cout << firstAlphabetical(hello, world) << '\n';

    6. It’s okay to return by const reference an rvalue passed by const reference - 

        When an argument for a const reference parameter is an rvalue, it’s still okay to return that parameter by const reference. This is because rvalues are not destroyed until the end of the full expression in which they are created.

        std::string getHello()
        {
            return std::string{"Hello"};
        }

        const std::string s{ getHello() };

        In this case, getHello() returns a std::string by value, which is an rvalue. This rvalue is then used to initialize s. After the initialization of s, the expression in which the rvalue was created has finished evaluating, and the rvalue is destroyed.

        const std::string& foo(const std::string& s)
        {
            return s;
        }

        std::string getHello()
        {
            return std::string{"Hello"};
        }

        const std::string s{ foo(getHello()) };

        The only difference in this case is that the rvalue is passed by const reference to foo() and then returned by const reference back to the caller before it is used to initialize s. Everything else works identically. These are also called access functions.

    7. The caller can modify values through the reference - The caller can modify values through the reference.

        // takes two integers by non-const reference, and returns the greater by reference
        int& max(int& x, int& y)
        {
            return (x > y) ? x : y;
        }

        int a{ 5 };
        int b{ 6 };

        max(a, b) = 7; // sets the greater of a or b to 7

    8. Return by address - Return by address works almost identically to return by reference, except a pointer to an object is returned instead of a reference to an object. Return by address has the same primary caveat as return by reference -- the object being returned by address must outlive the scope of the function returning the address, otherwise the caller will receive a dangling pointer. 

    Prefer return by reference over return by address unless the ability to return “no object” (using nullptr) is important.




*/

#include <string>

const int& getNextId()
{
    static int s_x{ 0 }; // note: variable is non-const
    ++s_x; // generate the next id
    return s_x; // and return a reference to it
}

// Takes two std::string objects, returns the one that comes first alphabetically
const std::string& firstAlphabetical(const std::string& a, const std::string& b)
{
	return (a < b) ? a : b; // We can use operator< on std::string to determine which comes first alphabetically
}

std::string getHello()
{
    return std::string{"Hello"};
}


int main()
{
    const int& id1 { getNextId() }; // id1 is a reference
    const int& id2 { getNextId() }; // id2 is a reference

    std::cout << id1 << id2 << '\n';

    std::string hello { "Hello" };
	std::string world { "World" };

	std::cout << firstAlphabetical(hello, world) << '\n';

    const std::string s{ getHello() };

    std::cout << s;

    return 0;
}