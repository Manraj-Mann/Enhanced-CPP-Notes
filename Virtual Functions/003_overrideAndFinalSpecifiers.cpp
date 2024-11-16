#include <iostream>
/* 
    Notes :  The override and final specifiers, and covariant return types

    1. To address some common challenges with inheritance, C++ has two inheritance-related identifiers: override and final. Note that these identifiers are not keywords -- they are normal words that have special meaning only when used in certain contexts. The C++ standard calls them “identifiers with special meaning”, but they are often referred to as “specifiers”.

    2. The override specifier : As we mentioned in the previous lesson, a derived class virtual function is only considered an override if its signature and return types match exactly. That can lead to inadvertent issues, where a function that was intended to be an override actually isn’t.

        - Because there is no performance penalty for using the override specifier and it helps ensure you’ve actually overridden the function you think you have, all virtual override functions should be tagged using the override specifier. Additionally, because the override specifier implies virtual, there’s no need to tag functions using the override specifier with the virtual keyword.

        - Use the virtual keyword on virtual functions in a base class. Use the override specifier (but not the virtual keyword) on override functions in derived classes. This includes virtual destructors.


    3. The final specifier : There may be cases where you don’t want someone to be able to override a virtual function, or inherit from a class. The final specifier can be used to tell the compiler to enforce this. If the user tries to override a function or inherit from a class that has been specified as final, the compiler will give a compile error.

    - In the case where we want to restrict the user from overriding a function, the final specifier is used in the same place the override specifier is, like so:

        class A
        {
        public:
            virtual std::string_view getName() const { return "A"; }
        };

        class B : public A
        {
        public:
            // note use of final specifier on following line -- that makes this function not able to be overridden in derived classes
            std::string_view getName() const override final { return "B"; } // okay, overrides A::getName()
        };

        class C : public B
        {
        public:
            std::string_view getName() const override { return "C"; } // compile error: overrides B::getName(), which is final
        };

    - In the case where we want to prevent inheriting from a class, the final specifier is applied after the class name:

        class A
        {
        public:
            virtual std::string_view getName() const { return "A"; }
        };

        class B final : public A // note use of final specifier here
        {
        public:
            std::string_view getName() const override { return "B"; }
        };

        class C : public B // compile error: cannot inherit from final class
        {
        public:
            std::string_view getName() const override { return "C"; }
        };

    4. Covariant return types:

        - There is one special case in which a derived class virtual function override can have a different return type than the base class and still be considered a matching override. If the return type of a virtual function is a pointer or a reference to some class, override functions can return a pointer or a reference to a derived class. These are called covariant return types. Here is an example:

            class Base
            {
            public:
                // This version of getThis() returns a pointer to a Base class
                virtual Base* getThis() { std::cout << "called Base::getThis()\n"; return this; }
                void printType() { std::cout << "returned a Base\n"; }
            };

            class Derived : public Base
            {
            public:
                // Normally override functions have to return objects of the same type as the base function
                // However, because Derived is derived from Base, it's okay to return Derived* instead of Base*
                Derived* getThis() override { std::cout << "called Derived::getThis()\n";  return this; }
                void printType() { std::cout << "returned a Derived\n"; }
            };

            int main()
            {
                Derived d{};
                Base* b{ &d };
                d.getThis()->printType(); // calls Derived::getThis(), returns a Derived*, calls Derived::printType
                b->getThis()->printType(); // calls Derived::getThis(), returns a Base*, calls Base::printType

                return 0;
            }

        - One interesting note about covariant return types: C++ can’t dynamically select types, so you’ll always get the type that matches the actual version of the function being called.Now the interesting case. We then call b->getThis(). Variable b is a Base pointer to a Derived object. Base::getThis() is a virtual function, so this calls Derived::getThis(). Although Derived::getThis() returns a Derived*, because Base version of the function returns a Base*, the returned Derived* is upcast to a Base*. Because Base::printType() is non-virtual, Base::printType() is called.

        - In other words, in the above example, you only get a Derived* if you call getThis() with an object that is typed as a Derived object in the first place. Note that if printType() were virtual instead of non-virtual, the result of b->getThis() (an object of type Base*) would have undergone virtual function resolution, and Derived::printType() would have been called.

        - Covariant return types are often used in cases where a virtual member function returns a pointer or reference to the class containing the member function (e.g. Base::getThis() returns a Base*, and Derived::getThis() returns a Derived*). However, this isn’t strictly necessary. Covariant return types can be used in any case where the return type of the override member function is derived from the return type of the base virtual member function.
                

*/

// class Base {
// public:
//     virtual ~Base() = default; // Virtual destructor
// };

// class Derived : public Base {
// public:
//     ~Derived() override { // Clear intent to override
//         // Destructor implementation
//     }
// };

class Base
{
    public:

        // This version of getThis() returns a pointer to a Base class
        virtual Base* getThis() { std::cout << "called Base::getThis()\n"; return this; }
        void printType() { std::cout << "returned a Base\n"; }
};

class Derived : public Base
{
    public:

        // Normally override functions have to return objects of the same type as the base function
        // However, because Derived is derived from Base, it's okay to return Derived* instead of Base*
        Derived* getThis() override { std::cout << "called Derived::getThis()\n";  return this; }
        void printType() { std::cout << "returned a Derived\n"; }
};


struct header
{
    int _header1{};

    void print()
    {
        std::cout<<"Header\n";
    }
};

struct data : public header
{
    int _body1{};

    void print()
    {
        header::print();
        std::cout<<"body\n";
    }
};

class class1
{
    public:

    virtual header * returnMessage()
    {
        return new header();
    }

};

class class2 : public class1
{
    public:

    data * returnMessage() override 
    {
        return new data();
    }

};

int main()
{
	Derived d{};
	Base* b{ &d };
	d.getThis()->printType(); // calls Derived::getThis(), returns a Derived*, calls Derived::printType
	b->getThis()->printType(); // calls Derived::getThis(), returns a Base*, calls Base::printType

    class2 c2;

    c2.returnMessage()->print();

    class1 * c1 {&c2};

    c1->returnMessage()->print();

	return 0;
}
