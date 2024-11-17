#include <iostream>
/* 
    Notes :  
    
    1. We took a look at a simple templated Storage class, along with a specialization for type double:

        template <typename T>
        class Storage
        {
        private:
            T m_value {};
        public:
            Storage(T value)
            : m_value { value }
            {
            }

            void print()
            {
                std::cout << m_value << '\n';
            }
        };

        template<>
        void Storage<double>::print() // fully specialized for type double
        {
            std::cout << std::scientific << m_value << '\n';
        }

        int main()
        {
            // Define some storage units
            Storage i { 5 };
            Storage d { 6.7 }; // will cause Storage<double> to be implicitly instantiated

            // Print out some values
            i.print(); // calls Storage<int>::print (instantiated from Storage<T>)
            d.print(); // calls Storage<double>::print (called from explicit specialization of Storage<double>::print())
        }

        - However, as simple as this class is, it has a hidden flaw: it compiles but malfunctions when T is a pointer type. For example:

            int main()
            {
                double d { 1.2 };
                double *ptr { &d };

                Storage s { ptr };
                s.print();

                return 0;
            }

            On the authors machine, this produced the result:

            0x7ffe164e0f50

        - What happened? Because ptr is a double*, s has type Storage<double*>, which means m_value has type double*. When the constructor is invoked, m_value receives a copy of the address that ptr is holding, and it is this address that is printed when the print() member function is called.

    2. One option would be to add a full specialization for type double*:

        template<>
        void Storage<double*>::print() // fully specialized for type double*
        {
            if (m_value)
                std::cout << std::scientific << *m_value << '\n';
        }

        template<>
        void Storage<double>::print() // fully specialized for type double (for comparison, not used)
        {
            std::cout << std::scientific << m_value << '\n';
        }

        - But this only solves the problem when T is of type double*. What about when T is int*, or char*, or any other pointer type?

        - We really don’t want to have to create a full specialization for every pointer type. And in fact, it’s not even possible, because the user can always pass in a pointer to a program-defined type.

    3. Partial template specialization for pointers : You might think to to try creating a template function overloaded on type T*:

        // doesn't work
        template<typename T>
        void Storage<T*>::print()
        {
            if (m_value)
                std::cout << std::scientific << *m_value << '\n';
        }
        
        - Such a function is a partially specialized template function because it’s restricting what type T can be (to a pointer type), but T is still a type template parameter.

        - Unfortunately, this doesn’t work for a simple reason: as of the time of writing (C++23) functions cannot be partially specialized. As we noted in lesson 26.5 -- Partial template specialization, only classes can be partially specialized.

        -   So let’s partially specialize the Storage class instead:

            template <typename T>
            class Storage // This is our primary template class (same as previous)
            {
            private:
                T m_value {};
            public:
                Storage(T value)
                : m_value { value }
                {
                }

                void print()
                {
                    std::cout << m_value << '\n';
                }
            };

            template <typename T> // we still have a type template parameter
            class Storage<T*> // This is partially specialized for T*
            {
            private:
                T* m_value {};
            public:
                Storage(T* value)
                : m_value { value }
                {
                }

                void print();
            };

            template <typename T>
            void Storage<T*>::print() // This is a non-specialized function of partially specialized class Storage<T*>
            {
                if (m_value)
                    std::cout << std::scientific << *m_value << '\n';
            }

            int main()
            {
                double d { 1.2 };
                double *ptr { &d };

                Storage s { ptr }; // instantiates Storage<double*> from partially specialized class
                s.print(); // calls Storage<double*>::print()

                return 0;
            }

    4. Ownership and lifetime issues : 

        - The above partially specialized class Storage<T*> has another potential issue. Because m_value is a T*, it is a pointer to the object that is passed in. If that object is then destroyed, our Storage<T*> will be left dangling.

        - The core problem is that our implementation of Storage<T> has copy semantics (meaning it makes a copy of its initializer) but Storage<T*> has reference semantics (meaning it’s a reference to its initializer). This inconsistency is a recipe for bugs.
*/

template <typename T>
class Storage // This is our primary template class (same as previous)
{
private:
    T m_value {};
public:
    Storage(T value)
      : m_value { value }
    {
    }

    void print()
    {
        std::cout << m_value << '\n';
    }
};

template <typename T> // we still have a type template parameter
class Storage<T*> // This is partially specialized for T*
{
private:
    T* m_value {};
public:
    Storage(T* value)
      : m_value { value }
    {
    }

    void print();
};

template <typename T>
void Storage<T*>::print() // This is a non-specialized function of partially specialized class Storage<T*>
{
    if (m_value)
        std::cout << std::scientific << *m_value << '\n';
}

int main()
{
    double d { 1.2 };
    double *ptr { &d };

    Storage s { ptr }; // instantiates Storage<double*> from partially specialized class
    s.print(); // calls Storage<double*>::print()

    return 0;
}
