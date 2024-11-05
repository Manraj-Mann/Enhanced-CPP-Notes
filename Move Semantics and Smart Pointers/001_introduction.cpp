#include <iostream>
/* 
    Notes :  
    
    1. Smart pointer classes to the rescue?

        - One of the best things about classes is that they contain destructors that automatically get executed when an object of the class goes out of scope. So if you allocate (or acquire) memory in your constructor, you can deallocate it in your destructor, and be guaranteed that the memory will be deallocated when the class object is destroyed (regardless of whether it goes out of scope, gets explicitly deleted, etc…). This is at the heart of the RAII programming paradigm.

        - So can we use a class to help us manage and clean up our pointers? We can! Consider a class whose sole job was to hold and “own” a pointer passed to it, and then deallocate that pointer when the class object went out of scope. As long as objects of that class were only created as local variables, we could guarantee that the class would properly go out of scope (regardless of when or how our functions terminate) and the owned pointer would get destroyed.

            template <typename T>
            class AutoPtr
            {
                T * _mPtr{};

                public:

                // constructor
                AutoPtr(T * ptr) : _mPtr(ptr) 
                {
                    std::cout<<"Pointer Allocated"<<std::endl;
                }

                // destructor
                ~AutoPtr()
                {
                    delete _mPtr;
                    std::cout<<"Pointer Released"<<std::endl;

                }

                // overloading (*) operator
                T & operator*()
                {
                    return *_mPtr;
                }

                // overloading (->) operator
                T* operator->()
                {
                    return _mPtr;
                }
            };

        - As long as AutoPtr is defined as a local variable (with automatic duration, hence the “Auto” part of the class name), the Resource will be guaranteed to be destroyed at the end of the block it is declared in, regardless of how the function terminates (even if it terminates early).

        - Such a class is called a smart pointer. A Smart pointer is a composition class that is designed to manage dynamically allocated memory and ensure that memory gets deleted when the smart pointer object goes out of scope. (Relatedly, built-in pointers are sometimes called “dumb pointers” because they can’t clean up after themselves).

    2. A critical flaw : The AutoPtr class has a critical flaw lurking behind some auto-generated code. 

        - Very likely (but not necessarily) your program will crash at this point. See the problem now? Because we haven’t supplied a copy constructor or an assignment operator, C++ provides one for us. And the functions it provides do shallow copies. So when we initialize res with pointer, both AutoPtr variables are pointed at the same Resource. When res goes out of the scope, it deletes the resource, leaving pointer with a dangling pointer. When pointer goes to delete its (already deleted) Resource, undefined behavior will result (probably a crash)!

        - You’d run into a similar problem with a function like this:

            void passByValue(Auto_ptr1<Resource> res)
            {
            }

        - Well, one thing we could do would be to explicitly define and delete the copy constructor and assignment operator, thereby preventing any copies from being made in the first place. That would prevent the pass by value case (which is good, we probably shouldn’t be passing these by value anyway).

        - But then how would we return an Autoptr from a function back to the caller?

            ??? generateResource()
            {
                Resource* r{ new Resource() };
                return Autoptr(r);
            }

        - We can’t return our AutoPtr by reference, because the local AutoPtr will be destroyed at the end of the function, and the caller will be left with a dangling reference. We could return pointer r as Resource*, but then we might forget to delete r later, which is the whole point of using smart pointers in the first place. So that’s out. Returning the Autoptr by value is the only option that makes sense -- but then we end up with shallow copies, duplicated pointers, and crashes.

        - Another option would be to overload the copy constructor and assignment operator to make deep copies. In this way, we’d at least guarantee to avoid duplicate pointers to the same object. But copying can be expensive (and may not be desirable or even possible), and we don’t want to make needless copies of objects just to return an AutoPtr from a function. Plus assigning or initializing a dumb pointer doesn’t copy the object being pointed to, so why would we expect smart pointers to behave differently? sWhat do we do?

    3. Move semantics : What if, instead of having our copy constructor and assignment operator copy the pointer (“copy semantics”), we instead transfer/move ownership of the pointer from the source to the destination object? This is the core idea behind move semantics. Move semantics means the class will transfer ownership of the object rather than making a copy. Deleting a nullptr is okay, as it does nothing.

        // Copy Constructor that implements move semantic
        AutoPtr(AutoPtr &ptr)
        {
            _mPtr = ptr._mPtr; // transfer our dumb pointer from the source to our local object
            ptr._mPtr = nullptr; // make sure the source no longer owns the pointer
        }

        // Assignment operator that implements move semantic
        AutoPtr& operator=(AutoPtr &ptr)
        {
            if(this == &ptr)
            {
                return *this;
            }

            delete _mPtr; // deallocate the  current 
            _mPtr = ptr._mPtr; // then transfer our dumb pointer from the source to the local object
            ptr._mPtr = nullptr;

            return *this;
        }

    4. std::auto_ptr, and why it was a bad idea : 

        - Now would be an appropriate time to talk about std::auto_ptr. std::auto_ptr, introduced in C++98 and removed in C++17, was C++’s first attempt at a standardized smart pointer. std::auto_ptr opted to implement move semantics just like the Autoptr class does. However, std::auto_ptr (and our AutoPtr class) has a number of problems that makes using it dangerous.

        - First, because std::auto_ptr implements move semantics through the copy constructor and assignment operator, passing a std::auto_ptr by value to a function will cause your resource to get moved to the function parameter (and be destroyed at the end of the function when the function parameters go out of scope). Then when you go to access your auto_ptr argument from the caller (not realizing it was transferred and deleted), you’re suddenly dereferencing a null pointer. Crash!

        - Second, std::auto_ptr always deletes its contents using non-array delete. This means auto_ptr won’t work correctly with dynamically allocated arrays, because it uses the wrong kind of deallocation. Worse, it won’t prevent you from passing it a dynamic array, which it will then mismanage, leading to memory leaks.

        Finally, auto_ptr doesn’t play nice with a lot of the other classes in the standard library, including most of the containers and algorithms. This occurs because those standard library classes assume that when they copy an item, it actually makes a copy, not a move.

    5. Moving forward : 
    
        - The core problem with the design of std::auto_ptr is that prior to C++11, the C++ language simply had no mechanism to differentiate “copy semantics” from “move semantics”. Overriding the copy semantics to implement move semantics leads to weird edge cases and inadvertent bugs. For example, you can write res1 = res2 and have no idea whether res2 will be changed or not!

        - Because of this, in C++11, the concept of “move” was formally defined, and “move semantics” were added to the language to properly differentiate copying from moving. Now that we’ve set the stage for why move semantics can be useful, we’ll explore the topic of move semantics throughout the rest of this chapter. We’ll also fix our Autoptr class using move semantics.

        - In C++11, std::auto_ptr has been replaced by a bunch of other types of “move-aware” smart pointers: std::unique_ptr, std::weak_ptr, and std::shared_ptr. We’ll also explore the two most popular of these: unique_ptr (which is a direct replacement for auto_ptr) and shared_ptr.

*/


