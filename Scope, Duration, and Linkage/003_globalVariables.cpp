#include <iostream>

/*
    Notes : Global Variables

    1. In C++, variables can also be declared outside of a function. Such variables are called global variables.

    2. Declaring global variables

    3. The scope of global variables : Identifiers declared in the global namespace have global namespace scope (commonly called global scope, and sometimes informally called file scope), which means they are visible from the point of declaration until the end of the file in which they are declared.

    namespace Foo // Foo is defined in the global scope
    {
        int g_x {}; // g_x is now inside the Foo namespace, but is still a global variable
    }

    void doSomething()
    {
        // global variables can be seen and used everywhere in the file
        Foo::g_x = 3;
        std::cout << Foo::g_x << '\n';
    }

    Although the identifier g_x is now limited to the scope of namespace Foo, that name is still globally accessible (via Foo::g_x), and g_x is still a global variable.

    Key insight - Variables declared inside a namespace are also global variables.

    4. Prefer defining global variables inside a namespace rather than in the global namespace.

    5. Global variables have static duration - Global variables are created when the program starts (before main() begins execution), and destroyed when it ends. This is called static duration. Variables with static duration are sometimes called static variables.

    6. Global variable initialization - 

        Unlike local variables, which are uninitialized by default, variables with static duration are zero-initialized by default.

        Non-constant global variables can be optionally initialized:

        int g_x;       // no explicit initializer (zero-initialized by default)
        int g_y {};    // value initialized (resulting in zero-initialization)
        int g_z { 1 }; // list initialized with specific value

    7. Constant global variables - Just like local variables, global variables can be constant. As with all constants, constant global variables must be initialized.

    8. A word of caution about (non-constant) global variables : because they can be used without having to explicitly pass them to every function that needs them. However, use of non-constant global variables should generally be avoided altogether!

*/

// Variables declared outside of a function are global variables
int g_x {}; // global variable g_x

const int glo{100};

int main()
{

    return 0;
}