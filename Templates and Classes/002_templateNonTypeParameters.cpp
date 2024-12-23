#include <iostream>
/* 
    Notes :  
    
    1. However, template type parameters are not the only type of template parameters available. Template classes and functions can make use of another kind of template parameter known as a non-type parameter.

    2. Non-type parameters : A template non-type parameter is a template parameter where the type of the parameter is predefined and is substituted for a constexpr value passed in as an argument.

        - A non-type parameter can be any of the following types:

            1. An integral type
            2. An enumeration type
            3. A pointer or reference to a class object
            4. A pointer or reference to a function
            5. A pointer or reference to a class member function
            6. std::nullptr_t
            7. A floating point type (since C++20)

    3. In the following example, we create a non-dynamic (static) array class that uses both a type parameter and a non-type parameter. The type parameter controls the data type of the static array, and the integral non-type parameter controls how large the static array is.

        template <typename T, int size> // size is an integral non-type parameter
        class StaticArray
        {
        private:
            // The non-type parameter controls the size of the array
            T m_array[size] {};

        public:
            T* getArray();

            T& operator[](int index)
            {
                return m_array[index];
            }
        };

        // Showing how a function for a class with a non-type parameter is defined outside of the class
        template <typename T, int size>
        T* StaticArray<T, size>::getArray()
        {
            return m_array;
        }

        int main()
        {
            // declare an integer array with room for 12 integers
            StaticArray<int, 12> intArray;

            // Fill it up in order, then print it backwards
            for (int count { 0 }; count < 12; ++count)
                intArray[count] = count;

            for (int count { 11 }; count >= 0; --count)
                std::cout << intArray[count] << ' ';
            std::cout << '\n';

            // declare a double buffer with room for 4 doubles
            StaticArray<double, 4> doubleArray;

            for (int count { 0 }; count < 4; ++count)
                doubleArray[count] = 4.4 + 0.1 * count;

            for (int count { 0 }; count < 4; ++count)
                std::cout << doubleArray[count] << ' ';

            return 0;
        }

    4. One noteworthy thing about the above example is that we do not have to dynamically allocate the m_array member variable! This is because for any given instance of the StaticArray class, size must be constexpr. For example, if you instantiate a StaticArray<int, 12>, the compiler replaces size with 12. Thus m_array is of type int[12], which can be allocated statically.
    
        - This functionality is used by the standard library class std::array. When you allocate a std::array<int, 5>, the int is a type parameter, and the 5 is a non-type parameter! Note that if you try to instantiate a template non-type parameter with a non-constexpr value, it will not work:

            template <int size>
            class Foo
            {
            };

            int main()
            {
                int x{ 4 }; // x is non-constexpr
                Foo<x> f; // error: the template non-type argument must be constexpr

                return 0;
            }

        - In such a case, your compiler will issue an error.

*/

template <typename T , int size>
class array
{
    T _arr[size]{};

    public:

    T* getArray();

    T& operator[](int index);
};

template <typename T , int size>
T& array<T , size>::operator[](int index)
{
    return _arr[index];
}

template <typename T , int size>
T* array<T , size>::getArray()
{
    return _arr;
}

int main()
{
   array<int , 19> arr;

   std::cout<<arr[0]<<std::endl;

   std::cout<<(arr.getArray()[0])<<std::endl;

    return 0;
}