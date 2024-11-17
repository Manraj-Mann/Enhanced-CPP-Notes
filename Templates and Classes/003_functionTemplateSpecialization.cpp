#include <iostream>
/* 
    Notes :  
    
    1. When instantiating a function template for a given type, the compiler stencils out a copy of the templated function and replaces the template type parameters with the actual types used in the variable declaration. This means a particular function will have the same implementation details for each instanced type (just using different types). While most of the time this is exactly what you want, occasionally there are cases where it is useful to implement a templated function slightly differently for a specific data type.

    2. Using a non-template function : 
    
        - Consider the following example:

            template <typename T>
            void print(const T& t)
            {
                std::cout << t << '\n';
            }

            int main()
            {
                print(5);
                print(6.7);

                return 0;
            }
        
        - Now, let’s say we want double values (and only double values) to output in scientific notation. One way to get different behavior for a given type is to define a non-template function:

            template <typename T>
            void print(const T& t)
            {
                std::cout << t << '\n';
            }

            void print(double d)
            {
                std::cout << std::scientific << d << '\n';
            }

        - Generally, prefer to define a non-template function if that option is available.

    3. Function template specialization - Another way to achieve a similar result is to use explicit template specialization. Explicit template specialization (often shortened to template specialization) is a feature that allows us to explicitly define different implementations of a template for specific types or values. When all of the template parameters are specialized, it is called a full specialization. When only some of the template parameters are specialized, it is called a partial specialization.

        // Here's our primary template (must come first)
        template <typename T>
        void print(const T& t)
        {
            std::cout << t << '\n';
        }

        // A full specialization of primary template print<T> for type double
        // Full specializations are not implicitly inline, so make this inline if put in header file
        template<>                          // template parameter declaration containing no template parameters
        void print<double>(const double& d) // specialized for type double
        {
            std::cout << std::scientific << d << '\n';
        }

        - In order to specialize a template, the compiler first must have seen a declaration for the primary template. The primary template in the example above is print<T>(const T&).

        - Note that if a matching non-template function and a matching template function specialization both exist, the non-template function will take precedence. 
        
        - Also, full specializations are not implicitly inline, so if you define one in a header file, make sure you inline it to avoid ODR violations.

        - Just like normal functions, function template specializations can be deleted (using = delete) if you want any function calls that resolve to the specialization to produce a compilation error.

    4. Function template specialization for member functions?

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

        int main()
        {
            // Define some storage units
            Storage i { 5 };
            Storage d { 6.7 };

            // Print out some values
            i.print();
            d.print();
        }

        - Let’s say we again want to create a version of the print() function that prints doubles in scientific notation. However, this time print() is a member function, so we can’t define a non-member function. So how might we do this?

        - Although it may seem like we need to use function template specialization here, that’s the wrong tool. Note that i.print() calls Storage<int>::print() and d.print() calls Storage<double>::print(). Therefore, if we want to change the behavior of this function when T is a double, we need to specialize Storage<double>::print(), which is a class template specialization, not a function template specialization!

    5. Specializing member functions : 

        - C++ does not require us to explicitly specialize Storage<double> to explicitly specialize Storage<double>::print(). Instead, we can let the compiler implicitly specialize Storage<double> from Storage<T>, and provide an explicit specialization of just Storage<double>::print()! 
        
        - Here’s what that looks like:

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

            // This is a specialized member function definition
            // Explicit function specializations are not implicitly inline, so make this inline if put in header file
            template<>
            void Storage<double>::print()
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

    6. Where to define class template specializations : 

        - In order to use a specialization, the compiler must be able to see the full definition of both the non-specialized class and the specialized class. If the compiler can only see the definition of the non-specialized class, it will use that instead of the specialization.

        - If a specialization is only required in a single translation unit, it can be defined in the source file for that translation unit. Because other translation units will not be able to see the definition of the specialization, they will continue to use the non-specialized version.

        - Be wary of putting a specialization in its own separate header file, with the intent of including the specialization’s header in any translation unit where the specialization is desired. It’s a bad idea to design code that transparently changes behavior based on the presence or absence of a header file. For example, if you intend to use the specialization but forget to include the header of the specialization, you may end up using the non-specialized version instead. If you intend to use the non-specialization, you may end up using the specialization anyway if some other header includes the specialization as a transitive include.


*/
int main()
{
    return 0;
}