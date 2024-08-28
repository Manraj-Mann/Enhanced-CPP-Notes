#include <iostream>

/*
    Note : 
    
    1. As a reminder, a naming collision occurs when two identical identifiers are introduced into the same scope, and the compiler can’t disambiguate which one to use.When this happens, compiler or linker will produce an error because they do not have enough information to resolve the ambiguity.

    2. Defining your own namespaces : 

        namespace NamespaceIdentifier
        {
            // content of namespace here
        }

    3. We recommend starting namespace names with a capital letter. However, either style should be seen as acceptable. A namespace must be defined either in the global scope, or inside another namespace. Much like the content of a function, the content of a namespace is conventionally indented one level.

    4. There are two different ways to tell the compiler which version of doSomething() to use, 
    
        4.1. via the scope resolution operator, or 
        4.2. via using statements (which we’ll discuss in a later lesson in this chapter).

    5. Forward declaration of content in namespaces:

        namespace BasicMath
        {
            // function add() is part of namespace BasicMath
            int add(int x, int y);
        }
    
    6. Multiple namespace blocks are allowed:

        #ifndef CIRCLE_H
        #define CIRCLE_H

        namespace BasicMath
        {
            constexpr double pi{ 3.14 };
        }

        #endif

        #ifndef GROWTH_H
        #define GROWTH_H

        namespace BasicMath
        {
            // the constant e is also part of namespace BasicMath
            constexpr double e{ 2.7 };
        }

        #endif

        std::cout << BasicMath::pi << '\n';
        std::cout << BasicMath::e << '\n';

    7. Namespace aliases : create namespace aliases, which allow us to temporarily shorten a long sequence of namespaces into something shorter:

        namespace Active = Foo::Goo; // active now refers to Foo::Goo
        std::cout << Active::add(1, 2) << '\n'; // This is really Foo::Goo::add()
    

*/

namespace Helpers
{
    void print()
    {
        std::cout<<"FGood one\n";
    }

    namespace  Mathematical
    {
        void print()
        {
            std::cout<<"MGood one\n";
        }
    }

}

int main()
{

    Helpers::print();
    Helpers::Mathematical::print();

    namespace good = Helpers::Mathematical;

    good::print();
    
    return 0;
}