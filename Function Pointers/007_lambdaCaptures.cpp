#include <iostream>
/* 
    Notes :  
    
    1. Capture clauses and capture by value : 

        auto checkEven {
            []()
            {
                return number % 2 == 0; // number not defined , compile time error
            }
        };

        - This code won’t compile. Unlike nested blocks, where any identifier accessible in the outer block is accessible in the nested block, lambdas can only access certain kinds of objects that have been defined outside the lambda. This includes:

            1. Objects with static (or thread local) storage duration (this includes global variables and static locals)
            
            2. Objects that are constexpr (explicitly or implicitly)

        - Lambdas can only access certain kinds of objects that have been defined outside the lambda, including those with static storage duration (e.g. global variables and static locals) and constexpr objects.

    2. The capture clause - The capture clause is used to (indirectly) give a lambda access to variables available in the surrounding scope that it normally would not have access to. All we need to do is list the entities we want to access from within the lambda as part of the capture clause.

        int number = 10;
        auto checkEven
        {
            [number]()
            {
                return number % 2 == 0;
            }
        };

    3. So how do captures actually work?

        - When a lambda definition is executed, for each variable that the lambda captures, a clone of that variable is made (with an identical name) inside the lambda. These cloned variables are initialized from the outer scope variables of the same name at this point. While these cloned variables have the same name, they don’t necessarily have the same type as the original variable. We’ll explore this in the upcoming sections of this lesson.

        - The captured variables of a lambda are copies of the outer scope variables, not the actual variables.

        - Although lambdas look like functions, they’re actually objects that can be called like functions (these are called functors -- we’ll discuss how to create your own functors from scratch in a future lesson). When the compiler encounters a lambda definition, it creates a custom object definition for the lambda. Each captured variable becomes a data member of the object. At runtime, when the lambda definition is encountered, the lambda object is instantiated, and the members of the lambda are initialized at that point.

    4. Captures are treated as const by default - When a lambda is called, operator() is invoked. By default, this operator() treats captures as const, meaning the lambda is not allowed to modify those captures.

        auto checkEven
        {
            [number]()
            {
                // number--; // cannot be modified , since capture is const by default
                return number % 2 == 0;
            }
        };

    5. Mutable captures - To allow modifications of variables that were captured, we can mark the lambda as mutable:

            int value = 0;
            auto increment
            {
                [value]() mutable
                {
                    value++;
                    std::cout<<"Incremented Value : "<<value<<std::endl;
                }
                
            };

        - Because captured variables are members of the lambda object, their values are persisted across multiple calls to the lambda! But since they are copy of value , it is not changing original value.

    6. Capture by reference - Much like functions can change the value of arguments passed by reference, we can also capture variables by reference to allow our lambda to affect the value of the argument.

    - To capture a variable by reference, we prepend an ampersand (&) to the variable name in the capture. Unlike variables that are captured by value, variables that are captured by reference are non-const, unless the variable they’re capturing is const. Capture by reference should be preferred over capture by value whenever you would normally prefer passing an argument to a function by reference (e.g. for non-fundamental types).

    7. Capturing multiple variables - Multiple variables can be captured by separating them with a comma. This can include a mix of variables captured by value or by reference:

        int health{ 33 };
        int armor{ 100 };
        std::vector<CEnemy> enemies{};

        // Capture health and armor by value, and enemies by reference.
        [health, armor, &enemies](){};

    8. Default captures - A default capture (also called a capture-default) captures all variables that are mentioned in the lambda. Variables not mentioned in the lambda are not captured if a default capture is used.

        1. To capture all used variables by value, use a capture value of =.

        2. To capture all used variables by reference, use a capture value of &.

        - Default captures can be mixed with normal captures. We can capture some variables by value and others by reference, but each variable can only be captured once.

    9. Defining new variables in the lambda-capture - Sometimes we want to capture a variable with a slight modification or declare a new variable that is only visible in the scope of the lambda. We can do so by defining a variable in the lambda-capture without specifying its type.

        auto found{ std::find_if(areas.begin(), areas.end(),

            // Declare a new variable that's visible only to the lambda.
            // The type of userArea is automatically deduced to int.
            [userArea{ width * height }](int knownArea) {
                return userArea == knownArea;
            }) };

        - 'userArea' will only be calculated once when the lambda is defined. The calculated area is stored in the lambda object and is the same for every call. If a lambda is mutable and modifies a variable that was defined in the capture, the original value will be overridden.

        - Only initialize variables in the capture if their value is short and their type is obvious. Otherwise it’s best to define the variable outside of the lambda and capture it.

    10. Dangling captured variables - Variables are captured at the point where the lambda is defined. If a variable captured by reference dies before the lambda, the lambda will be left holding a dangling reference.

        // returns a lambda
        auto makeWalrus(const std::string& name)
        {
            // Capture name by reference and return the lambda.
            return [&]() {
                std::cout << "I am a walrus, my name is " << name << '\n'; // Undefined behavior
            };
        }

        int main()
        {
            // Create a new walrus whose name is Roofus.
            // sayName is the lambda returned by makeWalrus.
            
            auto sayName{ makeWalrus("Roofus") };

            // Call the lambda function that makeWalrus returned.
            sayName();

            return 0;
        }

        - The call to makeWalrus creates a temporary std::string from the string literal “Roofus”. The lambda in makeWalrus captures the temporary string by reference. The temporary string dies when makeWalrus returns, but the lambda still references it. Then when we call sayName, the dangling reference is accessed, causing undefined behavior.

        - Note that this also happens if name is passed to makeWalrus by value. The variable name still dies at the end of makeWalrus, and the lambda is left holding a dangling reference.

        - Be extra careful when you capture variables by reference, especially with a default reference capture. The captured variables must outlive the lambda.

        - If we want the captured name to be valid when the lambda is used, we need to capture it by value instead (either explicitly or using a default-capture by value).


    11. Unintended copies of mutable lambdas - Because lambdas are objects, they can be copied. In some cases, this can cause problems. Consider the following code:

            int i{ 0 };

            // Create a new lambda named count
            auto count{ [i]() mutable {
                std::cout << ++i << '\n';
            } };

            count(); // invoke count

            auto otherCount{ count }; // create a copy of count

            // invoke both count and the copy
            count();
            otherCount();

        - When we created otherCount as a copy of count, we created a copy of count in its current state. count‘s i was 1, so otherCount‘s i is 1 as well. Since otherCount is a copy of count, they each have their own i.

        - Now let’s take a look at a slightly less obvious example: 

            void myInvoke(const std::function<void()>& fn)
            {
                fn();
            }

            int main()
            {
                int i{ 0 };

                // Increments and prints its local copy of @i.
                auto count{ [i]() mutable {
                std::cout << ++i << '\n';
                } };

                myInvoke(count);
                myInvoke(count);
                myInvoke(count);

                return 0;
            }

        - This exhibits the same problem as the prior example in a more obscure form. When we call myInvoke(count), the compiler will see that count (which has a lambda type) doesn’t match the type of the reference parameter type (std::function<void()>). It will convert the lambda into a temporary std::function so that the reference parameter can bind to it, and this will make a copy of the lambda. Thus, our call to fn() is actually being executed on the copy of our lambda that exists as part of the temporary std::function, not the actual lambda.

        - If we need to pass a mutable lambda, and want to avoid the possibility of inadvertent copies being made, there are two options. 
        
            1. One option is to use a non-capturing lambda instead -- in the above case, we could remove the capture and track our state using a static local variable instead. But static local variables can be difficult to keep track of and make our code less readable. 
            
            2. A better option is to prevent copies of our lambda from being made in the first place. But since we can’t affect how std::function (or other standard library functions or objects) are implemented, how can we do this?

                2.1. One option (h/t to reader Dck) is to put our lambda into a std::function immediately. That way, when we call myInvoke(), the reference parameter fn can bind to our std::function, and no temporary copy is made:

                    void myInvoke(const std::function<void()>& fn)
                    {
                        fn();
                    }

                    int main()
                    {
                        int i{ 0 };

                        // Increments and prints its local copy of @i.
                        std::function count{ [i]() mutable { // lambda object stored in a std::function
                        std::cout << ++i << '\n';
                        } };

                        myInvoke(count); // doesn't create copy when called
                        myInvoke(count); // doesn't create copy when called
                        myInvoke(count); // doesn't create copy when called

                        return 0;
                    }

                2.2. An alternate solution is to use a reference wrapper. C++ provides a convenient type (as part of the <functional> header) called std::reference_wrapper that allows us to pass a normal type as if it was a reference. For even more convenience, a std::reference_wrapper can be created by using the std::ref() function. By wrapping our lambda in a std::reference_wrapper, whenever anybody tries to make a copy of our lambda, they’ll make a copy of the reference_wrapper instead (avoiding making a copy of the lambda).

                    // std::ref(count) ensures count is treated like a reference
                    // thus, anything that tries to copy count will actually copy the reference
                    // ensuring that only one count exists
                    myInvoke(std::ref(count));
                    myInvoke(std::ref(count));
                    myInvoke(std::ref(count));

    12. Rule : Standard library functions may copy function objects (reminder: lambdas are function objects). If you want to provide lambdas with mutable captured variables, pass them by reference using std::ref.     

    13. Try to avoid mutable lambdas. Non-mutable lambdas are easier to understand and don’t suffer from the above issues, as well as more dangerous issues that arise when you add parallel execution.                    

*/

