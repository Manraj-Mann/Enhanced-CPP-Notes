#include <iostream>
#include <string>
#include <string_view>

/*
    Notes : 

    1. Some objects are expensive to copy -  Class types are usually expensive to copy. Whenever possible, we want to avoid making unnecessary copies of objects that are expensive to copy, especially when we will destroy those copies almost immediately.

    2. Pass by reference - Pass by reference allows us to pass arguments to a function without making copies of those arguments each time the function is called.

        void printValue(std::string& y) // type changed to std::string&
        {
            std::cout << y << '\n';
        } // y is destroyed here

    3. Pass by reference allows us to change the value of an argument - since a reference acts identically to the object being referenced, when using pass by reference, any changes made to the reference parameter will affect the argument:

        void addOne(int& y) // y is bound to the actual object x
        {
            ++y; // this modifies the actual object x
        }

    Passing values by reference to non-const allows us to write functions that modify the value of arguments passed in.

    4. Pass by reference can only accept modifiable lvalue arguments - Because a reference to a non-const value can only bind to a modifiable lvalue (essentially a non-const variable), this means that pass by reference only works with arguments that are modifiable lvalues. In practical terms, this significantly limits the usefulness of pass by reference to non-const, as it means we can not pass const variables or literals.

    Example : 

        const int z { 5 };
        printValue(z); // error: z is a non-modifiable lvalue

        printValue(5); // error: 5 is an rvalue

    5. Passing by const reference offers the same primary benefit as pass by reference (avoiding making a copy of the argument), while also guaranteeing that the function can not change the value being referenced.

        - Favor passing by const reference over passing by non-const reference unless you have a specific reason to do otherwise (e.g. the function needs to change the value of an argument).

        - Now we can understand the motivation for allowing const lvalue references to bind to rvalues: without that capability, there would be no way to pass literals (or other rvalues) to functions that used pass by reference!

    6. Passing values of a different type to a const lvalue reference parameter - A const lvalue reference can bind to a value of a different type, as long as that value is convertible to the type of the reference. The primary motivation for allowing this is so that we can pass a value as an argument to either a value parameter or a const reference parameter in exactly the same way:

        void printVal(double d)
        {
            std::cout << d << '\n';
        }

        void printRef(const double& d)
        {
            std::cout << d << '\n';
        }

        int main()
        {
            printVal(5); // 5 converted to temporary double, copied to parameter d
            printRef(5); // 5 converted to temporary double, bound to parameter d

            return 0;
        }

    7. Mixing pass by value and pass by reference - A function with multiple parameters can determine whether each parameter is passed by value or passed by reference individually.

        void foo(int a, int& b, const std::string& c)
        {
        }

    8. When to pass by (const) reference - Because class types can be expensive to copy (sometimes significantly so), class types are usually passed by const reference instead of by value to avoid making an expensive copy of the argument. Fundamental types are cheap to copy, so they are typically passed by value.

        - As a rule of thumb, pass fundamental types by value, and class (or struct) types by const reference.
        - Other common types to pass by value: enumerated types and std::string_view.
        - Other common types to pass by (const) reference: std::string, std::array, and std::vector.

    9. The cost of pass by value vs pass by reference - 

        - There are two key points that will help us understand when we should pass by value vs pass by reference: 

            1. First, the cost of copying an object is generally proportional to two things:

                -> The size of the object. Objects that use more memory take more time to copy.
                
                -> Any additional setup costs. Some class types do additional setup when they are instantiated (e.g. such as opening a file or database, or allocating a certain amount of dynamic memory to hold an object of a variable size). These setup costs must be paid each time an object is copied.

            2. On the other hand, binding a reference to an object is always fast (about the same speed as copying a fundamental type).

            3. Second, accessing an object through a reference is slightly more expensive than accessing an object through a normal variable identifier. With a variable identifier, the running program can just go to the memory address assigned to that variable and access the value directly. With a reference, there usually is an extra step: the program must first access the reference to determine which object is being referenced, and only then can it go to that memory address for that object and access the value. The compiler can also sometimes optimize code using objects passed by value more highly than code using objects passed by reference. This means code generated to access objects passed by reference is typically slower than the code generated for objects passed by value.

        - We can now answer the question of why we don’t pass everything by reference:

            1. For objects that are cheap to copy, the cost of copying is similar to the cost of binding, so we favor pass by value so the code generated will be faster.
            2. For objects that are expensive to copy, the cost of the copy dominates, so we favor pass by (const) reference to avoid making a copy.

        - Prefer pass by value for objects that are cheap to copy, and pass by const reference for objects that are expensive to copy. If you’re not sure whether an object is cheap or expensive to copy, favor pass by const reference.

    10. For function parameters, prefer std::string_view over const std::string& in most cases  - 

        - In C++, a string argument will typically be a std::string, a std::string_view, or a C-style string/string literal.

        void printSV(std::string_view sv)
        {
            std::cout << sv << '\n';
        }

        void printS(const std::string& s)
        {
            std::cout << s << '\n';
        }

        - std::string s{ "Hello, world" };
        - std::string_view sv { s };

        // Pass to `std::string_view` parameter

        - printSV(s);              // ok: inexpensive conversion from std::string to std::string_view
        - printSV(sv);             // ok: inexpensive copy of std::string_view
        - printSV("Hello, world"); // ok: inexpensive conversion of C-style string literal to std::string_view

        // pass to `const std::string&` parameter

        - printS(s);              // ok: inexpensive bind to std::string argument
        - printS(sv);             // compile error: cannot implicit convert std::string_view to std::string
        - printS(static_cast<std::string>(sv)); // bad: expensive creation of std::string temporary
        - printS("Hello, world"); // bad: expensive creation of std::string temporary

    => Additionally, we need to consider the cost of accessing the parameter inside the function. Because a std::string_view parameter is a normal object, the string being viewed can be accessed directly. Accessing a std::string& parameter requires an additional step to get to the referenced object before the string can be accessed.

*/

void printValue(int& y) // y only accepts modifiable lvalues
{
    std::cout << y << '\n';
}


void printVal(double d)
{
    std::cout << d << '\n';
}

void printRef(const double& d)
{
    std::cout << d << '\n';
}

void printSV(std::string_view sv)
{
    std::cout << sv << '\n';
}

void printS(const std::string& s)
{
    std::cout << s << '\n';
}


int main()
{
    int x { 5 };
    printValue(x); // ok: x is a modifiable lvalue

    // const int z { 5 };
    // printValue(z); // error: z is a non-modifiable lvalue

    // printValue(5); // error: 5 is an rvalue

    printVal(10); // 10 converted to temporary double, copied to parameter d
    printRef(10); // 10 converted to temporary double, bound to parameter d

    std::string s{ "Hello, world" };
    std::string_view sv { s };

    // Pass to `std::string_view` parameter
    printSV(s);              // ok: inexpensive conversion from std::string to std::string_view
    printSV(sv);             // ok: inexpensive copy of std::string_view
    printSV("Hello, world"); // ok: inexpensive conversion of C-style string literal to std::string_view

    // pass to `const std::string&` parameter
    printS(s);              // ok: inexpensive bind to std::string argument
    printS(sv);             // compile error: cannot implicit convert std::string_view to std::string
    printS(static_cast<std::string>(sv)); // bad: expensive creation of std::string temporary
    printS("Hello, world"); // bad: expensive creation of std::string temporary

    return 0;
}