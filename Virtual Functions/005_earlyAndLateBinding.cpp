#include <iostream>
/* 
    Notes :  
    
    1. When a C++ program is executed, it executes sequentially, beginning at the top of main(). When a function call is encountered, the point of execution jumps to the beginning of the function being called. How does the CPU know to do this? When a program is compiled, the compiler converts each statement in your C++ program into one or more lines of machine language. Each line of machine language is given its own unique sequential address. This is no different for functions -- when a function is encountered, it is converted into machine language and given the next available address. Thus, each function ends up with a unique address.

    2. Binding and dispatching : In general programming, binding is the process of associating names with such properties. Function binding (or method binding) is the process that determines what function definition is associated with a function call. The process of actually invoking a bound function is called dispatching.

    3. Early binding : Most of the function calls the compiler encounters will be direct function calls. A direct function call is a statement that directly calls a function. For example:

        struct Foo
        {
            void printValue(int value)
            {
                std::cout << value;
            }
        };

        void printValue(int value)
        {
            std::cout << value;
        }

        int main()
        {
            printValue(5);   // direct function call to printValue(int)

            Foo f{};
            f.printValue(5); // direct function call to Foo::printValue(int)
            return 0;
        }

        - In C++, when a direct call is made to a non-member function or a non-virtual member function, the compiler can determine which function definition should be matched to the call. This is sometimes called early binding (or static binding), as it can be performed at compile-time. The compiler (or linker) can then generate machine language instructions that tells the CPU to jump directly to the address of the function.
        
        - In C++, when a direct call is made to a non-member function or a non-virtual member function, the compiler can determine which function definition should be matched to the call. This is sometimes called early binding (or static binding), as it can be performed at compile-time. The compiler (or linker) can then generate machine language instructions that tells the CPU to jump directly to the address of the function.

        - Calls to overloaded functions and function templates can also be resolved at compile-time:

            template <typename T>
            void printValue(T value)
            {
                std::cout << value << '\n';
            }

            void printValue(double value)
            {
                std::cout << value << '\n';
            }

            void printValue(int value)
            {
                std::cout << value << '\n';
            }

            int main()
            {
                printValue(5);   // direct function call to printValue(int)
                printValue<>(5); // direct function call to printValue<int>(int)

                return 0;
            }

    4. Late binding : In some cases, a function call can’t be resolved until runtime. In C++, this is sometimes known as late binding (or in the case of virtual function resolution, dynamic dispatch).

        - In general programming terminology, the term “late binding” usually means that the function being called can’t be determined based on static type information alone, but must be resolved using dynamic type information.

        - In C++, the term tends to be used more loosely to mean any function call where the actual function being called is not known by the compiler or linker at the point where the function call is actually being made.


        1. In C++, one way to get late binding is to use function pointers. To review function pointers briefly, a function pointer is a type of pointer that points to a function instead of a variable. The function that a function pointer points to can be called by using the function call operator () on the pointer.

            void printValue(int value)
            {
                std::cout << value << '\n';
            }

            int main()
            {
                auto fcn { printValue }; // create a function pointer and make it point to function printValue
                fcn(5);                  // invoke printValue indirectly through the function pointer

                return 0;
            }

            - Calling a function via a function pointer is also known as an indirect function call. At the point where fcn(5) is actually called, the compiler does not know at compile-time what function is being called. Instead, at runtime, an indirect function call is made to whatever function exists at the address held by the function pointer.

            - The following calculator program is functionally identical to the calculator example above, except it uses a function pointer instead of a direct function call:

            int add(int x, int y)
            {
                return x + y;
            }

            int subtract(int x, int y)
            {
                return x - y;
            }

            int multiply(int x, int y)
            {
                return x * y;
            }

            int main()
            {
                int x{};
                std::cout << "Enter a number: ";
                std::cin >> x;

                int y{};
                std::cout << "Enter another number: ";
                std::cin >> y;

                int op{};
                std::cout << "Enter an operation (0=add, 1=subtract, 2=multiply): ";
                std::cin >> op;

                using FcnPtr = int (*)(int, int); // alias ugly function pointer type
                FcnPtr fcn { nullptr }; // create a function pointer object, set to nullptr initially

                // Set fcn to point to the function the user chose
                switch (op)
                {
                    case 0: fcn = add; break;
                    case 1: fcn = subtract; break;
                    case 2: fcn = multiply; break;
                    default:
                        std::cout << "Invalid operator\n";
                        return 1;
                }

                // Call the function that fcn is pointing to with x and y as parameters
                std::cout << "The answer is: " << fcn(x, y) << '\n';

                return 0;
            }

        2. Late binding is slightly less efficient since it involves an extra level of indirection. With early binding, the CPU can jump directly to the function’s address. With late binding, the program has to read the address held in the pointer and then jump to that address. This involves one extra step, making it slightly slower. However, the advantage of late binding is that it is more flexible than early binding, because decisions about what function to call do not need to be made until runtime. In the next lesson, we’ll take a look at how late binding is used to implement virtual functions.

*/
int main()
{
    return 0;
}