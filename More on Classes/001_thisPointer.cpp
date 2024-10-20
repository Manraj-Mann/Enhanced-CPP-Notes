#include <iostream>
/* 
    Notes :  
    
    1. this pointer : Inside every member function, the keyword this is a const pointer that holds the address of the current implicit object.

    2. How is this set? 

        1. When we call simple.setID(2), the compiler actually calls Simple::setID(&simple, 2), and simple is passed by address to the function.
        2. The function has a hidden parameter named this which receives the address of simple.
        3. Member variables inside setID() are prefixed with this->, which points to simple. So when the compiler evaluates this->m_id, it’s actually resolving to simple.m_id.
        
        The good news is that all of this happens automatically, and it doesn’t really matter whether you remember how it works or not. All you need to remember is that all non-static member functions have a this pointer that refers to the object the function was called on.

    3. this always points to the object being operated on : New programmers are sometimes confused about how many this pointers exist. Each member function has a single this pointer parameter that points to the implicit object. Consider:

        int main()
        {
            Simple a{1}; // this = &a inside the Simple constructor
            Simple b{2}; // this = &b inside the Simple constructor
            a.setID(3); // this = &a inside member function setID()
            b.setID(4); // this = &b inside member function setID()

            return 0;
        }

    4. Explicitly referencing this : Most of the time, you won’t need to explicitly reference the this pointer. However, there are a few occasions where doing so can be useful:

        First, if you have a member function that has a parameter with the same name as a data member, you can disambiguate them by using this:

        struct Something
        {
            int data{}; // not using m_ prefix because this is a struct

            void setData(int data)
            {
                this->data = data; // this->data is the member, data is the local parameter
            }
        };

        This Something class has a member named data. The function parameter of setData() is also named data. Within the setData() function, data refers to the function parameter (because the function parameter shadows the data member), so if we want to reference the data member, we use this->data.

        Some developers prefer to explicitly add this-> to all class members to make it clear that they are referencing a member. We recommend that you avoid doing so, as it tends to make your code less readable for little benefit. Using the “m_” prefix is a more concise way to differentiate private member variables from non-member (local) variables.

    5. Returning *this : Second, it can sometimes be useful to have a member function return the implicit object as a return value. The primary reason to do this is to allow member functions to be “chained” together, so several member functions can be called on the same object in a single expression! This is called function chaining (or method chaining).

        - Consider this common example where you’re outputting several bits of text using std::cout:

            std::cout << "Hello, " << userName;

        - The compiler evaluates the above snippet like this:

            (std::cout << "Hello, ") << userName;

        - First, operator<< uses std::cout and the string literal "Hello, " to print "Hello, " to the console. However, since this is part of an expression, operator<< also needs to return a value (or void). If operator<< returned void, you’d end up with this as the partially evaluated expression:

            void{} << userName;
        
        - which clearly doesn’t make any sense (and the compiler would throw an error). Instead, operator<< returns the stream object that was passed in, which in this case is std::cout. That way, after the first operator<< has been evaluated, we get:

            (std::cout) << userName;
        
        which then prints the user’s name.

        - This way, we only need to specify std::cout once, and then we can chain as many pieces of text together using operator<< as we want. Each call to operator<< returns std::cout so the next call to operator<< uses std::cout as the left operand.

        => We can implement this kind of behavior in our member functions too. Consider the following class:

            class Calc
            {
            private:
                int m_value{};

            public:

                void add(int value) { m_value += value; }
                void sub(int value) { m_value -= value; }
                void mult(int value) { m_value *= value; }

                int getValue() const { return m_value; }
            };

            int main()
            {
                Calc calc{};
                calc.add(5); // returns void
                calc.sub(3); // returns void
                calc.mult(4); // returns void

                std::cout << calc.getValue() << '\n';

                return 0;
            }

        => However, if we make each function return *this by reference, we can chain the calls together. Here is the new version of Calc with “chainable” functions:

            class Calc
            {
            private:
                int m_value{};

            public:
                Calc& add(int value) { m_value += value; return *this; }
                Calc& sub(int value) { m_value -= value; return *this; }
                Calc& mult(int value) { m_value *= value; return *this; }

                int getValue() const { return m_value; }
            };

            int main()
            {
                Calc calc{};
                calc.add(5).sub(3).mult(4); // method chaining

                std::cout << calc.getValue() << '\n';

                return 0;
            }

            - We have effectively condensed three lines into one expression! Let’s take a closer look at how this works.This is probably the most common explicit use of this, and is one you should consider whenever it makes sense to have chainable member functions. Because this always points to the implicit object, we don’t need to check whether it is a null pointer before dereferencing it.

    6. Resetting a class back to default state : If your class has a default constructor, you may be interested in providing a way to return an existing object back to its default state.

        => The best way to reset a class back to a default state is to create a reset() member function, have that function create a new object (using the default constructor), and then assign that new object to the current implicit object, like this:

        void reset()
        {
            *this = {}; // value initialize a new object and overwrite the implicit object
        }


    7. this and const objects : 

        => For non-const member functions, this is a const pointer to a non-const value (meaning this cannot be pointed at something else, but the object pointing to may be modified). With const member functions, this is a const pointer to a const value (meaning the pointer cannot be pointed at something else, nor may the object being pointed to be modified).
        

    8. Why this a pointer and not a reference : Since the this pointer always points to the implicit object (and can never be a null pointer unless we’ve done something to cause undefined behavior), so you may be wondering why this is a pointer instead of a reference. The answer is simple: when this was added to C++, references didn’t exist yet.

    If this were added to the C++ language today, it would undoubtedly be a reference instead of a pointer. In other more modern C++-like languages, such as Java and C#, this is implemented as a reference.

*/
int main()
{
    return 0;
}