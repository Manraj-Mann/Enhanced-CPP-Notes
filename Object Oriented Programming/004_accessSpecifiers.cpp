#include <iostream>
/* 
    Notes :  
    
    1. Member access - C++ has three different access levels: public, private, and protected. Whenever a member is accessed, the compiler checks whether the access level of the member permits that member to be accessed. If the access is not permitted, the compiler will generate a compilation error. This access level system is sometimes informally called access controls.

    2. The members of a struct are public by default - 

        - The members of a struct are public by default. Public members can be accessed by other members of the class type, and by the public.

        - The term “the public” is used to refer to code that exists outside of the members of a given class type. This includes non-member functions, as well as the members of other class types.

    3. The members of a class are private by default - 

        - Members that have the private access level are called private members. Private members are members of a class type that can only be accessed by other members of the same class.

        class Date // now a class instead of a struct
        {
            // class members are private by default, can only be accessed by other members
            int m_year {};     // private by default
            int m_month {};    // private by default
            int m_day {};      // private by default

            void print() const // private by default
            {
                // private members can be accessed in member functions
                std::cout << m_year << '/' << m_month << '/' << m_day;
            }
        };

    4. A class with private members is no longer an aggregate, and therefore can no longer use aggregate initialization.

    5. Naming your private member variables - 

        - Consider naming your private data members starting with an “m_” prefix to help distinguish them from the names of local variables, function parameters, and member functions.

        - Public members of classes may also follow this convention if desired. However, the public members of structs typically do not use this prefix since structs generally do not have many member functions (if any).

    6. Setting access levels via access specifiers - 

        - By default, the members of structs (and unions) are public, and the members of classes are private. However, we can explicitly set the access level of our members by using an access specifier. An access specifier sets the access level of all members that follow the specifier. C++ provides three access specifiers: public:, private:, and protected:.

        - Example : 

            class Date
            {
            // Any members defined here would default to private

            public: // here's our public access specifier

                void print() const // public due to above public: specifier
                {
                    // members can access other private members
                    std::cout << m_year << '/' << m_month << '/' << m_day;
                }

            private: // here's our private access specifier

                int m_year { 2020 };  // private due to above private: specifier
                int m_month { 14 }; // private due to above private: specifier
                int m_day { 10 };   // private due to above private: specifier
            };
    
    7. Access level summary - 

        Access level	Access specifier	Member access	Derived class access	Public access
        1.  Public           public:	         yes	            yes	                yes
        2.  Protected	     protected:	         yes	            yes	                no
        3.  Private	         private:	         yes	            no	                no

    8. Access level best practices for structs and classes - 

        - Structs should avoid access specifiers altogether, meaning all struct members will be public by default. We want our structs to be aggregates, and aggregates can only have public members. Using the public: access specifier would be redundant with the default, and using private: or protected: would make the struct a non-aggregate.

        - Classes should generally only have private (or protected) data members (either by using the default private access level, or the private: (or protected:) access specifier). 

        - Classes normally have public member functions (so those member functions can be used by the public after the object is created). However, occasionally member functions are made private (or protected) if they are not intended to be used by the public.

    9. Access levels work on a per-class basis - because access levels are per-class, not per-object, a member function can also directly access the private members of ANY other object of the same class type that is in scope.

        class Person
        {
        private:
            std::string m_name{};

        public:
            void kisses(const Person& p) const
            {
                std::cout << m_name << " kisses " << p.m_name << '\n';
            }

            void setName(std::string_view name)
            {
                m_name = name;
            }
        };

        int main()
        {
            Person joe;
            joe.setName("Joe");

            Person kate;
            kate.setName("Kate");

            joe.kisses(kate);

            return 0;
        }

    10. The technical and practical difference between structs and classes - 

        - A class defaults its members to private, whereas a struct defaults its members to public.

        - To be pedantic, there’s one more minor difference -- structs inherit from other class types publicly and classes inherit privately. We’ll cover what this means in the chapter on inheritance, but this particular point is practically irrelevant since you shouldn’t rely on the defaults for inheritance anyway.

*/
class Date // now a class instead of a struct
{
    // class members are private by default, can only be accessed by other members
    int m_year {};     // private by default
    int m_month {};    // private by default
    int m_day {};      // private by default

    void print() const // private by default
    {
        // private members can be accessed in member functions
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }
};

struct temp
{
    int i{10};
};

class Person
{
private:
    std::string m_name{};

public:
    void kisses(const Person& p) const
    {
        std::cout << m_name << " kisses " << p.m_name << '\n';
    }

    void setName(std::string_view name)
    {
        m_name = name;
    }
};
int main()
{
    temp t;
    std::cout<<"value = "<<t.i<<std::endl;

    // Date today { 2020, 10, 14 }; // compile error: can no longer use aggregate initialization

    // // private members can not be accessed by the public
    // today.m_day = 16; // compile error: the m_day member is private
    // today.print();    // compile error: the print() member function is private

    Person joe;
    joe.setName("Joe");

    Person kate;
    kate.setName("Kate");

    joe.kisses(kate);

    return 0;
}