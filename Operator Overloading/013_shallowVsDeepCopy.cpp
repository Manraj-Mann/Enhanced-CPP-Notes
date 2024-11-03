#include <iostream>
/* 
    Notes :  
    
    1. Shallow copying :Because C++ does not know much about your class, the default copy constructor and default assignment operators it provides use a copying method known as a memberwise copy (also known as a shallow copy). This means that C++ copies each member of the class individually (using the assignment operator for overloaded operator=, and direct initialization for the copy constructor). When classes are simple (e.g. do not contain any dynamically allocated memory), this works very well.

        - Example : 

            class Fraction
            {
            private:
                int m_numerator { 0 };
                int m_denominator { 1 };

            public:
                // Default constructor
                Fraction(int numerator = 0, int denominator = 1)
                    : m_numerator{ numerator }
                    , m_denominator{ denominator }
                {
                    assert(denominator != 0);
                }

                // Possible implementation of implicit copy constructor
                Fraction(const Fraction& f)
                    : m_numerator{ f.m_numerator }
                    , m_denominator{ f.m_denominator }
                {
                }

                // Possible implementation of implicit assignment operator
                Fraction& operator= (const Fraction& fraction)
                {
                    // self-assignment guard
                    if (this == &fraction)
                        return *this;

                    // do the copy
                    m_numerator = fraction.m_numerator;
                    m_denominator = fraction.m_denominator;

                    // return the existing object so we can chain this operator
                    return *this;
                }

                friend std::ostream& operator<<(std::ostream& out, const Fraction& f1)
                {
                out << f1.m_numerator << '/' << f1.m_denominator;
                return out;
                }
            };

        - when designing classes that handle dynamically allocated memory, memberwise (shallow) copying can get us in a lot of trouble! This is because shallow copies of a pointer just copy the address of the pointer -- it does not allocate any memory or copy the contents being pointed to!

    2. Deep copying : One answer to this problem is to do a deep copy on any non-null pointers being copied. A deep copy allocates memory for the copy and then copies the actual value, so that the copy lives in distinct memory from the source. This way, the copy and source are distinct and will not affect each other in any way. Doing deep copies requires that we write our own copy constructors and overloaded assignment operators.

        - Example : 

            // assumes m_data is initialized
            void MyString::deepCopy(const MyString& source)
            {
                // first we need to deallocate any value that this string is holding!
                delete[] m_data;

                // because m_length is not a pointer, we can shallow copy it
                m_length = source.m_length;

                // m_data is a pointer, so we need to deep copy it if it is non-null
                if (source.m_data)
                {
                    // allocate memory for our copy
                    m_data = new char[m_length];

                    // do the copy
                    for (int i{ 0 }; i < m_length; ++i)
                        m_data[i] = source.m_data[i];
                }
                else
                    m_data = nullptr;
            }

            // Copy constructor
            MyString::MyString(const MyString& source)
            {
                deepCopy(source);
            }

        - Now let’s do the overloaded assignment operator. The overloaded assignment operator is slightly trickier:

            // Assignment operator
            MyString& MyString::operator=(const MyString& source)
            {
                // check for self-assignment
                if (this != &source)
                {
                    // now do the deep copy
                    deepCopy(source);
                }

                return *this;
            }

        - When the overloaded assignment operator is called, the item being assigned to may already contain a previous value, which we need to make sure we clean up before we assign memory for new values. For non-dynamically allocated variables (which are a fixed size), we don’t have to bother because the new value just overwrites the old one. However, for dynamically allocated variables, we need to explicitly deallocate any old memory before we allocate any new memory. If we don’t, the code will not crash, but we will have a memory leak that will eat away our free memory every time we do an assignment!

    3. The rule of three : Remember the rule of three? If a class requires a user-defined destructor, copy constructor, or copy assignment operator, then it probably requires all three. This is why. If we’re user-defining any of these functions, it’s probably because we’re dealing with dynamic memory allocation. We need the copy constructor and copy assignment to handle deep copies, and the destructor to deallocate memory.

    4. A better solution : Classes in the standard library that deal with dynamic memory, such as std::string and std::vector, handle all of their memory management, and have overloaded copy constructors and assignment operators that do proper deep copying. So instead of doing your own memory management, you can just initialize or assign them like normal fundamental variables! That makes these classes simpler to use, less error-prone, and you don’t have to spend time writing your own overloaded functions!

    5. Summary : The default copy constructor and default assignment operators do shallow copies, which is fine for classes that contain no dynamically allocated variables. Classes with dynamically allocated variables need to have a copy constructor and assignment operator that do a deep copy. Favor using classes in the standard library over doing your own memory management.

*/
int main()
{
    return 0;
}