#include <functional>

void invoker(const std::function<void(void)> &f)
{
    f();
}
int main()
{
    // constexpr int number = 10; // works fine without clause
    // auto checkEven {
    //     []()
    //     {
    //         return number % 2 == 0;
    //     }
    // };

    int number = 10;

    auto checkEven
    {
        [number]()
        {
            // number--; // cannot be modified , since capture is const by default
            return number % 2 == 0;
        }
    };

    std::cout<<"number "<<number<<" is even ? "<<std::boolalpha<<checkEven()<<std::endl;

    int value = 0;
    auto increment
    {
        [value]() mutable
        {
            value++;
            std::cout<<"Incremented Value : "<<value<<std::endl;
        }
        
    };


    increment();
    increment();

    std::cout<<"Final Value : "<<value<<std::endl;

    auto decrement{

        [&value]()
        {
            --value;
            std::cout<<"Decremented Value : "<<value<<std::endl;
        }
    };

    decrement();
    decrement();

    std::cout<<"Final Value : "<< value<<std::endl;


    auto printer{

        [=]()
        {
            std::cout<<"PRINTER:: ";
            std::cout<<"Number : "<<number<<" Value = "<<value<<std::endl;
        }
    };

    printer();


    int caller = 10 , setter = 11;

    auto printInit{

        [=]()
        {
            std::cout<<"PRINT-INIT:: ";
            std::cout<<"caller = "<<caller<<" setter = "<<setter<<std::endl;
        }
    };

    printInit();
    auto initialize{

        [&]()
        {
            caller = 0;
            setter = 0;
            std::cout<<"INIT:: ";
            std::cout<<"caller = "<<caller<<" setter = "<<setter<<std::endl;
        }

    };

    initialize();
    std::cout<<"caller : "<<caller<<" setter : "<<setter<<std::endl;
    printInit();



    int counter = 0;

    auto count
    {
        [counter]() mutable
        {
            ++counter;
            std::cout<<"Counter = "<<counter<<std::endl;
        }
    };

    count();
    count();

    auto count2{count}; // creates a copy of count in count2

    count2();
    count();

    invoker(count); // keeps calling the copy of count
    invoker(count);
    invoker(count);
    invoker(count);


    std::function count3
    {
        [counter]() mutable
        {
            ++counter;
            std::cout<<"::Counter = "<<counter<<std::endl;
        }
    };

    invoker(count3);
    invoker(count3);
    invoker(count3);
    invoker(std::ref(count3));
    invoker(std::ref(count3));
    invoker(std::ref(count3));



    return 0;
}