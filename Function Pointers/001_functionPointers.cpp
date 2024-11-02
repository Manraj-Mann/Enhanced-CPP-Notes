#include <iostream>
/* 
    Notes :  
    
    1. Pointer is a variable that holds the address of another variable. Function pointers are similar, except that instead of pointing to variables, they point to functions!

    2. Identifier foo is the function’s name. But what type is the function? Functions have their own l-value function type -- in this case, a function type that returns an integer and takes no parameters. Much like variables, functions live at an assigned address in memory.

    When a function is called (via the () operator), execution jumps to the address of the function being called:

        int foo() // code for foo starts at memory address 0x002717f0
        {
            return 5;
        }

        int main()
        {
            foo(); // jump to address 0x002717f0

            return 0;
        }

    3. At some point in your programming career (if you haven’t already), you’ll probably make a simple mistake:

        int foo() // code starts at memory address 0x002717f0
        {
            return 5;
        }

        int main()
        {
            std::cout << foo << '\n'; // we meant to call foo(), but instead we're printing foo itself!

            return 0;
        }
        
        - Instead of calling function foo() and printing the return value, we’ve unintentionally sent function foo directly to std::cout. What happens in this case?

        - operator<< does not know how to output a function pointer (because there are an infinite number of possible function pointers). The standard says that in this case, foo should be converted to a bool (which operator<< does know how to print). And since the function pointer for foo is a non-void pointer, it should always evaluate to Boolean true. Thus, this should print:

        - Some compilers (e.g. Visual Studio) have a compiler extension that prints the address of the function instead: 0x002717f0. If your platform doesn’t print the function’s address and you want it to, you may be able to force it to do so by converting the function to a void pointer and printing that:

            =>  std::cout << reinterpret_cast<void*>(foo) << '\n'; // Tell C++ to interpret function foo as a void pointer (implementation-defined behavior)

    4. Pointers to functions - The syntax for creating a non-const function pointer is one of the ugliest things you will ever see in C++:

        // fcnPtr is a pointer to a function that takes no arguments and returns an integer
        int (*fcnPtr)();

        - In the above snippet, fcnPtr is a pointer to a function that has no parameters and returns an integer. fcnPtr can point to any function that matches this type.

        - The parentheses around *fcnPtr are necessary for precedence reasons, as int* fcnPtr() would be interpreted as a forward declaration for a function named fcnPtr that takes no parameters and returns a pointer to an integer. To make a const function pointer, the const goes after the asterisk:

            => int (*const fcnPtr)();

    5. Assigning a function to a function pointer - Function pointers can be initialized with a function (and non-const function pointers can be assigned a function). Like with pointers to variables, we can also use &foo to get a function pointer to foo.

    - Function pointers can be initialized with a function (and non-const function pointers can be assigned a function). Like with pointers to variables, we can also use &foo to get a function pointer to foo.

    - Note that the type (parameters and return type) of the function pointer must match the type of the function. Here are some examples of this:

        // function prototypes
        int foo();
        double goo();
        int hoo(int x);

        // function pointer initializers
        int (*fcnPtr1)(){ &foo };    // okay
        int (*fcnPtr2)(){ &goo };    // wrong -- return types don't match!
        double (*fcnPtr4)(){ &goo }; // okay
        fcnPtr1 = &hoo;              // wrong -- fcnPtr1 has no parameters, but hoo() does
        int (*fcnPtr3)(int){ &hoo }; // okay

    6. Unlike fundamental types, C++ will implicitly convert a function into a function pointer if needed (so you don’t need to use the address-of operator (&) to get the function’s address). However, function pointers will not convert to void pointers, or vice-versa (though some compilers like Visual Studio may allow this anyway).

        // function prototypes
        int foo();

        // function initializations
        int (*fcnPtr5)() { foo }; // okay, foo implicitly converts to function pointer to foo
        void* vPtr { foo };       // not okay, though some compilers may allow

    7. Function pointers can also be initialized or assigned the value nullptr:

        int (*fcnptr)() { nullptr }; // okay

    8. Calling a function using a function pointer - The other primary thing you can do with a function pointer is use it to actually call the function. There are two ways to do this. The first is via explicit dereference:

            int foo(int x)
            {
                return x;
            }

            int main()
            {
                int (*fcnPtr)(int){ &foo }; // Initialize fcnPtr with function foo
                (*fcnPtr)(5); // call function foo(5) through fcnPtr.

                return 0;
            }

        - The second way is via implicit dereference:

            int (*fcnPtr)(int){ &foo }; // Initialize fcnPtr with function foo
            fcnPtr(5); // call function foo(5) through fcnPtr.

        - As you can see, the implicit dereference method looks just like a normal function call -- which is what you’d expect, since normal function names are pointers to functions anyway! However, some older compilers do not support the implicit dereference method, but all modern compilers should.

    9. Also note that because function pointers can be set to nullptr, it’s a good idea to assert or conditionally test whether your function pointer is a null pointer before calling it. Just like with normal pointers, dereferencing a null function pointer leads to undefined behavior.

        int foo(int x)
        {
            return x;
        }

        int main()
        {
            int (*fcnPtr)(int){ &foo }; // Initialize fcnPtr with function foo
            if (fcnPtr) // make sure fcnPtr isn't a null pointer
                fcnPtr(5); // otherwise this will lead to undefined behavior

            return 0;
        }

    10. Default arguments don’t work for functions called through function pointers - When the compiler encounters a normal function call to a function with one or more default arguments, it rewrites the function call to include the default arguments. This process happens at compile-time, and thus can only be applied to functions that can be resolved at compile time. However, when a function is called through a function pointer, it is resolved at runtime. In this case, there is no rewriting of the function call to include default arguments.

    - This means that we can use a function pointer to disambiguate a function call that would otherwise be ambiguous due to default arguments. In the following example, we show two ways to do this: 

        void print(int x)
        {
            std::cout << "print(int)\n";
        }

        void print(int x, int y = 10)
        {
            std::cout << "print(int, int)\n";
        }

        int main()
        {
            // print(1); // ambiguous function call

            // Deconstructed method
            using vnptr = void(*)(int); // define a type alias for a function pointer to a void(int) function
            vnptr pi { print }; // initialize our function pointer with function print
            pi(1); // call the print(int) function through the function pointer

            // Concise method
            static_cast<void(*)(int)>(print)(1); // call void(int) version of print with argument 1

            return 0;
        }

    11. Passing functions as arguments to other functions :One of the most useful things to do with function pointers is pass a function as an argument to another function. Functions used as arguments to another function are sometimes called callback functions.

        Consider a case where you are writing a function to perform a task (such as sorting an array), but you want the user to be able to define how a particular part of that task will be performed (such as whether the array is sorted in ascending or descending order). Let’s take a closer look at this problem as applied specifically to sorting, as an example that can be generalized to other similar problems. 

        Many comparison-based sorting algorithms work on a similar concept: the sorting algorithm iterates through a list of numbers, does comparisons on pairs of numbers, and reorders the numbers based on the results of those comparisons. Consequently, by varying the comparison, we can change the way the algorithm sorts without affecting the rest of the sorting code.

        - Normal : void SelectionSort(int* array, int size)

        - F pointer : void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))

        As you can see, using a function pointer in this context provides a nice way to allow a caller to “hook” their own functionality into something you’ve previously written and tested, which helps facilitate code reuse! Previously, if you wanted to sort one array in descending order and another in ascending order, you’d need multiple versions of the sort routine. Now you can have one version that can sort any way the caller desires!

        Note: If a function parameter is of a function type, it will be converted to a pointer to the function type. This means:

            => void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
        
        can be equivalently written as:

            => void selectionSort(int* array, int size, bool comparisonFcn(int, int))
        
        This only works for function parameters, and so is of somewhat limited use. On a non-function parameter, the latter is interpreted as a forward declaration:

            bool (*ptr)(int, int); // definition of function pointer ptr
            bool fcn(int, int);    // forward declaration of function fcn

    12. Making function pointers prettier with type aliases : 

        Let’s face it -- the syntax for pointers to functions is ugly. However, type aliases can be used to make pointers to functions look more like regular variables:

            -> using ValidateFunction = bool(*)(int, int);

            This defines a type alias called “ValidateFunction” that is a pointer to a function that takes two ints and returns a bool.

        Now instead of doing this:

            -> bool validate(int x, int y, bool (*fcnPtr)(int, int)); // ugly
        
        You can do this:

            -> bool validate(int x, int y, ValidateFunction pfcn) // clean

    13. Using std::function : 

        - An alternate method of defining and storing function pointers is to use std::function, which is part of the standard library <functional> header. To define a function pointer using this method, declare a std::function object like so:

            #include <functional>
            bool validate(int x, int y, std::function<bool(int, int)> fcn); // std::function method that returns a bool and takes two int parameters

        - As you see, both the return type and parameters go inside angled brackets, with the parameters inside parentheses. If there are no parameters, the parentheses can be left empty.

        - Type aliasing std::function can be helpful for readability:

            using ValidateFunctionRaw = bool(*)(int, int); // type alias to raw function pointer
            using ValidateFunction = std::function<bool(int, int)>; // type alias to std::function
            
        - Also note that std::function only allows calling the function via implicit dereference (e.g. fcnPtr()), not explicit dereference (e.g. (*fcnPtr)()).

        - When defining a type alias, we must explicitly specify any template arguments. We can’t use CTAD in this case since there is no initializer to deduce the template arguments from.

    14. Type inference for function pointers : 
    
        - Much like the auto keyword can be used to infer the type of normal variables, the auto keyword can also infer the type of a function pointer.

            int foo(int x)
            {
                return x;
            }

            int main()
            {
                auto fcnPtr{ &foo };
                std::cout << fcnPtr(5) << '\n';

                return 0;
            }

    15. Function pointers are useful primarily when you want to store functions in an array (or other structure), or when you need to pass a function to another function. Because the native syntax to declare function pointers is ugly and error prone, we recommend using std::function. In places where a function pointer type is only used once (e.g. a single parameter or return value), std::function can be used directly. In places where a function pointer type is used multiple times, a type alias to a std::function is a better choice (to prevent repeating yourself).


*/
#include <functional>

