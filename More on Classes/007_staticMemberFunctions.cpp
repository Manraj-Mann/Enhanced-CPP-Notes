#include <iostream>
/* 
    Notes :  
    
    1. Static member functions : 

        => Because static member functions are not associated with a particular object, they can be called directly by using the class name and the scope resolution operator (e.g. Something::getValue()). Like static member variables, they can also be called through objects of the class type, though this is not recommended.

            class Something
            {
            private:
                static inline int s_value { 1 };

            public:
                static int getValue() { return s_value; } // static member function
            };

    2. Static member functions have no this pointer : 

        => Static member functions have two interesting quirks worth noting. First, because static member functions are not attached to an object, they have no this pointer! This makes sense when you think about it -- the this pointer always points to the object that the member function is working on. Static member functions do not work on an object, so the this pointer is not needed.

        => Second, static member functions can directly access other static members (variables or functions), but not non-static members. This is because non-static members must belong to a class object, and static member functions have no class object to work with!

    3. Static members defined outside the class definition : 

        Static member functions can also be defined outside of the class declaration. This works the same way as for normal member functions.

        class IDGenerator
        {
        private:
            static inline int s_nextID { 1 };

        public:
            static int getNextID(); // Here's the declaration for a static function
        };

        // Here's the definition of the static function outside of the class.  Note we don't use the static keyword here.
        int IDGenerator::getNextID() { return s_nextID++; }

        => Member functions defined inside the class definition are implicitly inline. Member functions defined outside the class definition are not implicitly inline, but can be made inline by using the inline keyword. Therefore a static member function that is defined in a header file should be made inline so as not to violate the One Definition Rule (ODR) if that header is then included into multiple translation units.

    4. A word of warning about classes with all static members : 

        Be careful when writing classes with all static members. Although such “pure static classes” (also called “monostates”) can be useful, they also come with some potential downsides.

            1. First, because all static members are instantiated only once, there is no way to have multiple copies of a pure static class (without cloning the class and renaming it). For example, if you needed two independent IDGenerator, this would not be possible with a pure static class.

            2. Second, in the lesson on global variables, you learned that global variables are dangerous because any piece of code can change the value of the global variable and end up breaking another piece of seemingly unrelated code. The same holds true for pure static classes. Because all of the members belong to the class (instead of object of the class), and class declarations usually have global scope, a pure static class is essentially the equivalent of declaring functions and global variables in a globally accessible namespace, with all the requisite downsides that global variables have.

        => Instead of writing a class with all static members, consider writing a normal class and instantiating a global instance of it (global variables have static duration). That way the global instance can be used when appropriate, but local instances can still be instantiated if and when that is useful.

    5. Pure static classes vs namespaces : 

        => Pure static classes have a lot of overlap with namespaces. Both allow you to define variables with static duration and functions within their scope region. However, one significant difference is that classes have access controls while namespaces do not.

        => In general, a static class is preferable when you have static data members and/or need access controls. Otherwise, prefer a namespace.

    6. C++ does not support static constructors : 

        => If you can initialize normal member variables via a constructor, then by extension it makes sense that you should be able to initialize static member variables via a static constructor. And while some modern languages do support static constructors for precisely this purpose, C++ is unfortunately not one of them.

        => If your static variable can be directly initialized, no constructor is needed: you can initialize the static member variable at the point of definition (even if it is private). We do this in the IDGenerator example above. Here’s another example:

            struct Chars
            {
                char first{};
                char second{};
                char third{};
                char fourth{};
                char fifth{};
            };

            struct MyClass
            {
                static inline Chars s_mychars { 'a', 'e', 'i', 'o', 'u' }; // initialize static variable at point of definition
            };

        => If initializing your static member variable requires executing code (e.g. a loop), there are many different, somewhat obtuse ways of doing this. One way that works with all variables, static or not, is to use a function to create an object, fill it with data, and return it to the caller. This returned value can be copied into the object being initialized.

            struct Chars
            {
                char first{};
                char second{};
                char third{};
                char fourth{};
                char fifth{};
            };

            class MyClass
            {
            private:
                static Chars generate()
                {
                    Chars c{}; // create an object
                    c.first = 'a'; // fill it with values however you like
                    c.second = 'e';
                    c.third = 'i';
                    c.fourth = 'o';
                    c.fifth = 'u';

                    return c; // return the object
                }

            public:
                static inline Chars s_mychars { generate() }; // copy the returned object into s_mychars
            };

*/
int main()
{
    return 0;
}