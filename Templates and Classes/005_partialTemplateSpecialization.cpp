#include <iostream>
/* 
    Notes :  
    
    1. Let’s take another look at the Static Array class we used in one of our previous examples:

        template <typename T, int size> // size is the expression parameter
        class StaticArray
        {
        private:
            // The expression parameter controls the size of the array
            T m_array[size]{};

        public:
            T* getArray() { return m_array; }

            const T& operator[](int index) const { return m_array[index]; }
            T& operator[](int index) { return m_array[index]; }
        };

        int main()
        {
            // Declare a char array
            StaticArray<char, 14> char14{};

            // Copy some data into it
            constexpr std::string_view hello{ "Hello, world!" };
            std::copy_n(hello.begin(), hello.size(), char14.getArray());

            // Print the array
            print(char14);

            return 0;
        }

        - This program will compile, execute, and produce the following value (or one similar):

                H e l l o ,   w o r l d !
        
        - For non-char types, it makes sense to put a space between each array element, so they don’t run together. However, with a char type, it makes more sense to print everything run together as a C-style string, which our print() function doesn’t do. So how can we fix this?

    2. Template specialization to the rescue?

        template <typename T, int size> // size is the expression parameter
        class StaticArray
        {
        private:
            // The expression parameter controls the size of the array
            T m_array[size]{};

        public:
            T* getArray() { return m_array; }

            const T& operator[](int index) const { return m_array[index]; }
            T& operator[](int index) { return m_array[index]; }
        };

        template <typename T, int size>
        void print(const StaticArray<T, size>& array)
        {
            for (int count{ 0 }; count < size; ++count)
                std::cout << array[count] << ' ';
        }

        // Override print() for fully specialized StaticArray<char, 14>
        template <>
        void print(const StaticArray<char, 14>& array)
        {
            for (int count{ 0 }; count < 14; ++count)
                std::cout << array[count];
        }


        - Although this solves the issue of making sure print() can be called with a StaticArray<char, 14>, it brings up another problem: using full template specialization means we have to explicitly define the length of the array this function will accept! Consider the following example:  StaticArray<char, 12> char12{};


    3. Partial template specialization : Partial template specialization allows us to specialize classes (but not individual functions!) where some, but not all, of the template parameters have been explicitly defined. For our challenge above, the ideal solution would be to have our overloaded print function work with StaticArray of type char, but leave the length expression parameter templated so it can vary as needed. Partial template specialization allows us to do just that!

        - Here’s our example with an overloaded print function that takes a partially specialized StaticArray:

            // overload of print() function for partially specialized StaticArray<char, size>
            template <int size> // size is still a template non-type parameter
            void print(const StaticArray<char, size>& array) // we're explicitly defining type char here
            {
                for (int count{ 0 }; count < size; ++count)
                    std::cout << array[count];
            }

        - Code : 

            template <typename T, int size> // size is the expression parameter
            class StaticArray
            {
            private:
                // The expression parameter controls the size of the array
                T m_array[size]{};

            public:
                T* getArray() { return m_array; }

                const T& operator[](int index) const { return m_array[index]; }
                T& operator[](int index) { return m_array[index]; }
            };

            template <typename T, int size>
            void print(const StaticArray<T, size>& array)
            {
                for (int count{ 0 }; count < size; ++count)
                    std::cout << array[count] << ' ';
            }

            // overload of print() function for partially specialized StaticArray<char, size>
            template <int size>
            void print(const StaticArray<char, size>& array)
            {
                for (int count{ 0 }; count < size; ++count)
                    std::cout << array[count];
            }

            int main()
            {
                // Declare an char array of size 14
                StaticArray<char, 14> char14{};

                // Copy some data into it
                constexpr std::string_view hello14{ "Hello, world!" };
                std::copy_n(hello14.begin(), hello14.size(), char14.getArray());

                // Print the array
                print(char14);

                std::cout << ' ';

                // Now declare an char array of size 12
                StaticArray<char, 12> char12{};

                // Copy some data into it
                constexpr std::string_view hello12{ "Hello, mom!" };
                std::copy_n(hello12.begin(), hello12.size(), char12.getArray());

                // Print the array
                print(char12);

                return 0;
            }

    4. Partial template specialization can only be used with classes, not template functions (functions must be fully specialized). Our void print(StaticArray<char, size> &array) example works because the print function is not partially specialized (it’s just an overloaded template function that happens to have a partially-specialized class parameter).

    5. Partial template specialization for member functions : 

        - The limitation on the partial specialization of functions can lead to some challenges when dealing with member functions. For example, what if we had defined StaticArray like this?

            template <typename T, int size>
            class StaticArray
            {
            private:
                T m_array[size]{};

            public:
                T* getArray() { return m_array; }

                const T& operator[](int index) const { return m_array[index]; }
                T& operator[](int index) { return m_array[index]; }

                void print() const;
            };

            template <typename T, int size>
            void StaticArray<T, size>::print() const
            {
                for (int i{ 0 }; i < size; ++i)
                    std::cout << m_array[i] << ' ';
                std::cout << '\n';
            }

        - print() is now a member function of class StaticArray<T, int>. So what happens when we want to partially specialize print(), so that it works differently? You might try this:

            // Doesn't work, can't partially specialize functions
            template <int size>
            void StaticArray<double, size>::print() const
            {
                for (int i{ 0 }; i < size; ++i)
                    std::cout << std::scientific << m_array[i] << ' ';
                std::cout << '\n';
            }

        - So how do we get around this? One obvious way is to partially specialize the entire class.However, this isn’t a great solution, because we have to duplicate a lot of code . If only there were some way to reuse the code in StaticArray<T, size> in StaticArray<double, size>. Sounds like a job for inheritance!

            template <int size> // size is the expression parameter
            class StaticArray<double, size>: public StaticArray<T, size>

            But this doesn’t work, because we’ve used T without defining it. There is no syntax that allows us to inherit in such a manner.


        - Fortunately, there’s a workaround, by using a common base class:

            template <typename T, int size>
            class StaticArray_Base
            {
            protected:
                T m_array[size]{};

            public:
                T* getArray() { return m_array; }

                const T& operator[](int index) const { return m_array[index]; }
                T& operator[](int index) { return m_array[index]; }

                void print() const
                {
                    for (int i{ 0 }; i < size; ++i)
                        std::cout << m_array[i] << ' ';
                    std::cout << '\n';
                }

                // Don't forget a virtual destructor if you're going to use virtual function resolution
            };

            template <typename T, int size>
            class StaticArray: public StaticArray_Base<T, size>
            {
            };

            template <int size>
            class StaticArray<double, size>: public StaticArray_Base<double, size>
            {
            public:

                void print() const
                {
                    for (int i{ 0 }; i < size; ++i)
                        std::cout << std::scientific << this->m_array[i] << ' ';
            // note: The this-> prefix in the above line is needed.
            // See https://stackoverflow.com/a/6592617 or https://isocpp.org/wiki/faq/templates#nondependent-name-lookup-members for more info on why.
                    std::cout << '\n';
                }
            };

    6. Why using this ? 

        template<typename T>
        class B 
        {
            public:
            void f() { }  // Member of class B<T>
        };

        template<typename T>
        class D : public B<T> 
        {
            public:
            void g()
            {
                f();  // Bad (even though some compilers erroneously (temporarily?) accept it)
            }
        };

        - Within D<T>::g(), the name f does not depend on template parameter T, so f is known as a nondependent name. On the other hand, B<T> is dependent on template parameter T so B<T> is called a dependent name.

        - Here’s the rule: the compiler does not look in dependent base classes (like B<T>) when looking up nondependent names (like f).

        - This doesn’t mean that inheritance doesn’t work. Class D<int> is still derived from class B<int>, the compiler still lets you implicitly do the is-a conversions (e.g., D<int>* to B<int>*), dynamic binding still works when virtual functions are invoked, etc. But there is an issue about how names are looked up.

        - Workarounds:

            1. Change the call from f() to this->f(). Since this is always implicitly dependent in a template, this->f is dependent and the lookup is therefore deferred until the template is actually instantiated, at which point all base classes are considered.
        
            2. Insert using B<T>::f; just prior to calling f().
        
            3. Change the call from f() to B<T>::f(). Note however that this might not give you what you want if f() is virtual, since it inhibits the virtual dispatch mechanism.

*/


