#include <iostream>

/*
    Notes : 

    1. In C++, a reference is an alias for an existing object. Once a reference has been defined, any operation on the reference is applied to the object being referenced. Modern C++ contains two types of references: lvalue references, and rvalue references.

    2. Rvalue references are covered in the chapter on move semantics

    3. Lvalue reference types - An lvalue reference (commonly just called a reference since prior to C++11 there was only one type of reference) acts as an alias for an existing lvalue (such as a variable).To declare an lvalue reference type, we use an ampersand (&) in the type declaration:

        - int      // a normal int type
        - int&     // an lvalue reference to an int object
        - double&  // an lvalue reference to a double object

    4. Lvalue reference variables - One of the things we can do with an lvalue reference type is create an lvalue reference variable. An lvalue reference variable is a variable that acts as a reference to an lvalue (usually another variable). To create an lvalue reference variable, we simply define a variable with an lvalue reference type:

        - int x { 5 };    // x is a normal integer variable
        - int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

        - std::cout << x << '\n';  // print the value of x (5)
        - std::cout << ref << '\n'; // print the value of x via ref (5)

    5. Modifying values through an lvalue reference - We can use a reference to read the value of the object being referenced. We can also use a reference to modify the value of the object being referenced:

        int x { 5 }; // normal integer variable
        int& ref { x }; // ref is now an alias for variable x

        std::cout << x << ref << '\n'; // print 55

        x = 6; // x now has value 6

        std::cout << x << ref << '\n'; // prints 66

    6. Initialization of lvalue references - Much like constants, all references must be initialized.

        - int& invalidRef;   // error: references must be initialized

        - int& ref { x }; // okay: reference to int is bound to int variable

        => When a reference is initialized with an object (or function), we say it is bound to that object (or function). The process by which such a reference is bound is called reference binding. The object (or function) being referenced is sometimes called the referent.
        

    7. Lvalue references must be bound to a modifiable lvalue - 

            int x { 5 };
            int& ref { x }; // valid: lvalue reference bound to a modifiable lvalue

            const int y { 5 };
            int& invalidRef { y };  // invalid: can't bind to a non-modifiable lvalue
            int& invalidRef2 { 0 }; // invalid: can't bind to an rvalue

        => Lvalue references can’t be bound to non-modifiable lvalues or rvalues (otherwise you’d be able to change those values through the reference, which would be a violation of their const-ness). For this reason, lvalue references are occasionally called lvalue references to non-const (sometimes shortened to non-const reference).

    8. References can’t be reseated (changed to refer to another object) - 

       -  Once initialized, a reference in C++ cannot be reseated, meaning it cannot be changed to reference another object.

        Example : 

            int x { 5 };
            int y { 6 };

            int& ref { x }; // ref is now an alias for x

            ref = y; // assigns 6 (the value of y) to x (the object being referenced by ref)
            // The above line does NOT change ref into a reference to variable y!

    9. Lvalue reference scope and duration : Reference variables follow the same scoping and duration rules that normal variables do.

    10. References and referents have independent lifetimes - 

        With one exception (that we’ll cover next lesson), the lifetime of a reference and the lifetime of its referent are independent. In other words, both of the following are true:

        - A reference can be destroyed before the object it is referencing.
        - The object being referenced can be destroyed before the reference.

        When a reference is destroyed before the referent, the referent is not impacted. 

        int x { 5 };

        {
            int& ref { x };   // ref is a reference to x
            std::cout << ref << '\n'; // prints value of ref (5)
        } // ref is destroyed here -- x is unaware of this

        std::cout << x << '\n'; // prints value of x (5)

    11. Dangling references - When an object being referenced is destroyed before a reference to it, the reference is left referencing an object that no longer exists. Such a reference is called a dangling reference. Accessing a dangling reference leads to undefined behavior.

    12. References aren’t objects - References are not objects in C++. A reference is not required to exist or occupy storage. If possible, the compiler will optimize references away by replacing all occurrences of a reference with the referent. However, this isn’t always possible, and in such cases, references may require storage.

    Because references aren’t objects, they can’t be used anywhere an object is required (e.g. you can’t have a reference to a reference, since an lvalue reference must reference an identifiable object). In cases where you need a reference that is an object or a reference that can be reseated, std::reference_wrapper provides a solution.

    Consider the following variables:

        int var{};
        int& ref1{ var };  // an lvalue reference bound to var
        int& ref2{ ref1 }; // an lvalue reference bound to var
    
    Because ref2 (a reference) is initialized with ref1 (a reference), you might be tempted to conclude that ref2 is a reference to a reference. It is not. Because ref1 is a reference to var, when used in an expression (such as an initializer), ref1 evaluates to var. So ref2 is just a normal lvalue reference (as indicated by its type int&), bound to var.

    A reference to a reference (to an int) would have syntax int&& -- but since C++ doesn’t support references to references, this syntax was repurposed in C++11 to indicate an rvalue reference

*/

int main()
{
    int x { 5 };    // x is a normal integer variable
    int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

    std::cout << x << '\n';  // print the value of x (5)
    std::cout << ref << '\n'; // print the value of x via ref (5)

    const int y { 5 };
    // int& invalidRef { y };  // invalid: can't bind to a non-modifiable lvalue
    // int& invalidRef2 { 0 }; // invalid: can't bind to an rvalue

    int z{6};

    std::cout<<"x = "<<x<<std::endl;
    std::cout<<"ref = "<<ref<<std::endl;
    std::cout<<"z = "<<z<<std::endl;

    std::cout<<"------------------------------------"<<std::endl;

    // change the value of x to z
    ref = z;

    std::cout<<"x = "<<x<<std::endl;
    std::cout<<"ref = "<<ref<<std::endl;
    std::cout<<"z = "<<z<<std::endl;

    std::cout<<"------------------------------------"<<std::endl;

    // change value of x , ref is still referring to x
    x = 100;

    std::cout<<"x = "<<x<<std::endl;
    std::cout<<"ref = "<<ref<<std::endl;
    std::cout<<"z = "<<z<<std::endl;

    // int &&refToRef = x; // error: cannot bind 'int' lvalue to 'int&&'



    std::cout<<"Ended"<<std::endl;
    return 0;
}