#include <iostream>
/* 
    Notes :  
    
    1. A struct (short for structure) is a program-defined data type (13.1 -- Introduction to program-defined (user-defined) types) that allows us to bundle multiple variables together into a single type.

    2. Defining structs - Because structs are a program-defined type, we first have to tell the compiler what our struct type looks like before we can begin using it. Here is an example of a struct definition for a simplified employee:

        struct Employee
        {
            int id {};
            int age {};
            double wage {};
        };

    The struct keyword is used to tell the compiler that we’re defining a struct, which we’ve named Employee (since program-defined types are typically given names starting with a capital letter). The variables that are part of the struct are called data members (or member variables). In C++, a member is a variable, function, or type that belongs to a struct (or class). All members must be declared within the struct (or class) definition.

    3. Defining struct objects - In order to use the Employee type, we simply define a variable of type Employee:

        Employee joe {}; // Employee is the type, joe is the variable name

    4. Accessing members - 

        struct Employee
        {
            int id {};
            int age {};
            double wage {};
        };

        In the above example, the name joe refers to the entire struct object (which contains the member variables). To access a specific member variable, we use the member selection operator (operator.) in between the struct variable name and the member name. For example, to access Joe’s age member, we’d use joe.age.

        joe.age = 32;  // use member selection operator (.) to select the age member of variable joe

    5. Struct aggregate initialization - 

        => Data members are not initialized by default - Much like normal variables, data members are not initialized by default.

            struct Employee
            {
                int id; // note: no initializer here
                int age;
                double wage;
            };

        => What is an aggregate? - In general programming, an aggregate data type (also called an aggregate) is any type that can contain multiple data members. Some types of aggregates allow members to have different types (e.g. structs), while others require that all members must be of a single type (e.g. arrays). In C++, the definition of an aggregate is narrower and quite a bit more complicated.

        => To simplify a bit, an aggregate in C++ is either a C-style array , or a class type (struct, class, or union) that has:

            - No user-declared constructors (14.9 -- Introduction to constructors)
            - No private or protected non-static data members (14.5 -- Public and private members and access specifiers)
            - No virtual functions (25.2 -- Virtual functions and polymorphism)

        => The intialization - 

            struct Employee
            {
                int id {};
                int age {};
                double wage {};
            };

        => Aggregates use a form of initialization called aggregate initialization, which allows us to directly initialize the members of aggregates. To do this, we provide an initializer list as an initializer, which is just a braced list of comma-separated values.

            There are 2 primary forms of aggregate initialization:

                Employee frank = { 1, 32, 60000.0 }; // copy-list initialization using braced list
                Employee joe { 2, 28, 45000.0 };     // list initialization using braced list (preferred)

            Each of these initialization forms does a memberwise initialization, which means each member in the struct is initialized in the order of declaration. Thus, Employee joe { 2, 28, 45000.0 }; first initializes joe.id with value 2, then joe.age with value 28, and joe.wage with value 45000.0 last.

        => Missing initializers in an initializer list - 

            If an aggregate is initialized but the number of initialization values is fewer than the number of members, then all remaining members are initialized with an empty initializer list. In most cases, this will perform value-initialization on those members.

    6. Overloading operator<< to print a struct - 

        std::ostream& operator<<(std::ostream& out, const Employee& e)
        {
            out << e.id << ' ' << e.age << ' ' << e.wage;
            return out;
        }

    7. Const structs - Variables of a struct type can be const (or constexpr), and just like all const variables, they must be initialized.

        struct Rectangle
        {
            double length {};
            double width {};
        };

        int main()
        {
            const Rectangle unit { 1.0, 1.0 };
            const Rectangle zero { }; // value-initialize all members

            return 0;
        }

    8. Designated initializers C++20 - 

        To help avoid this, C++20 adds a new way to initialize struct members called designated initializers. Designated initializers allow you to explicitly define which initialization values map to which members. The members can be initialized using list or copy initialization, and must be initialized in the same order in which they are declared in the struct, otherwise a warning or error will result. Members not designated an initializer will be value initialized.

            struct Foo
            {
                int a{ };
                int b{ };
                int c{ };
            };

            Foo f1{ .a{ 1 }, .c{ 3 } }; // ok: f1.a = 1, f1.b = 0 (value initialized), f1.c = 3
            Foo f2{ .a = 1, .c = 3 };   // ok: f2.a = 1, f2.b = 0 (value initialized), f2.c = 3
            Foo f3{ .b{ 2 }, .a{ 1 } }; // error: initialization order does not match order of declaration in struct

    9. Assignment with an initializer list - 

        struct Employee
        {
            int id {};
            int age {};
            double wage {};
        };

        Employee joe { 1, 32, 60000.0 };
        joe = { joe.id, 33, 66000.0 }; // Joe had a birthday and got a raise

    10. Assignment with designated initializers  - 

        joe = { .id = joe.id, .age = 33, .wage = 66000.0 }; // Joe had a birthday and got a raise

    11. 


*/

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

std::ostream& operator<<(std::ostream& out, const Employee& e)
{
    out << "id: " << e.id << " age: " << e.age << " wage: " << e.wage;
    return out;
}

struct Rectangle
{
    double length {};
    double width {};
};

int main()
{
    Employee joe { 2, 28 }; // joe.wage will be value-initialized to 0.0
    std::cout << joe << '\n';

    const Rectangle unit { 1.0, 1.0 };

    return 0;
}