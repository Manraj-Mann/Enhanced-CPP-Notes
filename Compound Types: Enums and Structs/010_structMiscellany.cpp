#include <iostream>
/* 
    Notes :  
    
    1. Structs with program-defined members - 

        In C++, structs (and classes) can have members that are other program-defined types. There are two ways to do this.

        1. We can define one program-defined type (in the global scope) and then use it as a member of another program-defined type:

            struct Employee
            {
                int id {};
                int age {};
                double wage {};
            };

            struct Company
            {
                int numberOfEmployees {};
                Employee CEO {}; // Employee is a struct within the Company struct
            };

            Company myCompany{ 7, { 1, 32, 55000.0 } }; // Nested initialization list to initialize Employee
            std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage

        2. Second, types can also be nested inside other types, so if an Employee only existed as part of a Company, the Employee type could be nested inside the Company struct:

            struct Company
            {
                struct Employee // accessed via Company::Employee
                {
                    int id{};
                    int age{};
                    double wage{};
                };

                int numberOfEmployees{};
                Employee CEO{}; // Employee is a struct within the Company struct
            };

    2. Structs that are owners should have data members that are owners - 

        - Owners manage their own data, and control when it is destroyed. Viewers view someone else’s data, and do not control when it is altered or destroyed.

        - In most cases, we want our structs (and classes) to be owners of the data they contain. This provides a few useful benefits:

            - The data members will be valid for as long as the struct (or class) is.
            - The value of those data members won’t change unexpectedly.
        
        - The easiest way to make a struct (or class) an owner is to give each data member a type that is an owner (e.g. not a viewer, pointer, or reference). If a struct or class has data members that are all owners, then the struct or class itself is automatically an owner.

        - If a struct (or class) has a data member that is a viewer, it is possible that the object being viewed by that member will be destroyed before the data member that is viewing it. If this happens, the struct will be left with a dangling member, and accessing that member will lead to undefined behavior.

        - In most cases, we want our structs (and classes) to be owners. The easiest way to enable this is to ensure each data member has an owning type (e.g. not a viewer, pointer, or reference).

    3. Struct size and data structure alignment - 

        - Typically, the size of a struct is the sum of the size of all its members, but not always!

            struct Foo
            {
                short a {};
                int b {};
                double c {};
            };

            Note that the size of short + int + double is 14 bytes, but the size of Foo is 16 bytes!

        - It turns out, we can only say that the size of a struct will be at least as large as the size of all the variables it contains. But it could be larger! For performance reasons, the compiler will sometimes add gaps into structures (this is called padding).

        - You can minimize padding by defining your members in decreasing order of size. The C++ compiler is not allowed to reorder members, so this has to be done manually.

    4. Details : 

        - Data structure alignment - Data structure alignment is the way data is arranged and accessed in computer memory. It consists of three separate but related issues: data alignment, data structure padding, and packing.

        - The CPU in modern computer hardware performs reads and writes to memory most efficiently when the data is naturally aligned, which generally means that the data's memory address is a multiple of the data size. For instance, in a 32-bit architecture, the data may be aligned if the data is stored in four consecutive bytes and the first byte lies on a 4-byte boundary.

    

*/

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

struct Company
{
    int numberOfEmployees {};
    Employee CEO {}; // Employee is a struct within the Company struct
};

struct Foo
{
    short a {};
    int b {};
    double c {};
};


int main()
{
    Company myCompany{ 7, { 1, 32, 55000.0 } }; // Nested initialization list to initialize Employee
    std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage

    std::cout << "The size of short is " << sizeof(short) << " bytes\n";
    std::cout << "The size of int is " << sizeof(int) << " bytes\n";
    std::cout << "The size of double is " << sizeof(double) << " bytes\n";

    std::cout << "The size of Foo is " << sizeof(Foo) << " bytes\n";

    return 0;
}