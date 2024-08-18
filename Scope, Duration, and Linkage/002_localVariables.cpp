#include <iostream>

/*
    Note : Local Variables

    1. When an identifier can not be accessed, we say it is out of scope. Scope is a compile-time property, and trying to use an identifier when it is out of scope will result in a compile error.

    2. Local variables have block scope:

        int main()
        {
            int i { 5 }; // i enters scope here
            double d { 4.0 }; // d enters scope here

            return 0;
        } // d and i go out of scope here

        int max(int x, int y) // x and y enter scope here
        {
            // assign the greater of x or y to max
            int max{ (x > y) ? x : y }; // max enters scope here

            return max;
        } // max, y, and x leave scope here

    3. All variable names within a scope must be unique

    4. Local variables have automatic storage duration : 

        A variable’s storage duration (usually just called duration) determines what rules govern when and how a variable will be created (instantiated) and destroyed. In most cases, a variable’s storage duration directly determines its lifetime.

        For example, local variables have automatic storage duration, which means they are created at the point of definition and destroyed at the end of the block they are defined in. For example:

        int main()
        {
            int i { 5 }; // i created and initialized here
            double d { 4.0 }; // d created and initialized here

            return 0;
        } // d and i are destroyed here

        For this reason, local variables are sometimes called automatic variables.

    5. Local variables in nested blocks : 

        int x { 5 }; // x enters scope and is created here

        { // nested block
            int y { 7 }; // y enters scope and is created here

            // x and y are both in scope here
            std::cout << x << " + " << y << " = " << x + y << '\n';
        } // y goes out of scope and is destroyed here

        // y can not be used here because it is out of scope in this block

    6. Local variables have no linkage

        Identifiers have another property named linkage. An identifier’s linkage determines whether a declaration of that same identifier in a different scope refers to the same object (or function).

        Local variables have no linkage. Each declaration of an identifier with no linkage refers to a unique object or function.

        int x { 2 }; // local variable, no linkage

        {
            int x { 3 }; // this declaration of x refers to a different object than the previous x
        }

        Scope and linkage may seem somewhat similar. However, scope determines where declaration of a single identifier can be seen and used in the code. Linkage determines whether multiple declarations of the same identifier refer to the same object or not.

    7. Variables should be defined in the most limited scope

        Define variables in the most limited existing scope. Avoid creating new blocks whose only purpose is to limit the scope of variables.

*/
int main()
{
    int x { 9 }; // x enters scope and is created here

    { // nested block
        int y { 7 }; // y enters scope and is created here

        // x and y are both in scope here
        std::cout << x << " + " << y << " = " << x + y << '\n';
    } // y goes out of scope and is destroyed here

    // y can not be used here because it is out of scope in this block

    int p {3};

    {
        int p {5};

        std::cout<<"p = "<<p<<std::endl;

        x = p;
    }
    
    std::cout<<"p = "<<p<<std::endl;

    std::cout<<"x = "<<x<<std::endl;

    return 0;
}