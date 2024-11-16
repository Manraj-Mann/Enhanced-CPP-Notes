#include <iostream>
/* 
    Notes :  Virtual functions and polymorphism
    
    1. Because rBase is a Base reference, it calls Base::getName(), even though it’s actually referencing the Base portion of a Derived object. In this lesson, we will show how to address this issue using virtual functions.

    2. Virtual functions : 

        - A virtual function is a special type of member function that, when called, resolves to the most-derived version of the function for the actual type of the object being referenced or pointed to.

        - A derived function is considered a match if it has the same signature (name, parameter types, and whether it is const) and return type as the base version of the function. Such functions are called overrides.

        - Example : 

            class Base
            {
            public:
                virtual std::string_view getName() const { return "Base"; } // note addition of virtual keyword
            };

            class Derived: public Base
            {
            public:
                virtual std::string_view getName() const { return "Derived"; }
            };

            int main()
            {
                Derived derived {};
                Base& rBase{ derived };
                std::cout << "rBase is a " << rBase.getName() << '\n';

                return 0;
            }

            Note : Some modern compilers may give an error about having virtual functions and an accessible non-virtual destructor. If this is the case, add a virtual destructor to the base class. In the above program, add this to the definition of Base:

                virtual ~Base() = default;

        - Because rBase is a reference to the Base portion of a Derived object, when rBase.getName() is evaluated, it would normally resolve to Base::getName(). However, Base::getName() is virtual, which tells the program to go look and see if there are any more-derived versions of the function available for a Derived object. In this case, it will resolve to Derived::getName()!

        - Note that virtual function resolution only works when a virtual member function is called through a pointer or reference to a class type object. This works because the compiler can differentiate the type of the pointer or reference from the type of the object being pointed to or referenced. We see this in example above.

        - Calling a virtual member function directly on an object (not through a pointer or reference) will always invoke the member function belonging to the same type of that object. For example:

            C c{};
            std::cout << c.getName(); // will always call C::getName

            A a { c }; // copies the A portion of c into a (don't do this)
            std::cout << a.getName(); // will always call A::getName

        - Key insight : Virtual function resolution only works when a member function is called through a pointer or reference to a class type object.

    3. Polymorphism : In programming, polymorphism refers to the ability of an entity to have multiple forms (the term “polymorphism” literally means “many forms”). For example, consider the following two function declarations:

        int add(int, int);
        double add(double, double);

        - The identifier add has two forms: add(int, int) and add(double, double).

        - "Compile-time polymorphism" - refers to forms of polymorphism that are resolved by the compiler. These include function overload resolution, as well as template resolution.

        - "Runtime polymorphism" - refers to forms of polymorphism that are resolved at runtime. This includes virtual function resolution.

    4. A word of warning: the signature of the derived class function must exactly match the signature of the base class virtual function in order for the derived class function to be used. If the derived class function has different parameter types, the program will likely still compile fine, but the virtual function will not resolve as intended. In the next lesson, we’ll discuss how to guard against this.

    5. Note that if a function is marked as virtual, all matching overrides in derived classes are also implicitly considered virtual, even if they are not explicitly marked as such. If a function is virtual, all matching overrides in derived classes are implicitly virtual.

    6. Return types of virtual functions : Under normal circumstances, the return type of a virtual function and its override must match. Consider the following example:   

        class Base
        {
        public:
            virtual int getValue() const { return 5; }
        };

        class Derived: public Base
        {
        public:
            virtual double getValue() const { return 6.78; }
        };

        - In this case, Derived::getValue() is not considered a matching override for Base::getValue() and compilation will fail.

    7. Do not call virtual functions from constructors or destructors : 

        - Here’s another gotcha that often catches unsuspecting new programmers. You should not call virtual functions from constructors or destructors. Why?

    8. Remember that when a Derived class is created, the Base portion is constructed first. If you were to call a virtual function from the Base constructor, and Derived portion of the class hadn’t even been created yet, it would be unable to call the Derived version of the function because there’s no Derived object for the Derived function to work on. In C++, it will call the Base version instead.

        - A similar issue exists for destructors. If you call a virtual function in a Base class destructor, it will always resolve to the Base class version of the function, because the Derived portion of the class will already have been destroyed.

        - Never call virtual functions from constructors or destructors.

    9. The downside of virtual functions - Since most of the time you’ll want your functions to be virtual, why not just make all functions virtual? The answer is because it’s inefficient -- resolving a virtual function call takes longer than resolving a regular one. Furthermore, the compiler also has to allocate an extra pointer for each class object that has one or more virtual functions. We’ll talk about this more in future lessons in this chapter.

*/

class base
{

    public:

    base()
    {
        std::cout<<"Base constructor called"<<std::endl;
    }

    virtual void print()
    {
        std::cout<<"base class"<<std::endl;
    }

    virtual ~base()
    {
        std::cout<<"Base destructor called"<<std::endl;

    }

};

class derived : public base
{
    public : 

    derived()
    {
        std::cout<<"derived constructor called"<<std::endl;

    }
    virtual void print()
    {
        std::cout<<"derived class"<<std::endl;
    }

    virtual ~derived()
    {
        std::cout<<"derived destructor called"<<std::endl;
    }
};

class superchild :  public derived 
{
    public : 

    superchild()
    {
        std::cout<<"superchild constructor called"<<std::endl;

    }
    virtual void print()
    {
        std::cout<<"superchild class"<<std::endl;
    }

    virtual ~superchild()
    {
        std::cout<<"superchild destructor called"<<std::endl;

    }
};

int main()
{
    superchild d;

    base * b {&d};

    d.print();


    // superchild c1 , c2 , c3;
    // derived d1 , d2 , d3;

    // base * classes[] = {&c1 , &c2 , &c3 , &d1 , &d2 , &d3};

    // for( auto * classI : classes)
    // {
    //     classI->print();
    // }



    return 0;
}