#include <iostream>

/*
    Notes : 

    1. Pass by address - C++ provides a third way to pass values to a function, called pass by address. With pass by address, instead of providing an object as an argument, the caller provides an object’s address (via a pointer). This pointer (holding the address of the object) is copied into a pointer parameter of the called function (which now also holds the address of the object). The function can then dereference that pointer to access the object whose address was passed.

    Example : 

        void printByAddress(const std::string* ptr) // The function parameter is a pointer that holds the address of str
        {
            std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
        }

    2. Pass by address does not make a copy of the object being pointed to - 

        std::string str{ "Hello, world!" };
        printByAddress(&str); // use address-of operator (&) to get pointer holding address of str

        When we pass a std::string by address, we’re not copying the actual std::string object -- we’re just copying the pointer (holding the address of the object) from the caller to the called function. Since an address is typically only 4 or 8 bytes, a pointer is only 4 or 8 bytes, so copying a pointer is always fast.

    3. Pass by address allows the function to modify the argument’s value - 

        void changeValue(const int* ptr) // note: ptr is now a pointer to a const
        {
            *ptr = 6; // error: can not change const value
        }

    4. Null checking - When passing a parameter by address, care should be taken to ensure the pointer is not a null pointer before you dereference the value. One way to do that is to use a conditional statement:

        void print(int* ptr)
        {
            if (ptr) // if ptr is not a null pointer
            {
                std::cout << *ptr << '\n';
            }
        }


    5. Prefer pass by (const) reference - 

        - Pass by reference has the same benefits as pass by address without the risk of inadvertently dereferencing a null pointer.

        - Pass by const reference has a few other advantages over pass by address.

        - First, because an object being passed by address must have an address, only lvalues can be passed by address (as rvalues don’t have addresses). Pass by const reference is more flexible, as it can accept lvalues and rvalues:

            Example : 

            void printByValue(int val) // The function parameter is a copy of the argument
            {
                std::cout << val << '\n'; // print the value via the copy
            }

            void printByReference(const int& ref) // The function parameter is a reference that binds to the argument
            {
                std::cout << ref << '\n'; // print the value via the reference
            }

            void printByAddress(const int* ptr) // The function parameter is a pointer that holds the address of the argument
            {
                std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
            }

            MAIN : 

            printByValue(5);     // valid (but makes a copy)
            printByReference(5); // valid (because the parameter is a const reference)
            printByAddress(&5);  // error: can't take address of r-value

        - Second, the syntax for pass by reference is natural, as we can just pass in literals or objects. With pass by address, our code ends up littered with ampersands (&) and asterisks (*).

    6. Prefer pass by reference to pass by address unless you have a specific reason to use pass by address.

    7. Pass by address for “optional” arguments - One of the more common uses for pass by address is to allow a function to accept an “optional” argument.

        void printIDNumber(const int *id=nullptr)
        {
            if (id)
                std::cout << "Your ID number is " << *id << ".\n";
            else
                std::cout << "Your ID number is not known.\n";
        }

        This has a number of advantages: we no longer have to worry about null dereferences, and we can pass in literals or other rvalues as an argument.

    8. Pass by address… by reference?

        Yup, it’s a thing. Just like we can pass a normal variable by reference, we can also pass pointers by reference. 

        void nullify(int*& refptr) // refptr is now a reference to a pointer
        {
            refptr = nullptr; // Make the function parameter a null pointer
        }

        int x{ 5 };
        int* ptr{ &x }; // ptr points to x

        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

        nullify(ptr);

        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

    9. std::nullptr_t - 

        Since nullptr can be differentiated from integer values in function overloads, it must have a different type. So what type is nullptr? The answer is that nullptr has type std::nullptr_t (defined in header <cstddef>). std::nullptr_t can only hold one value: nullptr! While this may seem kind of silly, it’s useful in one situation. If we want to write a function that accepts only a nullptr literal argument, we can make the parameter a std::nullptr_t.

    10. While the compiler can often optimize references away entirely, there are cases where this is not possible and a reference is actually needed. References are normally implemented by the compiler using pointers. This means that behind the scenes, pass by reference is essentially just a pass by address. Therefore, we can conclude that C++ really passes everything by value! The properties of pass by address (and reference) come solely from the fact that we can dereference the passed address to change the argument, which we can not do with a normal value parameter!
    

*/

void printByValue(int val) // The function parameter is a copy of the argument
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const int& ref) // The function parameter is a reference that binds to the argument
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const int* ptr) // The function parameter is a pointer that holds the address of the argument
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    printByValue(5);     // valid (but makes a copy)
    printByReference(5); // valid (because the parameter is a const reference)
    // printByAddress(&5);  // error: can't take address of r-value

    return 0;
}