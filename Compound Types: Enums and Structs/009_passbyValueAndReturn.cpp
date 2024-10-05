#include <iostream>
/* 
    Notes :  
    
    1. Passing structs (by reference) - 

        A big advantage of using structs over individual variables is that we can pass the entire struct to a function that needs to work with the members. Structs are generally passed by reference (typically by const reference) to avoid making copies.

        struct Employee
        {
            int id {};
            int age {};
            double wage {};
        };

        void printEmployee(const Employee& employee) // note pass by reference here
        {
            std::cout << "ID:   " << employee.id << '\n';
            std::cout << "Age:  " << employee.age << '\n';
            std::cout << "Wage: " << employee.wage << '\n';
        }

    2. Passing temporary structs - Temporary objects: they are created and initialized at the point of definition, and are destroyed at the end of the full expression in which they are created. And evaluation of a temporary object is an rvalue expression, it can only be used in places where rvalues are accepted. When a temporary object is used as a function argument, it will only bind to parameters that accept rvalues. This includes pass by value and pass by const reference, and excludes pass by non-const reference and pass by address.

    3. Returning structs - One common way is to return a struct:

            Point3d getZeroPoint()
            {
                // We can create a variable and return the variable (we'll improve this below)
                Point3d temp { 0.0, 0.0, 0.0 };
                return temp;
            }

        - Structs are usually returned by value, so as not to return a dangling reference.

            Point3d getZeroPoint()
            {
                // We can create a variable and return the variable (we'll improve this below)
                Point3d temp { 0.0, 0.0, 0.0 };
                return temp;
            }

        - We can make our function slightly better by returning a temporary (unnamed/anonymous) object instead:

            Point3d getZeroPoint()
            {
                return Point3d { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
            }
    
    4. Deducing the return type - 

        In the case where the function has an explicit return type (e.g. Point3d), we can even omit the type in the return statement:

        Point3d getZeroPoint()
        {
            // We already specified the type at the function declaration
            // so we don't need to do so here again
            return { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
        }

        Point3d getZeroPoint()
        {
            // We can use empty curly braces to value-initialize all members
            return {};
        }

*/

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

void printEmployee(const Employee& employee) // note pass by reference here
{
    std::cout << "ID:   " << employee.id << '\n';
    std::cout << "Age:  " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}


int main()
{
    Employee joe { 14, 32, 24.15 };
    
    // Print Joe's information
    printEmployee(joe);

    // Print Joe's information
    printEmployee(Employee { 14, 32, 24.15 }); // construct a temporary Employee to pass to function (type explicitly specified) (preferred)

    std::cout << '\n';

    // Print Frank's information
    printEmployee({ 15, 28, 18.27 }); // construct a temporary Employee to pass to function (type deduced from parameter)


    return 0;
}