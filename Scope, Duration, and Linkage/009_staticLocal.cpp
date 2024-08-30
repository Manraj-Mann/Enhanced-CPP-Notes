#include <iostream>

/*

    Notes : 

    Remember : Global variables have static duration, which means they are created when the program starts and destroyed when the program ends.
    
    We also discussed how the static keyword gives a global identifier internal linkage, which means the identifier can only be used in the file in which it is defined.

    1. Local variables have automatic duration by default, which means they are created at the point of definition, and destroyed when the block is exited.

    2. Using the static keyword on a local variable changes its duration from automatic duration to static duration. This means the variable is now created at the start of the program, and destroyed at the end of the program (just like a global variable). As a result, the static variable will retain its value even after it goes out of scope!

    3. Static local variables that are zero initialized or have a constexpr initializer can be initialized at program start.

    4. Static local variables that have no initializer or a non-constexpr initializer are zero-initialized at program start.

    5. ID generation - One of the most common uses for static duration local variables is for unique ID generators.

    6. Static variables offer some of the benefit of global variables (they don’t get destroyed until the end of the program) while limiting their visibility to block scope. This makes them easier to understand and safer to use.

    7. Static local constants - With a const/constexpr static local variable, you can create and initialize the expensive object once, and then reuse it whenever the function is called.

    8. Const static local variables are generally okay to use. Non-const static local variables should generally be avoided. If you do use them, ensure the variable never needs to be reset, and isn’t used to alter program flow.
    
*/


int generateID()
{

    static int id{10};

    return id++;
}

// id++; out of scope : A static local variable has block scope like a local variable, but its lifetime is until the end of the program like a global variable.

int main()
{
    // id++;
    std::cout<<generateID()<<std::endl;
    std::cout<<generateID()<<std::endl;
    std::cout<<generateID()<<std::endl;
    return 0;
}