#include <iostream>

/*
    Note : 

    1. The initialization order problem of global variables
       
       Initialization of static variables (which includes global variables) happens as part of program startup, before execution of the main function. 
       
       This proceeds in two phases : 

       1. The first phase is called static initialization. 
          In the static initialization phase, global variables with constexpr initializers (including literals) are initialized to those values. Also, global variables without initializers are zero-initialized.

       2. The second phase is called dynamic initialization. 
          This phase is more complex and nuanced, but the gist of it is that global variables with non-constexpr initializers are initialized.

        int init()
        {
            return 5;
        }

        int g_something{ init() }; // non-constexpr initialization

        Within a single file, for each phase, global variables are generally initialized in order of definition (there are a few exceptions to this rule for the dynamic initialization phase).

    2. Much more of a problem, the order in which static objects are initialized across different translation units is ambiguous.

    3. The ambiguity in the order that objects with static storage duration in different translation units are initialized is often called the static initialization order fiasco.
       
       The static initialization order fiasco refers to the ambiguity in the order that objects with static storage duration in different translation units are initialized in. 
       If an object in one translation unit relies on an object in another translation unit already being initialized, a crash can occur if the compiler decides to initialize them in the wrong order.        
       The Construct on "First Use Idiom" can be used to avoid the static initialization order fiasco and ensure that all objects are initialized in the correct order.

    4. Protecting yourself from global destruction:

        => First, prefix all non-namespaced global variables with “g” or “g_”, or better yet, put them in a namespace , to reduce the chance of naming collisions.

        namespace constants
        {
            constexpr double gravity { 9.8 };
        }

        => Second, instead of allowing direct access to the global variable, it’s a better practice to “encapsulate” the variable. Make sure the variable can only be accessed from within the file it’s declared in, e.g. by making the variable static or const, then provide external global “access functions” to work with the variable. 

        bad bad : 
        namespace constants
        {
            extern const double gravity { 9.8 }; // has external linkage, can be accessed by other files
        }

        namespace constants
        {
            extern const double gravity; // forward declaration
        }

        good good : 

        namespace constants
        {
            constexpr double gravity { 9.8 }; // has internal linkage, is accessible only within this file
        }

        double getGravity() // has external linkage, can be accessed by other files
        {
            // We could add logic here if needed later
            // or change the implementation transparently to the callers
            return constants::gravity;
        }

        Note : Global const variables have internal linkage by default, gravity doesn’t need to be static.

    5. Third, when writing an otherwise standalone function that uses the global variable, don’t use the variable directly in your function body. Pass it in as an argument instead. That way, if your function ever needs to use a different value for some circumstance, you can simply vary the argument. This helps maintain modularity.

    

*/


int initX();  // forward declaration
int initY();  // forward declaration

int g_x{ initX() }; // g_x is initialized first
int g_y{ initY() };

int initX()
{
    return g_y; // g_y isn't initialized when this is called
}

int initY()
{
    return 5;
}

int main()
{
    std::cout << g_x << ' ' << g_y << '\n';
}