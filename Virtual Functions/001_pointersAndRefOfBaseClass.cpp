#include <iostream>
/* 
    Notes :  Pointers and references to the base class of derived objects
    
    1. Base and Derived Class : 

        class Base
        {
        protected:
            int m_value {};

        public:
            Base(int value)
                : m_value{ value }
            {
            }

            std::string_view getName() const { return "Base"; }
            int getValue() const { return m_value; }
        };

        class Derived: public Base
        {
        public:
            Derived(int value)
                : Base{ value }
            {
            }

            std::string_view getName() const { return "Derived"; }
            int getValueDoubled() const { return m_value * 2; }
        };

        - When we create a Derived object, it contains a Base part (which is constructed first), and a Derived part (which is constructed second). Remember that inheritance implies an is-a relationship between two classes. Since a Derived is-a Base, it is appropriate that Derived contain a Base part.

    2. Pointers, references, and derived classes : 

        - It should be fairly intuitive that we can set Derived pointers and references to Derived objects: 

            int main()
            {
                Derived derived{ 5 };
                std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';

                Derived& rDerived{ derived };
                std::cout << "rDerived is a " << rDerived.getName() << " and has value " << rDerived.getValue() << '\n';

                Derived* pDerived{ &derived };
                std::cout << "pDerived is a " << pDerived->getName() << " and has value " << pDerived->getValue() << '\n';

                return 0;
            }

        - However, since Derived has a Base part, a more interesting question is whether C++ will let us set a Base pointer or reference to a Derived object. It turns out, we can!

            int main()
            {
                Derived derived{ 5 };

                // These are both legal!
                Base& rBase{ derived }; // rBase is an lvalue reference (not an rvalue reference)
                Base* pBase{ &derived };

                std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';
                std::cout << "rBase is a " << rBase.getName() << " and has value " << rBase.getValue() << '\n';
                std::cout << "pBase is a " << pBase->getName() << " and has value " << pBase->getValue() << '\n';

                return 0;
            }

        - It turns out that because rBase and pBase are a Base reference and pointer, they can only see members of Base (or any classes that Base inherited). So even though Derived::getName() shadows (hides) Base::getName() for Derived objects, the Base pointer/reference can not see Derived::getName(). Consequently, they call Base::getName(), which is why rBase and pBase report that they are a Base rather than a Derived.

        - Note that this also means it is not possible to call Derived::getValueDoubled() using rBase or pBase. They are unable to see anything in Derived.

            class Animal
            {
            protected:
                std::string m_name;

                // We're making this constructor protected because
                // we don't want people creating Animal objects directly,
                // but we still want derived classes to be able to use it.
                Animal(std::string_view name)
                    : m_name{ name }
                {
                }

                // To prevent slicing (covered later)
                Animal(const Animal&) = delete;
                Animal& operator=(const Animal&) = delete;

            public:
                std::string_view getName() const { return m_name; }
                std::string_view speak() const { return "???"; }
            };

            class Cat: public Animal
            {
            public:
                Cat(std::string_view name)
                    : Animal{ name }
                {
                }

                std::string_view speak() const { return "Meow"; }
            };

            class Dog: public Animal
            {
            public:
                Dog(std::string_view name)
                    : Animal{ name }
                {
                }

                std::string_view speak() const { return "Woof"; }
            };

            int main()
            {
                const Cat cat{ "Fred" };
                std::cout << "cat is named " << cat.getName() << ", and it says " << cat.speak() << '\n';

                const Dog dog{ "Garbo" };
                std::cout << "dog is named " << dog.getName() << ", and it says " << dog.speak() << '\n';

                const Animal* pAnimal{ &cat };
                std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

                pAnimal = &dog;
                std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

                return 0;
            }

            - Animal speak() will print ??? here.

    3. Use for pointers and references to base classes : 

        - First, let’s say you wanted to write a function that printed an animal’s name and sound. Without using a pointer to a base class, you’d have to write it using overloaded functions, like this:

            void report(const Cat& cat)
            {
                std::cout << cat.getName() << " says " << cat.speak() << '\n';
            }

            void report(const Dog& dog)
            {
                std::cout << dog.getName() << " says " << dog.speak() << '\n';
            }
        
        - Not too difficult, but consider what would happen if we had 30 different animal types instead of 2. You’d have to write 30 almost identical functions! Plus, if you ever added a new type of animal, you’d have to write a new function for that one too. This is a huge waste of time considering the only real difference is the type of the parameter. However, because Cat and Dog are derived from Animal, Cat and Dog have an Animal part. Therefore, it makes sense that we should be able to do something like this:

            void report(const Animal& rAnimal)
            {
                std::cout << rAnimal.getName() << " says " << rAnimal.speak() << '\n';
            }

        - The problem is, of course, that because rAnimal is an Animal reference, rAnimal.speak() will call Animal::speak() instead of the derived version of speak().

        - Second, let’s say you had 3 cats and 3 dogs that you wanted to keep in an array for easy access. Because arrays can only hold objects of one type, without a pointer or reference to a base class, you’d have to create a different array for each derived type, like this:

            int main()
            {
                const auto& cats{ std::to_array<Cat>({{ "Fred" }, { "Misty" }, { "Zeke" }}) };
                const auto& dogs{ std::to_array<Dog>({{ "Garbo" }, { "Pooky" }, { "Truffle" }}) };

                // Before C++20
                // const std::array<Cat, 3> cats{{ { "Fred" }, { "Misty" }, { "Zeke" } }};
                // const std::array<Dog, 3> dogs{{ { "Garbo" }, { "Pooky" }, { "Truffle" } }};

                for (const auto& cat : cats)
                {
                    std::cout << cat.getName() << " says " << cat.speak() << '\n';
                }

                for (const auto& dog : dogs)
                {
                    std::cout << dog.getName() << " says " << dog.speak() << '\n';
                }

                return 0;
            }

        - Now, consider what would happen if you had 30 different types of animals. You’d need 30 arrays, one for each type of animal! However, because both Cat and Dog are derived from Animal, it makes sense that we should be able to do something like this:

            // Before C++20, with the array size being explicitly specified
            // const std::array<const Animal*, 6> animals{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };

            for (const auto animal : animals)
            {
                std::cout << animal->getName() << " says " << animal->speak() << '\n';
            }

        - Although both of these techniques could save us a lot of time and energy, they have the same problem. The pointer or reference to the base class calls the base version of the function rather than the derived version. If only there was some way to make those base pointers call the derived version of a function instead of the base version… Want to take a guess what virtual functions are for? :)

*/
int main()
{
    return 0;
}