#include <iostream>
#include <vector>
/*

    Notes:

    1. In c++ templates are used to create generic functions and classes to work with any data type. In templates we can use one or more placeholder types. Ones a template is defined , compiler generates the appropriate function or class based on the data type used.

    2. Templates can even work with types which are not known at the time of writing the code. So it helps in making code future proof.

    3. A function template is a function like definition that is used to generate one or more overloads of a function at compile time. When we create a function template , we use placeholder types ( also called template parameters) for any parameter types , return types or types used in the function body that are not known at the time of writing the code.

    4. Template parameters are of three types:
        a. Type parameters: These are used to specify the type of the data that the function will work with.

            Example:
            template <typename T>
            T add(T a, T b)
            {
                return a + b;
            }

            Explanation : Here T is a type parameter. It is used to specify the type of the data that the function will work with. The function add can be called with any data type.

        b. Non-type parameters: These are used to specify a value that is not a type. ( where template parameter represents a constexpr value)

            Example:
            template <int N>
            void printArray(int (&arr)[N])
            {
                for(int i = 0; i < N; i++)
                {
                    std::cout << arr[i] << " ";
                }
            }

            Explanation: Here N is a non-type parameter. The datatype N would be the type specified in the template parameter.It is used to specify the size of the array. The function printArray can be called with an array of any size.

            Call to the function:

            int arr1[] = {1, 2, 3, 4, 5};
            printArray(arr1);            

        c. Template template parameters: These are used to specify a template as a parameter. ( will cover in future)

    5. Template parameter declaration: It is used to specify the type of the data that the function will work with.
        
        template <typename T> // this is a template parameter declaration

    6. Typename and class are used interchangeably in template parameter declaration. Both are used to specify the type of the data that the function will work with.
    
    Example - template <typename T> and template <class T> are same.


    7. Template Parameter Naming  - Good to have start with capital letters like T, U, V etc. This is a convention followed in c++. Followed by some meaningful name.

    Example:

    template <typename T, typename U>
    template <typename TAllocator, typename TContainer>

*/


template <typename T>
T add(T a, T b)
{
    return a + b;
}

template <int N>
void printArray(int (&arr)[N])
{
    for(int i = 0; i < N; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout<<std::endl;
}

template <class T>
void printNumber(T a)
{
    std::cout<<a<<std::endl;
}

int main()
{   
    std::cout << add(1, 2) << std::endl;
    std::cout << add(1.1, 2.2) << std::endl;
    std::cout << add('a', 'b') << std::endl;

    // std::cout<<add(1 , 12.34f)<<std::endl; // This will give error as the data types are different
    // deduced conflicting types for parameter ‘T’ (‘int’ and ‘float’)


    int arr1[] = {1, 2, 3, 4, 5};
    printArray(arr1);

    printNumber(10);


   
    return 0;
}