#include <iostream>

/*
    Note : 

    1. Unnamed (anonymous) namespaces - An unnamed namespace (also called an anonymous namespace) is a namespace that is defined without a name, like so:

        namespace // unnamed namespace
        {
            void doSomething() // can only be accessed in this file
            {
                std::cout << "v1\n";
            }
        }

    2. Avoid unnamed namespaces in header files.

    3. An inline namespace is a namespace that is typically used to version content. Much like an unnamed namespace, anything declared inside an inline namespace is considered part of the parent namespace. However, unlike unnamed namespaces, inline namespaces don’t affect linkage.

    4. Mixing inline and unnamed namespaces - A namespace can be both inline and unnamed.

        namespace V1 // declare a normal namespace named V1
        {
            void doSomething()
            {
                std::cout << "V1\n";
            }
        }

        inline namespace // declare an inline unnamed namespace
        {
            void doSomething() // has internal linkage
            {
                std::cout << "V2\n";
            }
        }

        V1::doSomething(); // calls the V1 version of doSomething()
        // there is no V2 in this example, so we can't use V2:: as a namespace prefix

        doSomething(); // calls the inline version of doSomething() (which is the anonymous one)

    5. However, in such cases, it’s probably better to nest an anonymous namespace inside an inline namespace. This has the same effect (all functions inside the anonymous namespace have internal linkage by default) but still gives you an explicit namespace name you can use:

        namespace V1 // declare a normal namespace named V1
        {
            void doSomething()
            {
                std::cout << "V1\n";
            }
        }

        inline namespace V2 // declare an inline namespace named V2
        {
            namespace // unnamed namespace
            {
                void doSomething() // has internal linkage
                {
                    std::cout << "V2\n";
                }

            }
        }

        V1::doSomething(); // calls the V1 version of doSomething()
        V2::doSomething(); // calls the V2 version of doSomething()

        doSomething(); // calls the inline version of doSomething() (which is V2)

*/

inline namespace V1 // declare an inline namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

namespace V2 // declare a normal namespace named V2
{
    void doSomething()
    {
        std::cout << "V2\n";
    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    V2::doSomething(); // calls the V2 version of doSomething()

    doSomething(); // calls the inline version of doSomething() (which is V1)
    return 0;
}