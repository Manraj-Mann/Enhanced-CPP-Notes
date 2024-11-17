#include <iostream>
/* 
    Notes :  
    
    1. We saw how it was possible to specialize functions in order to provide different functionality for specific data types. As it turns out, it is not only possible to specialize functions, it is also possible to specialize classes!

    2. Consider the case where you want a class that stores 8 objects. Here’s a simplified class template to do so:

        template <typename T>
        class Storage8
        {
        private:
            T m_array[8];

        public:
            void set(int index, const T& value)
            {
                m_array[index] = value;
            }

            const T& get(int index) const
            {
                return m_array[index];
            }
        };

        int main()
        {
            // Define a Storage8 for integers
            Storage8<int> intStorage;

            for (int count{ 0 }; count < 8; ++count)
                intStorage.set(count, count);

            for (int count{ 0 }; count < 8; ++count)
                std::cout << intStorage.get(count) << '\n';

            // Define a Storage8 for bool
            Storage8<bool> boolStorage;
            for (int count{ 0 }; count < 8; ++count)
                boolStorage.set(count, count & 3);

            std::cout << std::boolalpha;

            for (int count{ 0 }; count < 8; ++count)
            {
                std::cout << boolStorage.get(count) << '\n';
            }

            return 0;
        }

        - While this class is completely functional, it turns out that the implementation of Storage8<bool> is more inefficient than it needs to be. Because all variables must have an address, and the CPU can’t address anything smaller than a byte, all variables must be at least a byte in size. Consequently, a variable of type bool ends up using an entire byte even though technically it only needs a single bit to store its true or false value! Thus, a bool is 1 bit of useful information and 7 bits of wasted space. Our Storage8<bool> class, which contains 8 bool, is 1 byte worth of useful information and 7 bytes of wasted space.

        - As it turns out, using some basic bit logic, it’s possible to compress all 8 bools into a single byte, eliminating the wasted space altogether. However, in order to do this, we’ll need to revamp the class when used with type bool, replacing the array of 8 bool with a variable that is a single byte in size. While we could create an entirely new class to do so, this has one major downside: we have to give it a different name. Then the programmer has to remember that Storage8<T> is meant for non-bool types, whereas Storage8Bool (or whatever we name the new class) is meant for bool. That’s needless complexity we’d rather avoid. Fortunately, C++ provides us a better method: class template specialization.


    2. Class template specialization allows us to specialize a template class for a particular data type (or data types, if there are multiple template parameters). In this case, we’re going to use class template specialization to write a customized version of Storage8<bool> that will take precedence over the generic Storage8<T> class.

        - Class template specializations are treated as completely independent classes, even though they are instantiated in the same way as the templated class. This means that we can change anything and everything about our specialization class, including the way it’s implemented and even the functions it makes public, just as if it were an independent class.

        - Just like all templates, the compiler must be able to see the full definition of a specialization to use it. Also, defining a class template specialization requires the non-specialized class to be defined first.

        - Example : 

            // First define our non-specialized class template
            template <typename T>
            class Storage8
            {
            private:
                T m_array[8];

            public:
                void set(int index, const T& value)
                {
                    m_array[index] = value;
                }

                const T& get(int index) const
                {
                    return m_array[index];
                }
            };

            // Now define our specialized class template
            template <> // the following is a template class with no templated parameters
            class Storage8<bool> // we're specializing Storage8 for bool
            {
            // What follows is just standard class implementation details

            private:
                std::uint8_t m_data{};

            public:
                // Don't worry about the details of the implementation of these functions
                void set(int index, bool value)
                {
                    // Figure out which bit we're setting/unsetting
                    // This will put a 1 in the bit we're interested in turning on/off
                    auto mask{ 1 << index };

                    if (value)  // If we're setting a bit
                        m_data |= mask;   // use bitwise-or to turn that bit on
                    else  // if we're turning a bit off
                        m_data &= ~mask;  // bitwise-and the inverse mask to turn that bit off
                }

                bool get(int index)
                {
                    // Figure out which bit we're getting
                    auto mask{ 1 << index };
                    // bitwise-and to get the value of the bit we're interested in
                    // Then implicit cast to boolean
                    return (m_data & mask);
                }
            };

            // Same example as before
            int main()
            {
                // Define a Storage8 for integers (instantiates Storage8<T>, where T = int)
                Storage8<int> intStorage;

                for (int count{ 0 }; count < 8; ++count)
                {
                    intStorage.set(count, count);
                }

                for (int count{ 0 }; count < 8; ++count)
                {
                    std::cout << intStorage.get(count) << '\n';
                }

                // Define a Storage8 for bool  (instantiates Storage8<bool> specialization)
                Storage8<bool> boolStorage;

                for (int count{ 0 }; count < 8; ++count)
                {
                    boolStorage.set(count, count & 3);
                }

                std::cout << std::boolalpha;

                for (int count{ 0 }; count < 8; ++count)
                {
                    std::cout << boolStorage.get(count) << '\n';
                }

                return 0;
            }

    3. 
*/
int main()
{
    return 0;
}