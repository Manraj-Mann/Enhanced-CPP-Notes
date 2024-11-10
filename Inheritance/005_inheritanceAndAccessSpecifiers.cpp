#include <iostream>

/*
    Notes : 

    1. To this point, you’ve seen the private and public access specifiers, which determine who can access the members of a class. As a quick refresher, public members can be accessed by anybody. Private members can only be accessed by member functions of the same class or friends. This means derived classes can not access private members of the base class directly!

        class Base
        {
        private:
            int m_private {}; // can only be accessed by Base members and friends (not derived classes)
        public:
            int m_public {}; // can be accessed by anybody
        };

    2. The protected access specifier - C++ has a third access specifier that we have yet to talk about because it’s only useful in an inheritance context. The protected access specifier allows the class the member belongs to, friends, and derived classes to access the member. However, protected members are not accessible from outside the class.
    
        class Base
        {
        public:
            int m_public {}; // can be accessed by anybody
        protected:
            int m_protected {}; // can be accessed by Base members, friends, and derived classes
        private:
            int m_private {}; // can only be accessed by Base members and friends (but not derived classes)
        };

        class Derived: public Base
        {
        public:
            Derived()
            {
                m_public = 1; // allowed: can access public base members from derived class
                m_protected = 2; // allowed: can access protected base members from derived class
                m_private = 3; // not allowed: can not access private base members from derived class
            }
        };

        int main()
        {
            Base base;
            base.m_public = 1; // allowed: can access public members from outside class
            base.m_protected = 2; // not allowed: can not access protected members from outside class
            base.m_private = 3; // not allowed: can not access private members from outside class

            return 0;
        }

    3. So when should I use the protected access specifier?

        - With a protected attribute in a base class, derived classes can access that member directly. This means that if you later change anything about that protected attribute (the type, what the value means, etc…), you’ll probably need to change both the base class AND all of the derived classes.

        - Therefore, using the protected access specifier is most useful when you (or your team) are going to be the ones deriving from your own classes, and the number of derived classes is reasonable. That way, if you make a change to the implementation of the base class, and updates to the derived classes are necessary as a result, you can make the updates yourself (and have it not take forever, since the number of derived classes is limited).

        - Favor private members over protected members.

    4. Different kinds of inheritance, and their impact on access : First, there are three different ways for classes to inherit from other classes: public, protected, and private.

        -Example : 

            // Inherit from Base publicly
            class Pub: public Base
            {
            };

            // Inherit from Base protectedly
            class Pro: protected Base
            {
            };

            // Inherit from Base privately
            class Pri: private Base
            {
            };

            class Def: Base // Defaults to private inheritance
            {
            };

        - That gives us 9 combinations: 3 member access specifiers (public, private, and protected), and 3 inheritance types (public, private, and protected).

    5. Public inheritance is by far the most commonly used type of inheritance. In fact, very rarely will you see or use the other types of inheritance, so your primary focus should be on understanding this section. Fortunately, public inheritance is also the easiest to understand. 
    
        - When you inherit a base class publicly, inherited public members stay public, and inherited protected members stay protected. Inherited private members, which were inaccessible because they were private in the base class, stay inaccessible.

        - Example : 

            class Base
            {
            public:
                int m_public {};
            protected:
                int m_protected {};
            private:
                int m_private {};
            };

            class Pub: public Base // note: public inheritance
            {
                // Public inheritance means:
                // Public inherited members stay public (so m_public is treated as public)
                // Protected inherited members stay protected (so m_protected is treated as protected)
                // Private inherited members stay inaccessible (so m_private is inaccessible)
            public:
                Pub()
                {
                    m_public = 1; // okay: m_public was inherited as public
                    m_protected = 2; // okay: m_protected was inherited as protected
                    m_private = 3; // not okay: m_private is inaccessible from derived class
                }
            };

            int main()
            {
                // Outside access uses the access specifiers of the class being accessed.
                Base base;
                base.m_public = 1; // okay: m_public is public in Base
                base.m_protected = 2; // not okay: m_protected is protected in Base
                base.m_private = 3; // not okay: m_private is private in Base

                Pub pub;
                pub.m_public = 1; // okay: m_public is public in Pub
                pub.m_protected = 2; // not okay: m_protected is protected in Pub
                pub.m_private = 3; // not okay: m_private is inaccessible in Pub

                return 0;
            }

        - This is the same as the example above where we introduced the protected access specifier, except that we’ve instantiated the derived class as well, just to show that with public inheritance, things work identically in the base and derived class.

    6. Protected inheritance is the least common method of inheritance. It is almost never used, except in very particular cases. With protected inheritance, the public and protected members become protected, and private members stay inaccessible. Because this form of inheritance is so rare, we’ll skip the example and just summarize with a table:
     
        - Access specifier in base class	Access specifier when inherited protectedly
                    Public	                           Protected
                    Protected	                       Protected
                    Private	                           Inaccessible
                        
    7. Private inheritance : With private inheritance, all members from the base class are inherited as private. This means private members are inaccessible, and protected and public members become private. Note that this does not affect the way that the derived class accesses members inherited from its parent! It only affects the code trying to access those members through the derived class.

        class Base
        {
        public:
            int m_public {};
        protected:
            int m_protected {};
        private:
            int m_private {};
        };

        class Pri: private Base // note: private inheritance
        {
            // Private inheritance means:
            // Public inherited members become private (so m_public is treated as private)
            // Protected inherited members become private (so m_protected is treated as private)
            // Private inherited members stay inaccessible (so m_private is inaccessible)
        public:
            Pri()
            {
                m_public = 1; // okay: m_public is now private in Pri
                m_protected = 2; // okay: m_protected is now private in Pri
                m_private = 3; // not okay: derived classes can't access private members in the base class
            }
        };

        int main()
        {
            // Outside access uses the access specifiers of the class being accessed.
            // In this case, the access specifiers of base.
            Base base;
            base.m_public = 1; // okay: m_public is public in Base
            base.m_protected = 2; // not okay: m_protected is protected in Base
            base.m_private = 3; // not okay: m_private is private in Base

            Pri pri;
            pri.m_public = 1; // not okay: m_public is now private in Pri
            pri.m_protected = 2; // not okay: m_protected is now private in Pri
            pri.m_private = 3; // not okay: m_private is inaccessible in Pri

            return 0;
        }

        - Private inheritance can be useful when the derived class has no obvious relationship to the base class, but uses the base class for implementation internally. In such a case, we probably don’t want the public interface of the base class to be exposed through objects of the derived class (as it would be if we inherited publicly).

    8. Summary : 
    
        - First, a class (and friends) can always access its own non-inherited members. The access specifiers only affect whether outsiders and derived classes can access those members.

        - Second, when derived classes inherit members, those members may change access specifiers in the derived class. This does not affect the derived classes’ own (non-inherited) members (which have their own access specifiers). It only affects whether outsiders and classes derived from the derived class can access those inherited members.

*/
class Base
{
public:
    int m_public {};
protected:
    int m_protected {};
private:
    int m_private {};
};

class Pub: public Base // note: public inheritance
{
    // Public inheritance means:
    // Public inherited members stay public (so m_public is treated as public)
    // Protected inherited members stay protected (so m_protected is treated as protected)
    // Private inherited members stay inaccessible (so m_private is inaccessible)
public:
    Pub()
    {
        m_public = 1; // okay: m_public was inherited as public
        m_protected = 2; // okay: m_protected was inherited as protected
        m_private = 3; // not okay: m_private is inaccessible from derived class
    }
};

int main()
{
    // Outside access uses the access specifiers of the class being accessed.
    Base base;
    base.m_public = 1; // okay: m_public is public in Base
    // base.m_protected = 2; // not okay: m_protected is protected in Base
    // base.m_private = 3; // not okay: m_private is private in Base

    Pub pub;
    pub.m_public = 1; // okay: m_public is public in Pub
    // pub.m_protected = 2; // not okay: m_protected is protected in Pub
    // pub.m_private = 3; // not okay: m_private is inaccessible in Pub

    return 0;
}
