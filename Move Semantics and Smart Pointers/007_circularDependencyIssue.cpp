#include <iostream>
/* 
    Notes :  
    
    1. Consider the following case, where the shared pointers in two separate objects each point at the other object:

        class Person
        {
            std::string m_name;
            std::shared_ptr<Person> m_partner; // initially created empty

        public:

            Person(const std::string &name): m_name(name)
            {
                std::cout << m_name << " created\n";
            }
            ~Person()
            {
                std::cout << m_name << " destroyed\n";
            }

            friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
            {
                if (!p1 || !p2)
                    return false;

                p1->m_partner = p2;
                p2->m_partner = p1;

                std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

                return true;
            }
        };

        int main()
        {
            auto lucy { std::make_shared<Person>("Lucy") }; // create a Person named "Lucy"
            auto ricky { std::make_shared<Person>("Ricky") }; // create a Person named "Ricky"

            partnerUp(lucy, ricky); // Make "Lucy" point to "Ricky" and vice-versa

            return 0;
        }   

        - Then the program ends -- and neither Person “Lucy” or “Ricky” have been deallocated! Essentially, “Lucy” ends up keeping “Ricky” from being destroyed, and “Ricky” ends up keeping “Lucy” from being destroyed. It turns out that this can happen any time shared pointers form a circular reference.

    2. Circular references : 

        - A Circular reference (also called a cyclical reference or a cycle) is a series of references where each object references the next, and the last object references back to the first, causing a referential loop. The references do not need to be actual C++ references -- they can be pointers, unique IDs, or any other means of identifying specific objects.

        - In the context of shared pointers, the references will be pointers.

        - This is exactly what we see in the case above: “Lucy” points at “Ricky”, and “Ricky” points at “Lucy”. With three pointers, you’d get the same thing when A points at B, B points at C, and C points at A. The practical effect of having shared pointers form a cycle is that each object ends up keeping the next object alive -- with the last object keeping the first object alive. Thus, no objects in the series can be deallocated because they all think some other object still needs it!
    
    3. A reductive case : It turns out, this cyclical reference issue can even happen with a single std::shared_ptr -- a std::shared_ptr referencing the object that contains it is still a cycle (just a reductive one). Although it’s fairly unlikely that this would ever happen in practice, we’ll show you for additional comprehension:

        class Resource
        {
        public:
            std::shared_ptr<Resource> m_ptr {}; // initially created empty

            Resource() { std::cout << "Resource acquired\n"; }
            ~Resource() { std::cout << "Resource destroyed\n"; }
        };

        int main()
        {
            auto ptr1 { std::make_shared<Resource>() };

            ptr1->m_ptr = ptr1; // m_ptr is now sharing the Resource that contains it

            return 0;
        }

        - In the above example, when ptr1 goes out of scope, the Resource is not deallocated because the Resource’s m_ptr is sharing the Resource. At that point, the only way for the Resource to be released would be to set m_ptr to something else (so nothing is sharing the Resource any longer). But we can’t access m_ptr because ptr1 is out of scope, so we no longer have a way to do this. The Resource has become a memory leak.

    4. So what is std::weak_ptr for anyway?

        - std::weak_ptr was designed to solve the “cyclical ownership” problem described above. A std::weak_ptr is an observer -- it can observe and access the same object as a std::shared_ptr (or other std::weak_ptrs) but it is not considered an owner. Remember, when a std::shared pointer goes out of scope, it only considers whether other std::shared_ptr are co-owning the object. std::weak_ptr does not count!

        - Example : 

            class Person
            {
                std::string m_name;
                std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr

            public:

                Person(const std::string &name): m_name(name)
                {
                    std::cout << m_name << " created\n";
                }
                ~Person()
                {
                    std::cout << m_name << " destroyed\n";
                }

                friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
                {
                    if (!p1 || !p2)
                        return false;

                    p1->m_partner = p2;
                    p2->m_partner = p1;

                    std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

                    return true;
                }
            };

            int main()
            {
                auto lucy { std::make_shared<Person>("Lucy") };
                auto ricky { std::make_shared<Person>("Ricky") };

                partnerUp(lucy, ricky);

                return 0;
            }

    5. Using std::weak_ptr : One downside of std::weak_ptr is that std::weak_ptr are not directly usable (they have no operator->). To use a std::weak_ptr, you must first convert it into a std::shared_ptr. Then you can use the std::shared_ptr. To convert a std::weak_ptr into a std::shared_ptr, you can use the lock() member function. Here’s the above example, updated to show this off:

        class Person
        {
            std::string m_name;
            std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr

        public:

            Person(const std::string &name) : m_name(name)
            {
                std::cout << m_name << " created\n";
            }
            ~Person()
            {
                std::cout << m_name << " destroyed\n";
            }

            friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
            {
                if (!p1 || !p2)
                    return false;

                p1->m_partner = p2;
                p2->m_partner = p1;

                std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

                return true;
            }

            std::shared_ptr<Person> getPartner() const { return m_partner.lock(); } // use lock() to convert weak_ptr to shared_ptr
            const std::string& getName() const { return m_name; }
        };

        int main()
        {
            auto lucy { std::make_shared<Person>("Lucy") };
            auto ricky { std::make_shared<Person>("Ricky") };

            partnerUp(lucy, ricky);

            auto partner = ricky->getPartner(); // get shared_ptr to Ricky's partner
            std::cout << ricky->getName() << "'s partner is: " << partner->getName() << '\n';

            return 0;
        }

    6. Avoiding dangling pointers with std::weak_ptr : 

        - Consider the case where a normal “dumb” pointer is holding the address of some object, and then that object is destroyed. Such a pointer is dangling, and dereferencing the pointer will lead to undefined behavior. And unfortunately, there is no way for us to determine whether a pointer holding a non-null address is dangling or not. This is a large part of the reason dumb pointers are dangerous.

        - Because std::weak_ptr won’t keep an owned resource alive, it’s similarly possible for a std::weak_ptr to be left pointing to a resource that has been deallocated by a std::shared_ptr. However, std::weak_ptr has a neat trick up its sleeve -- because it has access to the reference count for an object, it can determine if it is pointing to a valid object or not! If the reference count is non-zero, the resource is still valid. If the reference count is zero, then the resource has been destroyed.

        - The easiest way to test whether a std::weak_ptr is valid is to use the expired() member function, which returns true if the std::weak_ptr is pointing to an invalid object, and false otherwise.

        - Example : 

            class Resource
            {
            public:
                Resource() { std::cerr << "Resource acquired\n"; }
                ~Resource() { std::cerr << "Resource destroyed\n"; }
            };

            // Returns a std::weak_ptr to an invalid object
            std::weak_ptr<Resource> getWeakPtr()
            {
                auto ptr{ std::make_shared<Resource>() };
                return std::weak_ptr<Resource>{ ptr };
            } // ptr goes out of scope, Resource destroyed

            // Returns a dumb pointer to an invalid object
            Resource* getDumbPtr()
            {
                auto ptr{ std::make_unique<Resource>() };
                return ptr.get();
            } // ptr goes out of scope, Resource destroyed

            int main()
            {
                auto dumb{ getDumbPtr() };
                std::cout << "Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");

                auto weak{ getWeakPtr() };
                std::cout << "Our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");

                return 0;
            }

        - Note that if a std::weak_ptr is expired, then we shouldn’t call lock() on it, because the object being pointed to has already been destroyed, so there is no object to share. If you do call lock() on an expired std::weak_ptr, it will return a std::shared_ptr to nullptr.

    7. std::shared_ptr can be used when you need multiple smart pointers that can co-own a resource. The resource will be deallocated when the last std::shared_ptr goes out of scope. std::weak_ptr can be used when you want a smart pointer that can see and use a shared resource, but does not participate in the ownership of that resource.

*/

#include <memory>
class Resource
{
public:
	Resource() { std::cerr << "Resource acquired\n"; }
	~Resource() { std::cerr << "Resource destroyed\n"; }
};

// Returns a std::weak_ptr to an invalid object
std::weak_ptr<Resource> getWeakPtr()
{
	auto ptr{ std::make_shared<Resource>() };
	return std::weak_ptr<Resource>{ ptr };
} // ptr goes out of scope, Resource destroyed

// Returns a dumb pointer to an invalid object
Resource* getDumbPtr()
{
	auto ptr{ std::make_unique<Resource>() };
	return ptr.get();
} // ptr goes out of scope, Resource destroyed

int main()
{
	auto dumb{ getDumbPtr() };
	std::cout << "Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");

	auto weak{ getWeakPtr() };
	std::cout << "Our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");

	return 0;
}