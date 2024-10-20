#include <iostream>
/* 
    Notes :  
    
    1. Static member variables - Member variables of a class can be made static by using the static keyword. Unlike normal member variables, static member variables are shared by all objects of the class. 

        struct Something
        {
            static int s_value; // now static
        };

        int Something::s_value{ 1 }; // initialize s_value to 1

        int main()
        {
            Something first{};
            Something second{};

            first.s_value = 2;

            std::cout << first.s_value << '\n';
            std::cout << second.s_value << '\n';
            return 0;
        }

    2. Static members are not associated with class objects : 
    
        - They are created at the start of the program and destroyed at the end of the program, so their lifetime is not bound to a class object like a normal member.

        - Essentially, static members are global variables that live inside the scope region of the class. There is very little difference between a static member of a class and a normal variable inside a namespace.

        class Something
        {
        public:
            static int s_value; // declares the static member variable
        };

        int Something::s_value{ 1 }; // defines the static member variable (we'll discuss this section below)

        int main()
        {
            // note: we're not instantiating any objects of type Something

            Something::s_value = 2;
            std::cout << Something::s_value << '\n';
            return 0;
        }

    3. Defining and initializing static member variables - When we declare a static member variable inside a class type, we’re telling the compiler about the existence of a static member variable, but not actually defining it (much like a forward declaration). Because static member variables are essentially global variables, you must explicitly define (and optionally initialize) the static member outside of the class, in the global scope.

        int Something::s_value{ 1 }; // defines the static member variable
    
        => This line serves two purposes: it instantiates the static member variable (just like a global variable), and initializes it. In this case, we’re providing the initialization value 1. If no initializer is provided, static member variables are zero-initialized by default.

        => Note that this static member definition is not subject to access controls: you can define and initialize the value even if it’s declared as private (or protected) in the class (as definitions are not considered to be a form of access).

        => For non-template classes, if the class is defined in a header (.h) file, the static member definition is usually placed in the associated code file for the class (e.g. Something.cpp). If the class is defined in a source (.cpp) file, the static member definition is usually placed directly underneath the class. Do not put the static member definition in a header file (much like a global variable, if that header file gets included more than once, you’ll end up with multiple definitions, which will cause a linker error).

        => For template classes, the (templated) static member definition is typically placed directly underneath the template class.

    4. Initialization of static member variables inside the class definition - 

        1. There are a few shortcuts to the above. First, when the static member is a constant integral type (which includes char and bool) or a const enum, the static member can be initialized inside the class definition:

            class Whatever
            {
            public:
                static const int s_value{ 4 }; // a static const int can be defined and initialized directly
            };

        In the above example, because the static member variable is a const int, no explicit definition line is needed. This shortcut is allowed because these specific const types are compile-time constants.

        2. We introduced inline variables, which are variables that are allowed to have multiple definitions. C++17 allows static members to be inline variables:

            class Whatever
            {
            public:
                static inline int s_value{ 4 }; // a static inline variable can be defined and initialized directly
            };

            Such variables can be initialized inside the class definition regardless of whether they are constant or not. This is the preferred method of defining and initializing static members.

        3. Because constexpr members are implicitly inline (as of C++17), static constexpr members can also be initialized inside the class definition without explicit use of the inline keyword:

            class Whatever
            {
            public:
                static constexpr double s_value{ 2.2 }; // ok
                static constexpr std::string_view s_view{ "Hello" }; // this even works for classes that support constexpr initialization
            };
        
        => Best practice : Make your static members inline or constexpr so they can be initialized inside the class definition.

    5. Only static members may use type deduction (auto and CTAD)

        1. A static member may use auto to deduce its type from the initializer, or Class Template Argument Deduction (CTAD) to deduce template type arguments from the initializer.

        2. Non-static members may not use auto or CTAD.

        class Foo
        {
        private:
            auto m_x { 5 };           // auto not allowed for non-static members
            std::pair m_v { 1, 2.3 }; // CTAD not allowed for non-static members

            static inline auto s_x { 5 };           // auto allowed for static members
            static inline std::pair s_v { 1, 2.3 }; // CTAD allowed for static members

        public:
            Foo() {};
        };


        The reasons for this distinction being made are quite complicated, but boil down to there being certain cases that can occur with non-static members that lead to ambiguity or non-intuitive results. This does not occur for static members. Thus non-static members are restricted from using these features, whereas static members are not.

*/

class Something
{
public:
    static int s_value; // declares the static member variable
};

int Something::s_value{ 1 }; // defines the static member variable 

int main()
{
    // note: we're not instantiating any objects of type Something

    Something::s_value = 2;
    std::cout << Something::s_value << '\n';
    return 0;
}
