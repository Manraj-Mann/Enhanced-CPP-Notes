#include <iostream>

/*
    Notes : 

    1. Null pointers - Besides a memory address, there is one additional value that a pointer can hold: a null value. A null value (often shortened to null) is a special value that means something has no value. When a pointer is holding a null value, it means the pointer is not pointing at anything. Such a pointer is called a null pointer.

    2. The easiest way to create a null pointer is to use value initialization:s

        - int* ptr {}; // ptr is now a null pointer, and is not holding an address

    3. Because we can use assignment to change what a pointer is pointing at, a pointer that is initially set to null can later be changed to point at a valid object:

        int* ptr {}; // ptr is a null pointer, and is not holding an address
        int x { 5 };
        ptr = &x; // ptr now pointing at object x (no longer a null pointer)
        std::cout << *ptr << '\n'; // print value of x through dereferenced ptr

    4. The nullptr keyword - Much like the keywords true and false represent Boolean literal values, the nullptr keyword represents a null pointer literal. We can use nullptr to explicitly initialize or assign a pointer a null value. Use nullptr when you need a null pointer literal for initialization, assignment, or passing a null pointer to a function.

    5. Dereferencing a null pointer results in undefined behavior - Much like dereferencing a dangling (or wild) pointer leads to undefined behavior, dereferencing a null pointer also leads to undefined behavior. In most cases, it will crash your application. Conceptually, this makes sense. Dereferencing a pointer means “go to the address the pointer is pointing at and access the value there”. A null pointer holds a null value, which semantically means the pointer is not pointing at anything. So what value would it access?

    => Whenever you are using pointers, you’ll need to be extra careful that your code isn’t dereferencing null or dangling pointers, as this will cause undefined behavior (probably an application crash).

    6. Checking for null pointers - Much like we can use a conditional to test Boolean values for true or false, we can use a conditional to test whether a pointer has value nullptr or not:

    Example : 

        int x { 5 };
        int* ptr { &x };

        if (ptr == nullptr) // explicit test for equivalence
            std::cout << "ptr is null\n";
        else
            std::cout << "ptr is non-null\n";

        int* nullPtr {};
        std::cout << "nullPtr is " << (nullPtr==nullptr ? "null\n" : "non-null\n"); // explicit test for equivalence

    => Similarly, pointers will also implicitly convert to Boolean values: a null pointer converts to Boolean value false, and a non-null pointer converts to Boolean value true. This allows us to skip explicitly testing for nullptr and just use the implicit conversion to Boolean to test whether a pointer is a null pointer. 

    => Conditionals can only be used to differentiate null pointers from non-null pointers. There is no convenient way to determine whether a non-null pointer is pointing to a valid object or dangling (pointing to an invalid object).

    7. Use nullptr to avoid dangling pointers : 

        // Assume ptr is some pointer that may or may not be a null pointer
        if (ptr) // if ptr is not a null pointer
            std::cout << *ptr << '\n'; // okay to dereference
        else
            // do something else that doesn't involve dereferencing ptr (print an error message, do nothing at all, etc...)

        - Because there is no way to detect whether a pointer is dangling, we need to avoid having any dangling pointers in our program in the first place. We do that by ensuring that any pointer that is not pointing at a valid object is set to nullptr.

        - A pointer should either hold the address of a valid object, or be set to nullptr. That way we only need to test pointers for null, and can assume any non-null pointer is valid.

    8. Legacy null pointer literals: 0 and NULL - In older code, you may see two other literal values used instead of nullptr.

        The first is the literal 0. In the context of a pointer, the literal 0 is specially defined to mean a null value, and is the only time you can assign an integral literal to a pointer.

        Example : 

            float* ptr { 0 };  // ptr is now a null pointer (for example only, don't do this)

            float* ptr2; // ptr2 is uninitialized
            ptr2 = 0; // ptr2 is now a null pointer (for example only, don't do this)

        On modern architectures, the address 0 is typically used to represent a null pointer. However, this value is not guaranteed by the C++ standard, and some architectures use other values. The literal 0, when used in the context of a null pointer, will be translated into whatever address the architecture uses to represent a null pointer.

        Additionally, there is a preprocessor macro named NULL (defined in the <cstddef> header). This macro is inherited from C, where it is commonly used to indicate a null pointer.

    9. Favor references over pointers whenever possible - 

        - Pointers and references both give us the ability to access some other object indirectly.

        - Pointers have the additional abilities of being able to change what they are pointing at, and to be pointed at null. However, these pointer abilities are also inherently dangerous: A null pointer runs the risk of being dereferenced, and the ability to change what a pointer is pointing at can make creating dangling pointers easier:

        - Since references can’t be bound to null, we don’t have to worry about null references. And because references must be bound to a valid object upon creation and then can not be reseated, dangling references are harder to create.

        - Because they are safer, references should be favored over pointers, unless the additional capabilities provided by pointers are required.


*/

int main()
{
    {
        int* ptr {}; // ptr is a null pointer, and is not holding an address

        int x { 5 };
        ptr = &x; // ptr now pointing at object x (no longer a null pointer)

        std::cout << *ptr << '\n'; // print value of x through dereferenced ptr
    }

    {
        int x { 5 };
        int* ptr { &x };

        if (ptr == nullptr) // explicit test for equivalence
            std::cout << "ptr is null\n";
        else
            std::cout << "ptr is non-null\n";

        int* nullPtr {};
        std::cout << "nullPtr is " << (nullPtr==nullptr ? "null\n" : "non-null\n"); // explicit test for equivalence

    }

    {
        float* ptr { 0 };  // ptr is now a null pointer (for example only, don't do this)

        float* ptr2; // ptr2 is uninitialized
        ptr2 = 0; // ptr2 is now a null pointer (for example only, don't do this)
    }


    return 0;
}