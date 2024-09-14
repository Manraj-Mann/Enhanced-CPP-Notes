#include <iostream>
#include <typeinfo>

/*
    Notes : 

    1.  The address-of operator (&) returns the memory address of its operand. This is pretty straightforward:

        = std::cout << &x << '\n'; // print the memory address of variable x

        For objects that use more than one byte of memory, address-of will return the memory address of the first byte used by the object.

    2. The dereference operator (*)  - Getting the address of a variable isn’t very useful by itself.

        The most useful thing we can do with an address is access the value stored at that address. The dereference operator (*) (also occasionally called the indirection operator) returns the value at a given memory address as an "lvalue":

        = std::cout << *(&x) << '\n'; // print the value at the memory address of variable x (parentheses not required, but make it easier to read)

    3. The address-of operator (&) and dereference operator (*) work as opposites: address-of gets the address of an object, and dereference gets the object at an address.

    4. Pointers - A pointer is an object that holds a memory address (typically of another variable) as its value. This allows us to store the address of some other object to use later.In modern C++, the pointers we are talking about here are sometimes called “raw pointers” or “dumb pointers”, to help differentiate them from “smart pointers” that were introduced into the language more recently. 

        - int;  // a normal int
        - int&; // an lvalue reference to an int value

        - int*; // a pointer to an int value (holds the address of an integer value)

    When declaring a pointer type, place the asterisk next to the type name.

    5. Pointer initialization - 

        Like normal variables, pointers are not initialized by default. 
        
        5.1. A pointer that has not been initialized is sometimes called a wild pointer. 
        
        5.2. Wild pointers contain a garbage address, and dereferencing a wild pointer will result in undefined behavior. Because of this, you should always initialize your pointers to a known value.

        Example : 
        
            - int* ptr;        // an uninitialized pointer (holds a garbage address)
            - int* ptr2{};     // a null pointer (we'll discuss these in the next lesson)
            - int* ptr3{ &x }; // a pointer initialized with the address of variable x

        5.3. Once we have a pointer holding the address of another object, we can then use the dereference operator (*) to access the value at that address. 

        Example : 

            - int* ptr{ &x }; // ptr holds the address of x
            - std::cout << *ptr << '\n'; // use dereference operator to print the value at the address that ptr is holding (which is x's address)
    
    6. Pointers and assignment - We can use assignment with pointers in two different ways:

        - To change what the pointer is pointing at (by assigning the pointer a new address)

            int x{ 5 };
            int* ptr{ &x }; // ptr initialized to point at x

            std::cout << *ptr << '\n'; // print the value at the address being pointed to (x's address)

            int y{ 6 };
            ptr = &y; // // change ptr to point at y


        - To change the value being pointed at (by assigning the dereferenced pointer a new value)

            int x{ 5 };
            int* ptr{ &x }; // initialize ptr with address of variable x

            std::cout << x << '\n';    // print x's value
            std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)

            *ptr = 6; // The object at the address held by ptr (x) assigned value 6 (note that ptr is dereferenced here)


    7. Key insight - 
        
        - When we use a pointer without a dereference (ptr), we are accessing the address held by the pointer. Modifying this (ptr = &y) changes what the pointer is pointing at.

        - When we dereference a pointer (*ptr), we are accessing the object being pointed at. Modifying this (*ptr = 6;) changes the value of the object being pointed at.

    8. Pointers behave much like lvalue references - Pointers and lvalue references behave similarly.

        Example : 

            int x{ 5 };
            int& ref { x };  // get a reference to x
            int* ptr { &x }; // get a pointer to x

            std::cout << x;
            std::cout << ref;  // use the reference to print x's value (5)
            std::cout << *ptr << '\n'; // use the pointer to print x's value (5)

            ref = 6; // use the reference to change the value of x
            std::cout << x;
            std::cout << ref;  // use the reference to print x's value (6)
            std::cout << *ptr << '\n'; // use the pointer to print x's value (6)

            *ptr = 7; // use the pointer to change the value of x
            std::cout << x;
            std::cout << ref;  // use the reference to print x's value (7)
            std::cout << *ptr << '\n'; // use the pointer to print x's value (7)

    9. There are some other differences between pointers and references worth mentioning:

        - References must be initialized, pointers are not required to be initialized (but should be).
        - References are not objects, pointers are.
        - References can not be reseated (changed to reference something else), pointers can change what they are pointing at.
        - References must always be bound to an object, pointers can point to nothing .
        - References are “safe” (outside of dangling references), pointers are inherently dangerous .

    10. The address-of operator returns a pointer - It’s worth noting that the address-of operator (&) doesn’t return the address of its operand as a literal. Instead, it returns a pointer containing the address of the operand, whose type is derived from the argument (e.g. taking the address of an int will return the address in an int pointer).

        int x{ 4 };
	    std::cout << typeid(&x).name() << '\n'; // print the type of &x

    11. The size of pointers - The size of a pointer is dependent upon the architecture the executable is compiled for -- a 32-bit executable uses 32-bit memory addresses -- consequently, a pointer on a 32-bit machine is 32 bits (4 bytes). With a 64-bit executable, a pointer would be 64 bits (8 bytes). Note that this is true regardless of the size of the object being pointed to:

    Example : 

        - char* chPtr{};        // chars are 1 byte
        - int* iPtr{};          // ints are usually 4 bytes
        - long double* ldPtr{}; // long doubles are usually 8 or 12 bytes

        - std::cout << sizeof(chPtr) << '\n'; // prints 4
        - std::cout << sizeof(iPtr) << '\n';  // prints 4
        - std::cout << sizeof(ldPtr) << '\n'; // prints 4

    The size of the pointer is always the same. This is because a pointer is just a memory address, and the number of bits needed to access a memory address is constant.

    12. Dangling pointers - Much like a dangling reference, a dangling pointer is a pointer that is holding the address of an object that is no longer valid (e.g. because it has been destroyed).Dereferencing a dangling pointer (e.g. in order to print the value being pointed at) will lead to undefined behavior, as you are trying to access an object that is no longer valid.


*/


