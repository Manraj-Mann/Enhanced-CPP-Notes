#include <iostream>
/* 
    Notes :  
    
    1. Overloading operator[] : 

        However, a better solution in this case is to overload the subscript operator ([]) to allow access to the elements of m_list. The subscript operator is one of the operators that must be overloaded as a member function. An overloaded operator[] function will always take one parameter: the subscript that the user places between the hard braces. In our IntList case, we expect the user to pass in an integer index, and we’ll return an integer value back as a result.

            class IntList
            {
            private:
                int m_list[10]{};

            public:
                int& operator[] (int index)
                {
                    return m_list[index];
                }
            };

    2. Now, whenever we use the subscript operator ([]) on an object of our class, the compiler will return the corresponding element from the m_list member variable! This allows us to both get and set values of m_list directly.

        - This is both easy syntactically and from a comprehension standpoint. When list[2] evaluates, the compiler first checks to see if there’s an overloaded operator[] function. If so, it passes the value inside the hard braces (in this case, 2) as an argument to the function.

    3. Let’s take a closer look at how list[2] = 3 evaluates. Because the subscript operator has a higher precedence than the assignment operator, list[2] evaluates first. list[2] calls operator[], which we’ve defined to return a reference to list.m_list[2]. Because operator[] is returning a reference, it returns the actual list.m_list[2] array element. Our partially evaluated expression becomes list.m_list[2] = 3, which is a straightforward integer assignment.

        - In lesson 12.2 -- Value categories (lvalues and rvalues), you learned that any value on the left hand side of an assignment statement must be an l-value (which is a variable that has an actual memory address). Because the result of operator[] can be used on the left hand side of an assignment (e.g. list[2] = 3), the return value of operator[] must be an l-value. As it turns out, references are always l-values, because you can only take a reference of variables that have memory addresses. So by returning a reference, the compiler is satisfied that we are returning an l-value.

    4. Overloaded operator[] for const objects - In the above IntList example, operator[] is non-const, and we can use it as an l-value to change the state of non-const objects. However, what if our IntList object was const? In this case, we wouldn’t be able to call the non-const version of operator[] because that would allow us to potentially change the state of a const object.

        - The good news is that we can define a non-const and a const version of operator[] separately. The non-const version will be used with non-const objects, and the const version with const-objects.

        - Example : 

            class IntList
            {
            private:
                int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // give this class some initial state for this example

            public:
                // For non-const objects: can be used for assignment
                int& operator[] (int index)
                {
                    return m_list[index];
                }

                // For const objects: can only be used for access
                // This function could also return by value if the type is cheap to copy
                const int& operator[] (int index) const
                {
                    return m_list[index];
                }
            };

    5. Removing duplicate code between const and non-const overloads : 

        - In such a case, the redundancy introduced by having many duplicate statements is more problematic, and it would be desirable to have a single implementation that we could use for both overloads. But how? Normally we’d simply implement one function in terms of the other (e.g. have one function call the other). But that’s a bit tricky in this case. The const version of the function can’t call the non-const version of the function, because that would require discarding the const of a const object. And while the non-const version of the function can call the const version of the function, the const version of the function returns a const reference, when we need to return a non-const reference. Fortunately, there is a way to work around this.

        - The preferred solution is as follows:

            - Implement the logic for the const version of the function.
            
            - Have the non-const function call the const function and use const_cast to remove the const.

        - Example : 

            class IntList
            {
            private:
                int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // give this class some initial state for this example

            public:
                int& operator[] (int index)
                {
                    // use std::as_const to get a const version of `this` (as a reference)
                    // so we can call the const version of operator[]
                    // then const_cast to discard the const on the returned reference
                    return const_cast<int&>(std::as_const(*this)[index]);
                }

                const int& operator[] (int index) const
                {
                    return m_list[index];
                }
            };

        - Normally using const_cast to remove const is something we want to avoid, but in this case it’s acceptable. If the non-const overload was called, then we know we’re working with a non-const object. It’s okay to remove the const on a const reference to a non-const object.

        - In C++23, we can do even better by making use of several features we don’t yet cover in this tutorial series:

            class IntList
            {
            private:
                int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // give this class some initial state for this example

            public:
                // Use an explicit object parameter (self) and auto&& to differentiate const vs non-const
                auto&& operator[](this auto&& self, int index)
                {
                    // Complex code goes here
                    return self.m_list[index];
                }
            };

    6. Detecting index validity - One other advantage of overloading the subscript operator is that we can make it safer than accessing arrays directly. Normally, when accessing arrays, the subscript operator does not check whether the index is valid. 

        class IntList
        {
        private:
            int m_list[10]{};

        public:
            int& operator[] (int index)
            {
                assert(index >= 0 && static_cast<std::size_t>(index) < std::size(m_list));

                return m_list[index];
            }
        };

    7. Pointers to objects and overloaded operator[] don’t mix : If you try to call operator[] on a pointer to an object, C++ will assume you’re trying to index an array of objects of that type.

        class IntList
        {
        private:
            int m_list[10]{};

        public:
            int& operator[] (int index)
            {
                return m_list[index];
            }
        };

        int main()
        {
            IntList* list{ new IntList{} };
            list [2] = 3; // error: this will assume we're accessing index 2 of an array of IntLists
            delete list;

            return 0;
        }

    8. The function parameter does not need to be an integral type - As mentioned above, C++ passes what the user types between the hard braces as an argument to the overloaded function. In most cases, this will be an integral value. However, this is not required -- and in fact, you can define that your overloaded operator[] take a value of any type you desire. You could define your overloaded operator[] to take a double, a std::string, or whatever else you like.

        Example : 

            #include <iostream>
            #include <string_view> // C++17

            class Stupid
            {
                private:

                public:
                    void operator[] (std::string_view index);
            };

            // It doesn't make sense to overload operator[] to print something
            // but it is the easiest way to show that the function parameter can be a non-integer
            void Stupid::operator[] (std::string_view index)
            {
                std::cout << index;
            }

            int main()
            {
                Stupid stupid{};
                stupid["Hello, world!"];

                return 0;
            }




*/

class IntList 
{
    int arr[10] = {100};

    public:

    int & operator[](int index)
    {
        return arr[index];
    }

    const int& operator[](int index) const
    {
        return arr[index];
    }
};


int main()
{
    IntList list;

    list[4] = 10;

    std::cout<<"Value : "<<list[4]<<std::endl;

    const IntList list2;

    std::cout<<"value - "<<list2[0]<<std::endl;

    IntList* list3{ new IntList{} };
    // list3 [2] = 3; // error: this will assume we're accessing index 2 of an array of IntLists
    IntList &l = list3[0];
    std::cout<<"Value : "<<l[0]<<std::endl;

    delete list3;

    return 0;
}