template <typename T>
class AutoPtr
{
    T * _mPtr{};

    public:

    // constructor
    AutoPtr(T * ptr = nullptr) : _mPtr(ptr) 
    {
        std::cout<<"Pointer Allocated"<<std::endl;
    }

    // destructor
    ~AutoPtr()
    {
        delete _mPtr;
        std::cout<<"Pointer Released"<<std::endl;

    }

    // Copy Constructor that implements move semantic
    AutoPtr(AutoPtr &ptr)
    {
        _mPtr = ptr._mPtr; // transfer our dumb pointer from the source to our local object
        ptr._mPtr = nullptr; // make sure the source no longer owns the pointer
    }

    // Assignment operator that implements move semantic
    AutoPtr& operator=(AutoPtr &ptr)
    {
        if(this == &ptr)
        {
            return *this;
        }

        delete _mPtr; // deallocate the  current 
        _mPtr = ptr._mPtr; // then transfer our dumb pointer from the source to the local object
        ptr._mPtr = nullptr;

        return *this;
    }

    // overloading (*) operator
    T & operator*()
    {
        return *_mPtr;
    }

    // overloading (->) operator
    T* operator->()
    {
        return _mPtr;
    }

    bool isNull()
    {
        return _mPtr == nullptr;
    }
};

class Resource
{
    public:

    Resource()
    {
        std::cout<<"Resource Acquired"<<std::endl;
    }

    ~Resource()
    {
        std::cout<<"Resource Released"<<std::endl;
    }

    void sayHello()
    {
        std::cout<<"Hello Smarty !"<<std::endl;
    }
};

void passByValue(AutoPtr<Resource> pointer)
{

}

int main()
{
    AutoPtr<Resource> pointer{new Resource()};

    pointer->sayHello();

    // AutoPtr<Resource> res(pointer); // crash with default copy constructor

    // passByValue(pointer); // crash with default copy constructor

    // implemented move semantics

    AutoPtr<Resource> res(pointer);

    std::cout<<"Object is null ? "<<std::boolalpha<<pointer.isNull()<<std::endl;
    std::cout<<"Object is null ? "<<std::boolalpha<<res.isNull()<<std::endl;

    pointer = res;

    std::cout<<"Object is null ? "<<std::boolalpha<<pointer.isNull()<<std::endl;
    std::cout<<"Object is null ? "<<std::boolalpha<<res.isNull()<<std::endl;


    return 0;
}