int main()
{
    int x{10};
    std::cout<<&x<<std::endl;

    std::cout << *(&x) << '\n'; // print the value at the memory address of variable x (parentheses not required, but make it easier to read)

    std::cout << &(*(&x)) << '\n'; // verify if it is an l value


    // Pointers and assignment
    {
        int x{ 5 };
        int* ptr{ &x }; // ptr initialized to point at x

        std::cout << *ptr << '\n'; // print the value at the address being pointed to (x's address)

        int y{ 6 };
        ptr = &y; // change ptr to point at y

        std::cout << *ptr << '\n'; // print the value at the address being pointed to (y's address)
    }

    {
        int x{ 5 };
        int* ptr{ &x }; // initialize ptr with address of variable x

        std::cout << x << '\n';    // print x's value
        std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)

        *ptr = 6; // The object at the address held by ptr (x) assigned value 6 (note that ptr is dereferenced here)

        std::cout << x << '\n';
        std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)
    }

    // Pointers behave much like lvalue references
    {
        int x{ 5 };
        int& ref { x };  // get a reference to x
        int* ptr { &x }; // get a pointer to x

        std::cout << x;
        std::cout << ref;  // use the reference to print x's value (5)
        std::cout << *ptr << '\n'; // use the pointer to print x's value (5)

        ref = 6; // use the reference to change the value of x
        std::cout << x;
        std::cout << ref;  // use the reference to print x's value (6)
        std::cout << *ptr << '\n'; // use the pointer to print x's value (6)

        *ptr = 7; // use the pointer to change the value of x
        std::cout << x;
        std::cout << ref;  // use the reference to print x's value (7)
        std::cout << *ptr << '\n'; // use the pointer to print x's value (7)
    }

    {
        int x{ 4 };
	    std::cout << typeid(&x).name() << '\n'; // print the type of &x
    }

    {
        char* chPtr{};        // chars are 1 byte
        int* iPtr{};          // ints are usually 4 bytes
        long double* ldPtr{}; // long doubles are usually 8 or 12 bytes

        std::cout << sizeof(chPtr) << '\n'; // prints 4
        std::cout << sizeof(iPtr) << '\n';  // prints 4
        std::cout << sizeof(ldPtr) << '\n'; // prints 4
    }

    // dangling pointers
    {
        int x{ 5 };
        int* ptr{ &x };

        std::cout << *ptr << '\n'; // valid

        {
            int y{ 6 };
            ptr = &y;

            std::cout << *ptr << '\n'; // valid
        } // y goes out of scope, and ptr is now dangling

        std::cout << *ptr << '\n'; // undefined behavior from dereferencing a dangling pointer
    }


    return 0;
}