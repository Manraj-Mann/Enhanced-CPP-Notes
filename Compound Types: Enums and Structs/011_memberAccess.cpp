#include <iostream>
/* 
    Notes :  
    
    1. Member selection for structs and references to structs - we showed that you can use the member selection operator (.) to select a member from a struct object:

        struct Employee
        {
            int id {};
            int age {};
            double wage {};
        };

        int main()
        {
            Employee joe { 1, 34, 65000.0 };

            // Use member selection operator (.) to select a member from struct object
            ++joe.age; // Joe had a birthday
            joe.wage = 68000.0; // Joe got a promotion

            return 0;
        }

    2. Member selection for pointers to structs - However, the member selection operator (.) can’t be used directly on a pointer to a struct:

        struct Employee
        {
            int id{};
            int age{};
            double wage{};
        };

        int main()
        {
            Employee joe{ 1, 34, 65000.0 };

            ++joe.age;
            joe.wage = 68000.0;

            Employee* ptr{ &joe };
            std::cout << ptr.id << '\n'; // Compile error: can't use operator. with pointers

            return 0;
        }

    3. With normal variables or references, we can access objects directly. However, because pointers hold addresses, we first need to dereference the pointer to get the object before we can do anything with it. So one way to access a member from a pointer to a struct is as follows:

        std::cout << (*ptr).id << '\n'; // Not great but works: First dereference ptr, then use member selection

    4. To make for a cleaner syntax, C++ offers a member selection from pointer operator (->) (also sometimes called the arrow operator) that can be used to select members from a pointer to an object:

        std::cout << ptr->id << '\n'; // Better: use -> to select member from pointer to object

    5. Chaining operator-> If the member accessed via operator-> is a pointer to a class type, operator-> can be applied again in the same expression to access the member of that class type.

        std::cout << ptr2->c->y << '\n'; // much nicer

    6. Mixing pointers and non-pointers to members - 

        The member selection operator is always applied to the currently selected variable. If you have a mix of pointers and normal member variables, you can see member selections where . and -> are both used in sequence:

*/

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

struct Point
{
    double x {};
    double y {};
};

struct Triangle
{
    Point* a {};
    Point* b {};
    Point* c {};
};

struct Paw
{
    int claws{};
};

struct Animal
{
    std::string name{};
    Paw paw{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    // std::cout << ptr.id << '\n'; // Compile error: can't use operator. with pointers

    std::cout << "Value : "<<(*ptr).id << '\n'; // Not great but works: First dereference ptr, then use member selection

    std::cout << "Value : "<<ptr->id << '\n'; // Better: use -> to select member from pointer to object


    Point a {1,2};
    Point b {3,7};
    Point c {10,2};

    Triangle tr { &a, &b, &c };
    Triangle* ptr2 {&tr};

    // ptr is a pointer to a Triangle, which contains members that are pointers to a Point
    // To access member y of Point c of the Triangle pointed to by ptr, the following are equivalent:

    // access via operator.
    std::cout << (*(*ptr2).c).y << '\n'; // ugly!

    // access via operator->
    std::cout << ptr2->c->y << '\n'; // much nicer


    Animal puma{ "Puma", { 5 } };

    Animal* ptr3{ &puma };

    // ptr is a pointer, use ->
    // paw is not a pointer, use .

    std::cout << (ptr3->paw).claws << '\n';

    return 0;
}