int foo()
{
    return 0;
}
int goo()
{
    return 1;
}

void hoo()
{

}

int loo(int x)
{
    return x;
}
int shoo(int x)
{
    return 2*x;
}

void print(int x)
{
    std::cout << "print(int)\n";
}

void print(int x, int y = 10)
{
    std::cout << "print(int, int)\n";
}

void caller(bool func(int , int))
{
    func(10 , 30);
}
void caller2(bool (*func)(int , int))
{
    func(10 , 20);
}

void caller3(std::function<void (int , int)> func)
{
    func(20 , 40);
}

bool pickachu(int a, int b)
{
    std::cout<<"Pikachu "<<a<<" pika pika "<<b<<std::endl;
    return a == b;
}
int main()
{
    int (*fptr)(){&goo};

    fptr = &foo;

    int (*gptr)(){goo};

    void (*hptr)(){hoo};

    int (*lptr)(int){loo};
    
    std::cout<<"Loo : "<<(*lptr)(100)<<std::endl;
    std::cout<<"Loo : "<<lptr(100)<<std::endl;

    lptr = nullptr;

    if(!lptr)
    {
        std::cout<<"lptr is null"<<std::endl;
    }

    lptr = &shoo;


    if(lptr)
    {
        std::cout<<"lptr is not null : "<<lptr(100)<<std::endl;
    }

    // print(1); // error while compilation

    using vnptr = void(*)(int); // define a type alias for a function pointer to a void(int) function
    vnptr pi { print }; // initialize our function pointer with function print
    pi(1); // call the print(int) function through the function pointer

    using vptr2 = void(*)(int,int);
    vptr2 pt2(print);
    pt2(1 , 2);

    // Concise method
    static_cast<void(*)(int)>(print)(1); // call void(int) version of print with argument 1

    caller(pickachu);
    caller2(pickachu);
    caller3(pickachu);

    // std::function<bool(int ,int)> ptr{pickachu};
    using fcaller = std::function<bool(int , int)>;
    fcaller ptr {pickachu};

    ptr(100 , 20);

    auto ptr2{pickachu};

    ptr2(10000 , 30000);


    return 0;
}