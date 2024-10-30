#include <iostream>
/* 
    Notes :  
    
    1. Friend classes : A friend class is a class that can access the private and protected members of another class.

        - Here is an example:

            class Storage
            {
            private:
                int m_nValue {};
                double m_dValue {};
            public:
                Storage(int nValue, double dValue)
                : m_nValue { nValue }, m_dValue { dValue }
                { }

                // Make the Display class a friend of Storage
                friend class Display;
            };

            class Display
            {
            private:
                bool m_displayIntFirst {};

            public:
                Display(bool displayIntFirst)
                    : m_displayIntFirst { displayIntFirst }
                {
                }

                // Because Display is a friend of Storage, Display members can access the private members of Storage
                void displayStorage(const Storage& storage)
                {
                    if (m_displayIntFirst)
                        std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                    else // display double first
                        std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
                }

                void setDisplayIntFirst(bool b)
                {
                    m_displayIntFirst = b;
                }
            };
        
        - First, even though Display is a friend of Storage, Display has no access to the *this pointer of Storage objects (because *this is actually a function parameter).

        - Second, friendship is not reciprocal. Just because Display is a friend of Storage does not mean Storage is also a friend of Display. If you want two classes to be friends of each other, both must declare the other as a friend.

        - Class friendship is also not transitive. If class A is a friend of B, and B is a friend of C, that does not mean A is a friend of C.

        - Nor is friendship inherited. If class A makes B a friend, classes derived from B are not friends of A.

    2. Friend member functions : Instead of making an entire class a friend, you can make a single member function a friend. This is done similarly to making a non-member function a friend, except the name of the member function is used instead.

    - However, in actuality, this can be a little trickier than expected. Let’s convert the previous example to make Display::displayStorage a friend member function. You might try something like this:

        class Display; // forward declaration for class Display

        class Storage
        {
        private:
            int m_nValue {};
            double m_dValue {};
        public:
            Storage(int nValue, double dValue)
                : m_nValue { nValue }, m_dValue { dValue }
            {
            }

            // Make the Display::displayStorage member function a friend of the Storage class
            friend void Display::displayStorage(const Storage& storage); // error: Storage hasn't seen the full definition of class Display
        };

        class Display
        {
        private:
            bool m_displayIntFirst {};

        public:
            Display(bool displayIntFirst)
                : m_displayIntFirst { displayIntFirst }
            {
            }

            void displayStorage(const Storage& storage)
            {
                if (m_displayIntFirst)
                    std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                else // display double first
                    std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
            }
        };

    - However, it turns out this won’t work. In order to make a single member function a friend, the compiler has to have seen the full definition for the class of the friend member function (not just a forward declaration). Since class Storage hasn’t seen the full definition for class Display yet, the compiler will error at the point where we try to make the member function a friend.

    - Fortunately, this is easily resolved by moving the definition of class Display before the definition of class Storage (either in the same file, or by moving the definition of Display to a header file and #including it before Storage is defined).

        class Display
        {
        private:
            bool m_displayIntFirst {};

        public:
            Display(bool displayIntFirst)
                : m_displayIntFirst { displayIntFirst }
            {
            }

            void displayStorage(const Storage& storage) // compile error: compiler doesn't know what a Storage is
            {
                if (m_displayIntFirst)
                    std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                else // display double first
                    std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
            }
        };

        class Storage
        {
        private:
            int m_nValue {};
            double m_dValue {};
        public:
            Storage(int nValue, double dValue)
                : m_nValue { nValue }, m_dValue { dValue }
            {
            }

            // Make the Display::displayStorage member function a friend of the Storage class
            friend void Display::displayStorage(const Storage& storage); // okay now
        };

    - However, we now have another problem. Because member function Display::displayStorage() uses Storage as a reference parameter, and we just moved the definition of Storage below the definition of Display, the compiler will complain it doesn’t know what a Storage is. We can’t fix this one by rearranging the definition order, because then we’ll undo our previous fix.

    3. Fortunately, this is also fixable in a couple of simple steps. 
    
        - First, we can add class Storage as a forward declaration so the compiler will be okay with a reference to Storage before it has seen the full definition of the class.

        - Second, we can move the definition of Display::displayStorage() out of the class, after the full definition of Storage class.

        Example : 

            class Storage; // forward declaration for class Storage

            class Display
            {
            private:
                bool m_displayIntFirst {};

            public:
                Display(bool displayIntFirst)
                    : m_displayIntFirst { displayIntFirst }
                {
                }

                void displayStorage(const Storage& storage); // forward declaration for Storage needed for reference here
            };

            class Storage // full definition of Storage class
            {
            private:
                int m_nValue {};
                double m_dValue {};
            public:
                Storage(int nValue, double dValue)
                    : m_nValue { nValue }, m_dValue { dValue }
                {
                }

                // Make the Display::displayStorage member function a friend of the Storage class
                // Requires seeing the full definition of class Display (as displayStorage is a member)
                friend void Display::displayStorage(const Storage& storage);
            };

            // Now we can define Display::displayStorage
            // Requires seeing the full definition of class Storage (as we access Storage members)
            void Display::displayStorage(const Storage& storage)
            {
                if (m_displayIntFirst)
                    std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                else // display double first
                    std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
            }

        - Now everything will compile properly: the forward declaration of class Storage is enough to satisfy the declaration of Display::displayStorage() inside the Display class. The full definition of Display satisfies declaring Display::displayStorage() as a friend of Storage. And the full definition of class Storage is enough to satisfy the definition of member function Display::displayStorage().

    4. If this seems like a pain -- it is. Fortunately, this dance is only necessary because we’re trying to do everything in a single file. A better solution is to put each class definition in a separate header file, with the member function definitions in corresponding .cpp files. That way, all of the class definitions would be available in the .cpp files, and no rearranging of classes or functions is necessary!


*/
int main()
{
    return 0;
}