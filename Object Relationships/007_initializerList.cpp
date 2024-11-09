#include <iostream>

/*

    Notes : 

    1. In the previous lesson, we introduced the concept of container classes, and showed an example of an IntArray class that holds an array of integers:

        class IntArray
        {
        private:
            int m_length{};
            int* m_data{};

        public:
            IntArray() = default;

            IntArray(int length)
                : m_length{ length }
            , m_data{ new int[static_cast<std::size_t>(length)] {} }
            {
            }

            ~IntArray()
            {
                delete[] m_data;
                // we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
            }

            int& operator[](int index)
            {
                assert(index >= 0 && index < m_length);
                return m_data[index];
            }

            int getLength() const { return m_length; }
        };

        int main()
        {
            // What happens if we try to use an initializer list with this container class?
            IntArray array { 5, 4, 3, 2, 1 }; // this line doesn't compile
            for (int count{ 0 }; count < 5; ++count)
                std::cout << array[count] << ' ';

            return 0;
        }

    2. Class initialization using std::initializer_list : When a compiler sees an initializer list, it automatically converts it into an object of type std::initializer_list. Therefore, if we create a constructor that takes a std::initializer_list parameter, we can create objects using the initializer list as an input.

    - There are a few things to know about std::initializer_list. Much like std::array or std::vector, you have to tell std::initializer_list what type of data the list holds using angled brackets, unless you initialize the std::initializer_list right away. Therefore, you’ll almost never see a plain std::initializer_list. Instead, you’ll see something like std::initializer_list<int> or std::initializer_list<std::string>.

    - Second, std::initializer_list has a (misnamed) size() function which returns the number of elements in the list. This is useful when we need to know the length of the list passed in.

    - Third, std::initializer_list is often passed by value. Much like std::string_view, std::initializer_list is a view. Copying a std::initializer_list does not copy the elements in the list.

        #include <algorithm> // for std::copy
        #include <cassert> // for assert()
        #include <initializer_list> // for std::initializer_list
        #include <iostream>

        class IntArray
        {
        private:
            int m_length {};
            int* m_data{};

        public:
            IntArray() = default;

            IntArray(int length)
                : m_length{ length }
                , m_data{ new int[static_cast<std::size_t>(length)] {} }
            {

            }

            IntArray(std::initializer_list<int> list) // allow IntArray to be initialized via list initialization
                : IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
            {
                // Now initialize our array from the list
                std::copy(list.begin(), list.end(), m_data);
            }

            ~IntArray()
            {
                delete[] m_data;
                // we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
            }

            IntArray(const IntArray&) = delete; // to avoid shallow copies
            IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies

            int& operator[](int index)
            {
                assert(index >= 0 && index < m_length);
                return m_data[index];
            }

            int getLength() const { return m_length; }
        };

        int main()
        {
            IntArray array{ 5, 4, 3, 2, 1 }; // initializer list
            for (int count{ 0 }; count < array.getLength(); ++count)
                std::cout << array[count] << ' ';

            return 0;
        }

    3. Accessing elements of a std::initializer_list : In some cases, you may want access to each element of the std:initializer_list before copying that element into the internal array (e.g. to sanity check values, or modify those values somehow). For some inexplicable reason, std::initializer_list does not provide access to the elements of the list via subscripting (operator[]). The omission has been noted many times to the standards committee and never addressed.

    4. List initialization prefers list constructors over non-list constructors : Non-empty initializer lists will always favor a matching initializer_list constructor over other potentially matching constructors. Consider:

            IntArray a1(5);   // uses IntArray(int), allocates an array of size 5
            IntArray a2{ 5 }; // uses IntArray<std::initializer_list<int>, allocates array of size 1

        -  The a1 case uses direct initialization (which doesn’t consider list constructors), so this definition will call IntArray(int), allocating an array of size 5.

        - The a2 case uses list initialization (which favors list constructors). Both IntArray(int) and IntArray(std::initializer_list<int>) are possible matches here, but since list constructors are favored, IntArray(std::initializer_list<int>) will be called, allocating an array of size 1 (with that element having value 5).

        - List initialization favors matching list constructors over matching non-list constructors.

        - When initializing a container that has a list constructor:

            1. Use brace initialization when intending to call the list constructor (e.g. because your initializers are element values).

            2. Use direct initialization when intending to call a non-list constructor (e.g. because your initializers are not element values).


    5. Adding list constructors to an existing class is dangerous : Because list initialization favors list constructors, adding a list constructor to an existing class that did not previously have one can cause existing programs to silently change behavior. Adding a list constructor to an existing class that did not have one may break existing programs.

        class Foo
        {
        public:
            Foo(int, int)
            {
                std::cout << "Foo(int, int)" << '\n';
            }

            // We've added a list constructor
            Foo(std::initializer_list<int>)
            {
                std::cout << "Foo(std::initializer_list<int>)" << '\n';
            }

        };

        int main()
        {
            // note that the following statement has not changed
            Foo f1{ 1, 2 }; // now calls Foo(std::initializer_list<int>)

            return 0;
        }


    6. Class assignment using std::initializer_list : You can also use std::initializer_list to assign new values to a class by overloading the assignment operator to take a std::initializer_list parameter. This works analogously to the above. 

        - Note that if you implement a constructor that takes a std::initializer_list, you should ensure you do at least one of the following:

            1. Provide an overloaded list assignment operator
            2. Provide a proper deep-copying copy assignment operator
            3. Delete the copy assignment operator

        - Here’s why: consider the following class (which doesn’t have any of these things), along with a list assignment statement:

            class IntArray
            {
            private:
                int m_length{};
                int* m_data{};

            public:
                IntArray() = default;

                IntArray(int length)
                    : m_length{ length }
                    , m_data{ new int[static_cast<std::size_t>(length)] {} }
                {

                }

                IntArray(std::initializer_list<int> list) // allow IntArray to be initialized via list initialization
                    : IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
                {
                    // Now initialize our array from the list
                    std::copy(list.begin(), list.end(), m_data);
                }

                ~IntArray()
                {
                    delete[] m_data;
                }

            //	IntArray(const IntArray&) = delete; // to avoid shallow copies
            //	IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies

                int& operator[](int index)
                {
                    assert(index >= 0 && index < m_length);
                    return m_data[index];
                }

                int getLength() const { return m_length; }
            };

            int main()
            {
                IntArray array{};
                array = { 1, 3, 5, 7, 9, 11 }; // Here's our list assignment statement

                for (int count{ 0 }; count < array.getLength(); ++count)
                    std::cout << array[count] << ' '; // undefined behavior

                return 0;
            }


        - If you provide list construction, it’s a good idea to provide list assignment as well.

        - First, the compiler will note that an assignment function taking a std::initializer_list doesn’t exist. Next it will look for other assignment functions it could use, and discover the implicitly provided copy assignment operator. However, this function can only be used if it can convert the initializer list into an IntArray. Because { 1, 3, 5, 7, 9, 11 } is a std::initializer_list, the compiler will use the list constructor to convert the initializer list into a temporary IntArray. Then it will call the implicit assignment operator, which will shallow copy the temporary IntArray into our array object.

        - At this point, both the temporary IntArray’s m_data and array->m_data point to the same address (due to the shallow copy). You can already see where this is going.

        - At the end of the assignment statement, the temporary IntArray is destroyed. That calls the destructor, which deletes the temporary IntArray’s m_data. This leaves array->m_data as a dangling pointer. When you try to use array->m_data for any purpose (including when array goes out of scope and the destructor goes to delete m_data), you’ll get undefined behavior.

    7. Summary : Implementing a constructor that takes a std::initializer_list parameter allows us to use list initialization with our custom classes. We can also use std::initializer_list to implement other functions that need to use an initializer list, such as an assignment operator.

*/

#include <algorithm> // for std::copy
#include <cassert> // for assert()
#include <initializer_list> // for std::initializer_list
#include <iostream>

class IntArray
{
private:
	int m_length {};
	int* m_data{};

public:
	IntArray() = default;

	IntArray(int length)
		: m_length{ length }
		, m_data{ new int[static_cast<std::size_t>(length)] {} }
	{

	}

	IntArray(std::initializer_list<int> list) // allow IntArray to be initialized via list initialization
		: IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
	{
		// Now initialize our array from the list
		std::copy(list.begin(), list.end(), m_data);
	}

	~IntArray()
	{
		delete[] m_data;
		// we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
	}

	IntArray(const IntArray&) = delete; // to avoid shallow copies
	IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies

	int& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	int getLength() const { return m_length; }
};

int main()
{
	IntArray array{ 5, 4, 3, 2, 1 }; // initializer list
	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' ';

	return 0;
}