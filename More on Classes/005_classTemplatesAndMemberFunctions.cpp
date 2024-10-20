#include <iostream>
/* 
    Notes :  
    
    1. Type template parameters in member functions : Type template parameters defined as part of a class template parameter declaration can be used both as the type of data members and as the type of member function parameters.

        template <typename T>
        class Pair
        {
        private:
            T m_first{};
            T m_second{};

        public:
            // When we define a member function inside the class definition,
            // the template parameter declaration belonging to the class applies
            Pair(const T& first, const T& second)
                : m_first{ first }
                , m_second{ second }
            {
            }

            bool isEqual(const Pair<T>& pair);
        };

        // When we define a member function outside the class definition,
        // we need to resupply a template parameter declaration
        template <typename T>
        bool Pair<T>::isEqual(const Pair<T>& pair)
        {
            return m_first == pair.m_first && m_second == pair.m_second;
        }

        int main()
        {
            Pair p1{ 5, 6 }; // uses CTAD to infer type Pair<int>
            std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
            std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';

            return 0;
        }

        => let’s look more closely at the case where we define a member function for a class template outside of the class template definition:

            template <typename T>
            bool Pair<T>::isEqual(const Pair<T>& pair)
            {
                return m_first == pair.m_first && m_second == pair.m_second;
            }
        
        => Since this member function definition is separate from the class template definition, we need to resupply a template parameter declaration (template <typename T>) so the compiler knows what T is.

        Also, when we define a member function outside of the class, we need to qualify the member function name with the fully templated name of the class template (Pair<T>::isEqual, not Pair::isEqual).

    2. Injected class names :  In a prior lesson, we noted that the name of a constructor must match the name of the class. But in our class template for Pair<T> above, we named our constructor Pair, not Pair<T>. Somehow this still works, even though the names don’t match.

       =>  Within the scope of a class, the unqualified name of the class is called an injected class name. In a class template, the injected class name serves as shorthand for the fully templated name.

        -> Because Pair is the injected class name of Pair<T>, within the scope of our Pair<T> class template, any use of Pair will be treated as if we had written Pair<T> instead. Therefore, although we named the constructor Pair, the compiler treats it as if we had written Pair<T> instead. The names now match! This means that we can also define our isEqual() member function like this:

            template <typename T>
            bool Pair<T>::isEqual(const Pair& pair) // note the parameter has type Pair, not Pair<T>
            {
                return m_first == pair.m_first && m_second == pair.m_second;
            }

        => Because this is a definition for a member function of Pair<T>, we’re in the scope of the Pair<T> class template. Therefore, any use of Pair is shorthand for Pair<T>!

    3. Where to define member functions for class templates outside the class : We typically want to define both a class and its member function templates in the same location.

        1. When a member function template is defined inside the class definition, the template member function definition is part of the class definition, so anywhere the class definition can be seen, the template member function definition can also be seen. This makes things easy (at the cost of cluttering our class definition).

        2. When a member function template is defined outside the class definition, it should generally be defined immediately below the class definition. That way, anywhere the class definition can be seen, the member function template definitions immediately below the class definition will also be seen.

        => In the typical case where a class is defined in a header file, this means any member function templates defined outside the class should also be defined in the same header file, below the class definition.

*/
#include <ios>       // for std::boolalpha

template <typename T>
class Pair
{
private:
    T m_first{};
    T m_second{};

public:
    // When we define a member function inside the class definition,
    // the template parameter declaration belonging to the class applies
    Pair(const T& first, const T& second)
        : m_first{ first }
        , m_second{ second }
    {
    }

    bool isEqual(const Pair<T>& pair);
};

// When we define a member function outside the class definition,
// we need to resupply a template parameter declaration
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair)
{
    return m_first == pair.m_first && m_second == pair.m_second;
}

int main()
{
    Pair p1{ 5, 6 }; // uses CTAD to infer type Pair<int>
    std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
    std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';

    return 0;
}