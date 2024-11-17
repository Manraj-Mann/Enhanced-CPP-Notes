#include <iostream>
/* 
    Notes :  
    
    1. Exception specifications are a language mechanism that was originally designed to document what kind of exceptions a function might throw as part of a function specification. While most of the exception specifications have now been deprecated or removed, one useful exception specification was added as a replacement, which we’ll cover in this lesson.

    2. The noexcept specifier : In C++, all functions are classified as either non-throwing or potentially throwing. A non-throwing function is one that promises not to throw exceptions that are visible to the caller. A potentially throwing function may throw exceptions that are visible to the caller.

        - To define a function as non-throwing, we can use the noexcept specifier. To do so, we use the noexcept keyword in the function declaration, placed to the right of the function parameter list:

            void doSomething() noexcept; // this function is specified as non-throwing

        - If an unhandled exception would exit a noexcept function, std::terminate will be called (even if there is an exception handler that would otherwise handle such an exception somewhere up the stack). And if std::terminate is called from inside a noexcept function, stack unwinding may or may not occur (depending on implementation and optimizations), which means your objects may or may not be destructed properly prior to termination.

    3. Illustrating the behavior of noexcept functions and exceptions : 

            class Doomed
            {
            public:
                ~Doomed()
                {
                    std::cout << "Doomed destructed\n";
                }
            };

            void thrower()
            {
                std::cout << "Throwing exception\n";
                throw 1;
            }

            void pt()
            {
                std::cout << "pt (potentally throwing) called\n";
                //This object will be destroyed during stack unwinding (if it occurs)
                Doomed doomed{};
                thrower();
                std::cout << "This never prints\n";
            }

            void nt() noexcept
            {
                std::cout << "nt (noexcept) called\n";
                //This object will be destroyed during stack unwinding (if it occurs)
                Doomed doomed{};
                thrower();
                std::cout << "this never prints\n";
            }

            void tester(int c) noexcept
            {
                std::cout << "tester (noexcept) case " << c << " called\n";
                try
                {
                    (c == 1) ? pt() : nt();
                }
                catch (...)
                {
                    std::cout << "tester caught exception\n";
                }
            }

            int main()
            {
                std::cout << std::unitbuf; // flush buffer after each insertion
                std::cout << std::boolalpha; // print boolean as true/false
                tester(1);
                std::cout << "Test successful\n\n";
                tester(2);
                std::cout << "Test successful\n";

                return 0;
            }

        - On the author’s machine, this program printed:

            tester (noexcept) case 1 called
            pt (potentially throwing) called
            Throwing exception
            Doomed destructed
            tester caught exception
            Test successful

            tester (noexcept) case 2 called
            nt (noexcept) called
            throwing exception
            terminate called after throwing an instance of 'int'

    4. The noexcept specifier with a Boolean parameter : The noexcept specifier has an optional Boolean parameter. noexcept(true) is equivalent to noexcept, meaning the function is non-throwing. noexcept(false) means the function is potentially throwing. These parameters are typically only used in template functions, so that a template function can be dynamically created as non-throwing or potentially throwing based on some parameterized value.

    5. Which functions are non-throwing and potentially-throwing : 

        - Functions that are implicitly non-throwing:

            + Destructors
        
        - Functions that are non-throwing by default for implicitly-declared or defaulted functions:

            +Constructors: default, copy, move
            +Assignments: copy, move
            +Comparison operators (as of C++20)
            
        - However, if any of these functions call (explicitly or implicitly) another function which is potentially throwing, then the listed function will be treated as potentially throwing as well. 
        
        For example, if a class has a data member with a potentially throwing constructor, then the class’s constructors will be treated as potentially throwing as well. As another example, if a copy assignment operator calls a potentially throwing assignment operator, then the copy assignment will be potentially throwing as well.

        - Functions that are potentially throwing (if not implicitly-declared or defaulted):

            + Normal functions
            + User-defined constructors
            + User-defined operators

    6. The noexcept operator : The noexcept operator can also be used inside expressions. It takes an expression as an argument, and returns true or false if the compiler thinks it will throw an exception or not. The noexcept operator is checked statically at compile-time, and doesn’t actually evaluate the input expression. The noexcept operator can be used to conditionally execute code depending on whether it is potentially throwing or not. This is required to fulfill certain exception safety guarantees, which we’ll talk about in the next section.

        void foo() {throw -1;}
        void boo() {};
        void goo() noexcept {};
        struct S{};

        constexpr bool b1{ noexcept(5 + 3) }; // true; ints are non-throwing
        constexpr bool b2{ noexcept(foo()) }; // false; foo() throws an exception
        constexpr bool b3{ noexcept(boo()) }; // false; boo() is implicitly noexcept(false)
        constexpr bool b4{ noexcept(goo()) }; // true; goo() is explicitly noexcept(true)
        constexpr bool b5{ noexcept(S{}) };   // true; a struct's default constructor is noexcept by default

    7. Exception safety guarantees : 

        - An exception safety guarantee is a contractual guideline about how functions or classes will behave in the event an exception occurs. There are four levels of exception safety guarantees:

            + No guarantee -- There are no guarantees about what will happen if an exception is thrown (e.g. a class may be left in an unusable state)
            + Basic guarantee -- If an exception is thrown, no memory will be leaked and the object is still usable, but the program may be left in a modified state.
            + Strong guarantee -- If an exception is thrown, no memory will be leaked and the program state will not be changed. This means the function must either completely succeed or have no side effects if it fails. This is easy if the failure happens before anything is modified in the first place, but can also be achieved by rolling back any changes so the program is returned to the pre-failure state.
            + No throw / No fail guarantee -- The function will always succeed (no-fail) or fail without throwing an exception that is exposed to the caller (no-throw). Exceptions may be thrown internally if not exposed. The noexcept specifier maps to this level of exception safety guarantee.

    8. When to use noexcept  :

        - Best practice :

            + Always make move constructors, move assignment, and swap functions noexcept.
            + Make copy constructors and copy assignment operators noexcept when you can.
            + Use noexcept on other functions to express a no-fail or no-throw guarantee.

        - Best practice :

            If you are uncertain whether a function should have a no-fail/no-throw guarantee, err on the side of caution and do not mark it with noexcept. Reversing a decision to use noexcept violates an interface commitment to the user about the behavior of the function, and may break existing code. Making guarantees stronger by later adding noexcept to a function that was not originally noexcept is considered safe.

*/
int main()
{
    return 0;
}