template <typename T, int size>
class StaticArray_Base
{
protected:
	T m_array[size]{};

public:
	T* getArray() { return m_array; }

	const T& operator[](int index) const { return m_array[index]; }
	T& operator[](int index) { return m_array[index]; }

	void print() const
	{
		for (int i{ 0 }; i < size; ++i)
			std::cout << m_array[i] << ' ';
		std::cout << '\n';
	}

	// Don't forget a virtual destructor if you're going to use virtual function resolution
};

template <typename T, int size>
class StaticArray: public StaticArray_Base<T, size>
{
};

template <int size>
class StaticArray<double, size>: public StaticArray_Base<double, size>
{
public:

	void print() const
	{
		for (int i{ 0 }; i < size; ++i)
			std::cout << std::scientific << this->m_array[i] << ' ';
// note: The this-> prefix in the above line is needed.
// See https://stackoverflow.com/a/6592617 or https://isocpp.org/wiki/faq/templates#nondependent-name-lookup-members for more info on why.
		std::cout << '\n';
	}
};

int main()
{
	// declare an integer array with room for 6 integers
	StaticArray<int, 6> intArray{};

	// Fill it up in order, then print it
	for (int count{ 0 }; count < 6; ++count)
		intArray[count] = count;

	intArray.print();

	// declare a double buffer with room for 4 doubles
	StaticArray<double, 4> doubleArray{};

	for (int count{ 0 }; count < 4; ++count)
		doubleArray[count] = (4.0 + 0.1 * count);

	doubleArray.print();

	return 0;
}