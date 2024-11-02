#include <iostream>
/* 
    Notes :  
    
    1. Inside every (non-static) member function, the keyword this is a const pointer that holds the address of the current implicit object. We can have functions return *this by reference in order to enable method chaining, where several member functions can be called on the same object in a single expression.

    2. Prefer to put your class definitions in a header file with the same name as the class. Trivial member functions (such as access functions, constructors with empty bodies, etc…) can be defined inside the class definition.

    3. Prefer to define non-trivial member functions in a source file with the same name as the class.

    4. A type that is defined inside a class type is called a nested type (or member type). Type aliases can also be nested.

    5. Member functions defined inside a class template definition can use the template parameters of the class template itself. Member functions defined outside the class template definition must resupply a template parameter declaration, and should be defined (in the same file) just below the class template definition.

    6. Static member variables are static duration members that are shared by all objects of the class. Static members exist even if no objects of the class have been instantiated. Prefer to access them using the class name, the scope resolution operator, and the members name.

    7. Making static members inline allows them to be initialized inside the class definition.

    8. Static member functions are member functions that can be called with no object. They do not have a *this pointer, and cannot access non-static data members.

    9. Inside the body of a class, a friend declaration (using the friend keyword) can be used to tell the compiler that some other class or function is now a friend. A friend is a class or function (member or non-member) that has been granted full access to the private and protected members of another class. A friend function is a function (member or non-member) that can access the private and protected members of a class as though it were a member of that class. A friend class is a class that can access the private and protected members of another class.

*/
int main()
{
    return 0;
}