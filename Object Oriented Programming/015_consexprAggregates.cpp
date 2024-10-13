#include <iostream>
/* 
    Notes :  Constexpr aggregates and classes
    
    1. Constexpr member functions - Just like non-member functions, member functions can be made constexpr via use of the constexpr keyword. Constexpr member functions can be evaluated at either compile-time or runtime.

        struct Pair
        {
            int m_x {};
            int m_y {};

            constexpr int greater() const // can evaluate at either compile-time or runtime
            {
                return (m_x > m_y  ? m_x : m_y);
            }
        };

        int main()
        {
            Pair p { 5, 6 };
            std::cout << p.greater() << '\n'; // okay: p.greater() evaluates at runtime

            constexpr int g { p.greater() };  // compile error: p not constexpr
            std::cout << g << '\n';

            return 0;
        }

        - In this example, we’ve made greater() a constexpr function, so the compiler can evaluate it at either runtime or compile-time.

        - In this example, we’ve made greater() a constexpr function, so the compiler can evaluate it at either runtime or compile-time. When we call p.greater() in runtime expression std::cout << p.greater(), it evaluates at runtime. However, when p.greater() is used to initialize constexpr variable g, we get a compiler error. Although greater() is now constexpr, p is still not constexpr, therefore p.greater() is not a constant expression.

    2. Constexpr aggregates - Okay, so if we need p to be constexpr, let’s just make it constexpr:

        struct Pair // Pair is an aggregate
        {
            int m_x {};
            int m_y {};

            constexpr int greater() const
            {
                return (m_x > m_y  ? m_x : m_y);
            }
        };

        int main()
        {
            constexpr Pair p { 5, 6 };        // now constexpr
            std::cout << p.greater() << '\n'; // p.greater() evaluates at runtime or compile-time

            constexpr int g { p.greater() };  // p.greater() must evaluate at compile-time
            std::cout << g << '\n';

            return 0;
        }

        - Since Pair is an aggregate, and aggregates implicitly support constexpr, we’re done. This works! Since p is a constexpr type, and greater() is a constexpr member function, p.greater() is a constant expression and can be used in places where only constant expressions are allowed.

    3. Constexpr class objects and constexpr constructors : 

        - Now let’s make our Pair a non-aggregate:

            class Pair // Pair is no longer an aggregate
            {
            private:
                int m_x {};
                int m_y {};

            public:
                Pair(int x, int y): m_x { x }, m_y { y } {}

                constexpr int greater() const
                {
                    return (m_x > m_y  ? m_x : m_y);
                }
            };

            int main()
            {
                constexpr Pair p { 5, 6 };       // compile error: p is not a literal type
                std::cout << p.greater() << '\n';

                constexpr int g { p.greater() };
                std::cout << g << '\n';

                return 0;
            }

        - This example is almost identical to the prior one, except Pair is no longer an aggregate (due to having private data members and a constructor). When we compile this program, we get a compiler error about Pair not being a “literal type”. Say what? 
            
        - In C++, a literal type is any type for which it might be possible to create an object within a constant expression. Put another way, an object can’t be constexpr unless the type qualifies as a literal type. And our non-aggregate Pair does not qualify.

        - A literal and a literal type are distinct (but related) things. A literal is a constexpr value that is inserted into the source code. A literal type is a type that can be used as the type of a constexpr value. A literal always has a literal type. However, a value or object with a literal type need not be a literal.

        - And now we see why our Pair isn’t a literal type. When a class object is instantiated, the compiler will call the constructor function to initialize the object. And the constructor function in our Pair class is not constexpr, so it can’t be invoked at compile-time. Therefore, Pair objects cannot be constexpr. The fix for this is simple: we just make our constructor constexpr as well:

            class Pair
            {
            private:
                int m_x {};
                int m_y {};

            public:
                constexpr Pair(int x, int y): m_x { x }, m_y { y } {} // now constexpr

                constexpr int greater() const
                {
                    return (m_x > m_y  ? m_x : m_y);
                }
            };

            int main()
            {
                constexpr Pair p { 5, 6 };
                std::cout << p.greater() << '\n';

                constexpr int g { p.greater() };
                std::cout << g << '\n';

                return 0;
            }

        - Best practice : If you want your class to be able to be evaluated at compile-time, make your member functions and constructor constexpr.

        - Tip : Constexpr is part of the interface of the class, and removing it later will break callers who are calling the function in a constant context.

    4. Constexpr members may be needed with non-constexpr/non-const objects : 

        - In the above example, since the initializer of constexpr variable g must be a constant expression, it’s clear that p.greater() must be a constant expression, and therefore p, the Pair constructor, and greater() must all be constexpr. However, if we replace p.greater() with a constexpr function, things get a little less obvious:

            class Pair
            {
            private:
                int m_x {};
                int m_y {};

            public:
                constexpr Pair(int x, int y): m_x { x }, m_y { y } {}

                constexpr int greater() const
                {
                    return (m_x > m_y  ? m_x : m_y);
                }
            };

            constexpr int init()
            {
                Pair p { 5, 6 };    // requires constructor to be constexpr when evaluated at compile-time
                return p.greater(); // requires greater() to be constexpr when evaluated at compile-time
            }

            int main()
            {
                constexpr int g { init() }; // init() evaluated in runtime context
                std::cout << g << '\n';

                return 0;
            }

        - Remember that a constexpr function can evaluate at either runtime or compile-time. And when a constexpr function evaluates at compile-time, it can only call functions capable of evaluating at compile-time. In the case of a class type, that means constexpr member functions.

        - Since g is constexpr, init() must be evaluated at compile-time. Within the init() function, we define p as non-constexpr/non-const (because we can, not because we should). Even though p is not defined as constexpr, p still needs to be created at compile-time, and therefore requires a constexpr Pair constructor. Similarly, in order for p.greater() to evaluate at compile-time, greater() must be a constexpr member function. If either the Pair constructor or greater() were not constexpr, the compiler would error.

        - Key insight : When a constexpr function is evaluating in a compile-time context, only constexpr functions can be called.

    5. Constexpr member functions may be const or non-const : 

    In C++11, non-static constexpr member functions are implicitly const (except constructors). However, as of C++14, constexpr member functions are no longer implicitly const. This means a constexpr non-const member function can change data members of the class, so long as the implicit object isn’t const.

    Here’s a contrived example of this:

        class Pair
        {
        private:
            int m_x {};
            int m_y {};

        public:
            constexpr Pair(int x, int y): m_x { x }, m_y { y } {}

            constexpr int greater() const // constexpr and const
            {
                return (m_x > m_y  ? m_x : m_y);
            }

            constexpr void reset() // constexpr but non-const
            {
                m_x = m_y = 0; // non-const member function can change members
            }

            constexpr const int& getX() const { return m_x; }
        };

        // This function is constexpr
        constexpr Pair zero()
        {
            Pair p { 1, 2 }; // p is non-const
            p.reset();       // okay to call non-const member function on non-const object
            return p;
        }

        int main()
        {
            Pair p1 { 3, 4 };
            p1.reset();                     // okay to call non-const member function on non-const object
            std::cout << p1.getX() << '\n'; // prints 0

            Pair p2 { zero() };             // zero() will be evaluated at runtime
            p2.reset();                     // okay to call non-const member function on non-const object
            std::cout << p2.getX() << '\n'; // prints 0

            constexpr Pair p3 { zero() };   // zero() will be evaluated at compile-time
        //    p3.reset();                   // Compile error: can't call non-const member function on const object
            std::cout << p3.getX() << '\n'; // prints 0

            return 0;
        }

        - As we work through this example, remember: 

            = A non-const member function can modify members of non-const objects.
            
            = A constexpr member function can be called in either runtime contexts or compile-time contexts.

        - These two things work independently.

            In the case of p1, p1 is non-const. Therefore, we are allowed to call non-const member function p1.reset() to modify p1. The fact that reset() is constexpr doesn’t matter here because nothing we’re doing requires compile-time evaluation.

            The p2 case is similar. In this case, the initializer to p2 is a function call to zero(). Even though zero() is a constexpr function, in this case it is invoked in a runtime context, and acts just like a normal function. Within zero(), we instantiate non-const p, call non-const member function p.reset() on it, and then return p. The returned Pair is used as the initializer for p2. The fact that zero() and reset() are constexpr don’t matter in this case, because nothing we’re doing requires compile-time evaluation.

            The p3 case is the interesting one. Because p3 is constexpr, it must have a constant expression initializer. Therefore, this call to zero() must evaluate at compile-time. And because we’re evaluating in a compile-time context, we can only call constexpr functions. Inside zero(), p is non-const (which is allowed, even though we’re evaluating at compile-time). However, because we’re in a compile-time context, the constructor used to create p must be constexpr. And just like the p2 case, we’re allowed to call non-const member function p.reset() on non-const object p. But because we’re in a compile-time context, the reset() member function must be constexpr. The function then returns p, which is used to initialize p3.

    6. Constexpr functions that return const references (or pointers) : Normally you won’t see constexpr and const used right next to each other, but one case where this does happen is when you have a constexpr member function that returns a const reference (or pointer-to-const).

    In our Pair class above, getX() is a constexpr member function that returns a const reference:

        constexpr const int& getX() const { return m_x; }
    
    That’s a lot of const-ing!

    The constexpr indicates that the member function can be evaluated at compile-time. The const int& is the return type of the function. The rightmost const means the member-function itself is const so it can be called on const objects.

*/

class Pair // Pair is no longer an aggregate
{
private:
    int m_x {};
    int m_y {};

public:
    Pair(int x, int y): m_x { x }, m_y { y } {}

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    constexpr Pair p { 5, 6 };       // compile error: p is not a literal type
    std::cout << p.greater() << '\n';

    constexpr int g { p.greater() };
    std::cout << g << '\n';

    return 0;
}
