#include <iostream>
/* 
    Notes :  
    
    1. So far, we’ve seen class types with two different kinds of members: data members and member functions. 

        => Class types support another kind of member: nested types (also called member types). To create a nested type, you simply define the type inside the class, under the appropriate access specifier.

            class Fruit
            {
            public:
                // FruitType has been moved inside the class, under the public access specifier
                    // We've also renamed it Type and made it an enum rather than an enum class
                enum Type
                {
                    apple,
                    banana,
                    cherry
                };

            private:
                Type m_type {};
                int m_percentageEaten { 0 };

            public:
                Fruit(Type type) :
                    m_type { type }
                {
                }

                Type getType() { return m_type;  }
                int getPercentageEaten() { return m_percentageEaten;  }

                bool isCherry() { return m_type == cherry; } // Inside members of Fruit, we no longer need to prefix enumerators with FruitType::
            };

    2. Nested types (member types) : 

        => First, note that FruitType is now defined inside the class, where it has been renamed Type for reasons that we will discuss shortly.

        => Second, nested type Type has been defined at the top of the class. Nested type names must be fully defined before they can be used, so they are usually defined first.

        => Third, nested types follow normal access rules. Type is defined under the public access specifier, so that the type name and enumerators can be directly accessed by the public.

        => Fourth, class types act as a scope region for names declared within, just as namespaces do. Therefore the fully qualified name of Type is Fruit::Type, and the fully qualified name of the apple enumerator is Fruit::apple.

        => Outside the class, we must use the fully qualified name (e.g. Fruit::apple). We renamed FruitType to Type so we can access it as Fruit::Type (rather than the more redundant Fruit::FruitType).

        => Finally, we changed our enumerated type from scoped to unscoped. Since the class itself is now acting as a scope region, it’s somewhat redundant to use a scoped enumerator as well. Changing to an unscoped enum means we can access enumerators as Fruit::apple rather than the longer Fruit::Type::apple we’d have to use if the enumerator were scoped.

    3. Nested typedefs and type aliases - 

        - Class types can also contain nested typedefs or type aliases:

            class Employee
            {
            public:
                using IDType = int;

            private:
                std::string m_name{};
                IDType m_id{};
                double m_wage{};

            public:
                Employee(std::string_view name, IDType id, double wage)
                    : m_name { name }
                    , m_id { id }
                    , m_wage { wage }
                {
                }

                const std::string& getName() { return m_name; }
                IDType getId() { return m_id; } // can use unqualified name within class
            };

        - Note that inside the class we can just use IDType, but outside the class we must use the fully qualified name Employee::IDType.

    4. Nested classes and access to outer class members - 

        It is fairly uncommon for classes to have other classes as a nested type, but it is possible. In C++, a nested class does not have access to the this pointer of the outer (containing) class, so nested classes can not directly access the members of the outer class. This is because a nested class can be instantiated independently of the outer class (and in such a case, there would be no outer class members to access!)

        => However, because nested classes are members of the outer class, they can access any private members of the outer class that are in scope.

            class Employee
            {
            public:
                using IDType = int;

                class Printer
                {
                public:
                    void print(const Employee& e) const
                    {
                        // Printer can't access Employee's `this` pointer
                        // so we can't print m_name and m_id directly
                        // Instead, we have to pass in an Employee object to use
                        // Because Printer is a member of Employee,
                        // we can access private members e.m_name and e.m_id directly
                        std::cout << e.m_name << " has id: " << e.m_id << '\n';
                    }
                };

            private:
                std::string m_name{};
                IDType m_id{};
                double m_wage{};

            public:
                Employee(std::string_view name, IDType id, double wage)
                    : m_name{ name }
                    , m_id{ id }
                    , m_wage{ wage }
                {
                }

                // removed the access functions in this example (since they aren't used)
            };

        => There is one case where nested classes are more commonly used. In the standard library, most iterator classes are implemented as nested classes of the container they are designed to iterate over. For example, std::string::iterator is implemented as a nested class of std::string. We’ll cover iterators in a future chapter.

    5. Nested types can’t be forward declared : 

        => There is one other limitation of nested types that is worth mentioning -- nested types can’t be forward declared. This limitation may be lifted in a future version of C++.

*/


class Fruit
{
public:
	// FruitType has been moved inside the class, under the public access specifier
        // We've also renamed it Type and made it an enum rather than an enum class
	enum Type
	{
		apple,
		banana,
		cherry
	};

private:
	Type m_type {};
	int m_percentageEaten { 0 };

public:
	Fruit(Type type) :
		m_type { type }
	{
	}

	Type getType() { return m_type;  }
	int getPercentageEaten() { return m_percentageEaten;  }

	bool isCherry() { return m_type == cherry; } // Inside members of Fruit, we no longer need to prefix enumerators with FruitType::
};

int main()
{
	// Note: Outside the class, we access the enumerators via the Fruit:: prefix now
	Fruit apple { Fruit::apple };

	if (apple.getType() == Fruit::apple)
		std::cout << "I am an apple";
	else
		std::cout << "I am not an apple";

	return 0;
}