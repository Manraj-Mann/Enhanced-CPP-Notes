#include <iostream>

/*
    Notes : 

    1. Pointer to const value -  A pointer to a const value (sometimes called a pointer to const for short) is a (non-const) pointer that points to a constant value.

        const int x{ 5 };
        const int* ptr { &x }; // okay: ptr is pointing to a "const int"

        *ptr = 6; // not allowed: we can't change a const value

    2. However, because a pointer to const is not const itself (it just points to a const value), we can change what the pointer is pointing at by assigning the pointer a new address:

        const int y{ 6 };
        ptr = &y; // okay: ptr now points at const int y

    3. Just like a reference to const, a pointer to const can point to non-const variables too. A pointer to const treats the value being pointed to as constant, regardless of whether the object at that address was initially defined as const or not:

        int x{ 5 }; // non-const
        const int* ptr { &x }; // ptr points to a "const int"

        *ptr = 6;  // not allowed: ptr points to a "const int" so we can't change the value through ptr
        x = 6; // allowed: the value is still non-const when accessed through non-const identifier x

    4. Const pointers - We can also make a pointer itself constant. A const pointer is a pointer whose address can not be changed after initialization.

        To declare a const pointer, use the const keyword after the asterisk in the pointer declaration:

        Example : 

            int x{ 5 };
            int* const ptr { &x }; // const after the asterisk means this is a const pointer

            int* const ptr { &x }; // okay: the const pointer is initialized to the address of x
            ptr = &y; // error: once initialized, a const pointer can not be changed.

        However, because the value being pointed to is non-const, it is possible to change the value being pointed to via dereferencing the const pointer:

        Example : 

            int x{ 5 };
            int* const ptr { &x }; // ptr will always point to x

            *ptr = 6; // okay: the value being pointed to is non-const

    5. Const pointer to a const value - Finally, it is possible to declare a "const pointer to a const value" by using the const keyword both before the type and after the asterisk:

        int value { 5 };
        const int* const ptr { &value }; // a const pointer to a const value

        A const pointer to a const value can not have its address changed, nor can the value it is pointing to be changed through the pointer. It can only be dereferenced to get the value it is pointing at.

    6. Summary : 

        int v{ 5 };

        int* ptr0 { &v };             // points to an "int" but is not const itself, so this is a normal pointer.
        const int* ptr1 { &v };       // points to a "const int" but is not const itself, so this is a pointer to a const value.
        int* const ptr2 { &v };       // points to an "int" and is const itself, so this is a const pointer (to a non-const value).
        const int* const ptr3 { &v }; // points to a "const int" and is const itself, so this is a const pointer to a const value.

        // if the const is on the left side of the *, the const belongs to the value
        // if the const is on the right side of the *, the const belongs to the pointer

 */

int main()
{
    
    {
        int x{ 5 }; // non-const
        const int* ptr { &x }; // ptr points to a "const int"

        // *ptr = 6;  // not allowed: ptr points to a "const int" so we can't change the value through ptr
        x = 6; // allowed: the value is still non-const when accessed through non-const identifier x
    }

    {
        int x{ 5 };
        int* const ptr { &x }; // const after the asterisk means this is a const pointer
    }

    {
        int value { 5 };
        const int* const ptr { &value }; // a const pointer to a const value

        std::cout<<*ptr<<std::endl;

        value = 9;

        std::cout<<*ptr<<std::endl;

        // *ptr = 100;
    }

    return 0;
}