#include <iostream>

/*
    Notes : 

    1. Each block defines its own scope region. So what happens when we have a variable inside a nested block that has the same name as a variable in an outer block?

        => When this happens, the nested variable “hides” the outer variable in areas where they are both in scope. This is called name hiding or shadowing.
    
    2. Shadowing of global variables : Similar to how variables in a nested block can shadow variables in an outer block, local variables with the same name as a global variable will shadow the global variable wherever the local variable is in scope.

    3. Avoid variable shadowing = 

    Shadowing of local variables should generally be avoided, as it can lead to inadvertent errors where the wrong variable is used or modified. Some compilers will issue a warning when a variable is shadowed.

    // add -Wshadow if you want to generate warning of shadow variables.

*/

int value { 5 }; // global variable

void foo()
{
    std::cout << "global variable value: " << value << '\n'; // value is not shadowed here, so this refers to the global value
}


int main()
{ // outer block
    int apples { 5 }; // here's the outer block apples

    { // nested block
        // apples refers to outer block apples here
        std::cout << apples << '\n'; // print value of outer block apples

        int apples{ 0 }; // define apples in the scope of the nested block

        // apples now refers to the nested block apples
        // the outer block apples is temporarily hidden

        apples = 10; // this assigns value 10 to nested block apples, not outer block apples

        std::cout << apples << '\n'; // print value of nested block apples
    } // nested block apples destroyed


    std::cout << apples << '\n'; // prints value of outer block apples


    // ------------------------------------------------------------

    int value { 7 }; // hides the global variable value (wherever local variable value is in scope)

    ++value; // increments local value, not global value

    std::cout << "local variable value: " << value << '\n';

    foo();

    // access the global values

    std::cout<<"Value :: = "<<::value<<std::endl;

    return 0;
} // outer block apples destroyed