#include <iostream>
/* 
    Notes :  
    
    1. In addition to having member variables, class types (which includes structs, classes, and unions) can also have their own functions! Functions that belong to a class type are called member functions. Member functions must be declared inside the class type definition, and can be defined inside or outside of the class type definition. As a reminder, a definition is also a declaration, so if we define a member function inside the class, that counts as a declaration.

    Example : 

        struct Date
        {
            int year {};
            int month {};
            int day {};

            void print() // defines a member function named print
            {
                std::cout << year << '/' << month << '/' << day;
            }
        };

    2. Member functions are declared inside the class type definition - 

        - In the non-member example, the print() non-member function is defined outside of the Date struct, in the global namespace. By default, it has external linkage, so it could be called from other source files (with the appropriate forward declaration).

        - Member functions defined inside the class type definition are implicitly inline, so they will not cause violations of the one-definition rule if the class type definition is included into multiple code files.

        

    3. Calling member functions (and the implicit object) - 

            Date today { 2020, 10, 14 }; // aggregate initialize our struct

            today.day = 16; // member variables accessed using member selection operator (.)
            today.print();  // member functions also accessed using member selection operator (.)

        - The object that a member function is called on is implicitly passed to the member function. For this reason, the object that a member function is called on is often called the implicit object.

        - In other words, when we call today.print(), today is the implicit object, and it is implicitly passed to the print() member function.

    4. Accessing members inside a member function uses the implicit object : 

        - With non-member functions, we have to explicitly pass an object to the function to work with, and members are explicitly accessed through that object.

        - With member functions, we implicitly pass an object to the function to work with, and members are implicitly accessed through that object.

    5. Member variables and functions can be defined in any order -  inside a class definition, this restriction doesn’t apply: you can access member variables and member functions before they are declared. This means you can define member variables and member functions in any order you like!

        - Data members are initialized in order of declaration. If the initialization of a data member accesses another data member that isn’t declared until later (and thus hasn’t been initialized yet), the initialization will result in undefined behavior.

        Example : 

            struct Bad
            {
                int m_bad1 { m_data }; // undefined behavior: m_bad1 initialized before m_data
                int m_bad2 { fcn() };  // undefined behavior: m_bad2 initialized before m_data (accessed through fcn())

                int m_data { 5 };
                int fcn() { return m_data; }
            };

    6. Member functions can be overloaded : 

        struct Date
        {
            int year {};
            int month {};
            int day {};

            void print()
            {
                std::cout << year << '/' << month << '/' << day;
            }

            void print(std::string_view prefix)
            {
                std::cout << prefix << year << '/' << month << '/' << day;
            }
        };

    7. Structs and member functions :  Member functions can be used with both structs and classes. However, structs should avoid defining constructor member functions, as doing so makes them a non-aggregate.

    8. Class types with no data members : It is possible to create class types with no data members (e.g. class types that only have member functions). It is also possible to instantiate objects of such a class type:

        struct Foo
        {
            void printHi() { std::cout << "Hi!\n"; }
        };

        int main()
        {
            Foo f{};
            f.printHi(); // requires object to call

            return 0;
        }

        However, if a class type does not have any data members, then using a class type is probably overkill. In such cases, consider using a namespace (containing non-member functions) instead. This makes it clearer to the reader that no data is being managed (and does not require an object to be instantiated to call the functions).

        



*/
int main()
{
    return 0;
}