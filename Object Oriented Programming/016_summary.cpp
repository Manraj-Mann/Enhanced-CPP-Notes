#include <iostream>
/* 
    Notes :  
    
    1. In procedural programming, the focus is on creating “procedures” (which in C++ are called functions) that implement our program logic. We pass data objects to these functions, those functions perform operations on the data, and then potentially return a result to be used by the caller.

    2. With Object-oriented programming (often abbreviated as OOP), the focus is on creating program-defined data types that contain both properties and a set of well-defined behaviors.

    3. A class invariant is a condition that must be true throughout the lifetime of an object in order for the object to remain in a valid state. An object that has a violated class invariant is said to be in an invalid state, and unexpected or undefined behavior may result from further use of that object.

    4. A class is a program-defined compound type that bundles both data and functions that work on that data.

    Functions that belong to a class type are called member functions. The object that a member function is called on is often called the implicit object. Functions that are not member functions are called non-member functions to distinguish them from member functions. If your class type has no data members, prefer using a namespace instead.

    5. A const member function is a member function that guarantees it will not modify the object or call any non-const member functions (as they may modify the object). A member function that does not (and will not ever) modify the state of the object should be made const, so that it can be called on both non-const and const objects.

    6. Each member of a class type has a property called an access level that determines who can access that member. The access level system is sometimes informally called access controls. Access levels are defined on a per-class basis, not on a per-object basis.

    7. Public members are members of a class type that do not have any restrictions on how they can be accessed. Public members can be accessed by anyone (as long as they are in scope). This includes other members of the same class. Public members can also be accessed by the public, which is what we call code that exists outside the members of a given class type. Examples of the public include non-member functions, as well as the members of other class types.

    8. By default, all members of a struct are public members.

    9. Private members are members of a class type that can only be accessed by other members of the same class.

    10. By default, the members of a class are private. A class with private members is no longer an aggregate, and therefore can no longer use aggregate initialization. Consider naming your private members starting with an “m_” prefix to help distinguish them from the names of local variables, function parameters, and member functions.

    11. We can explicitly set the access level of our members by using an access specifier. Structs should generally avoid using access specifiers so all members default to public.

    12. An access function is a trivial public member function whose job is to retrieve or change the value of a private member variable. Access functions come in two flavors: getters and setters. Getters (also sometimes called accessors) are public member functions that return the value of a private member variable. Setters (also sometimes called mutators) are public member functions that set the value of a private member variable.

    13. The interface of a class type defines how a user of the class type will interact with objects of the class type. Because only public members can be accessed from outside of the class type, the public members of a class type form its interface. For this reason, an interface composed of public members is sometimes called a public interface.

    14. The implementation of a class type consists of the code that actually makes the class behave as intended. This includes both the member variables that store data, and the bodies of the member functions that contain the program logic and manipulate the member variables.

    15. In programming, data hiding (also called information hiding or data abstraction) is a technique used to enforce the separation of interface and implementation by hiding the implementation of a program-defined data type from users.

    16. The term encapsulation is also sometimes used to refer to data hiding. However, this term is also used to refer to the bundling of data and functions together (without regard for access controls), so its use can be ambiguous.

    17. When defining a class, prefer to declare your public members first and your private members last. This spotlights the public interface and de-emphasizes implementation details.

    18. A constructor is a special member function that is used to initialize class type objects. A matching constructor must be found in order to create a non-aggregate class type object.

    19. A Member initializer list allows you to initialize your member variables from within a constructor. Member variables in a member initializer list should be listed in order that they are defined in the class. Prefer using the member initializer list to initialize your members over assigning values in the body of the constructor.

    20. A constructor that takes no parameters (or has all default parameters) is called a default constructor. The default constructor is used if no initialization values are provided by the user. If a non-aggregate class type object has no user-declared constructors, the compiler will generate a default constructor (so that the class can be value or default initialized). This constructor is called an implicit default constructor.

    21. Constructors are allowed to delegate initialization to another constructor from the same class type. This process is sometimes called constructor chaining and such constructors are called delegating constructors. Constructors can delegate or initialize, but not both.

    22. A temporary object (sometimes called an anonymous object or an unnamed object) is an object that has no name and exists only for the duration of a single expression.

    23. A copy constructor is a constructor that is used to initialize an object with an existing object of the same type. If you do not provide a copy constructor for your classes, C++ will create a public implicit copy constructor for you that does memberwise initialization.

    24. The as-if rule says that the compiler can modify a program however it likes in order to produce more optimized code, so long as those modifications do not affect a program’s “observable behavior”. One exception to the as-if rule is copy elision. Copy elision is a compiler optimization technique that allows the compiler to remove unnecessary copying of objects. When the compiler optimizes away a call to the copy constructor, we say the constructor has been elided.

    25. A function that we’ve written to convert a value to or from a program-defined type is called a user-defined conversion. A constructor that can be used to perform an implicit conversion is called a converting constructor. By default, all constructors are converting constructors.

    26. We can use the explicit keyword to tell the compiler that a constructor should not be used as a converting constructor. Such a constructor can not be used to do copy initialization or copy list initialization, nor can it be used to do implicit conversions.

    27. Make any constructor that accepts a single argument explicit by default. If an implicit conversion between types is both semantically equivalent and performant (such as a conversion from std::string to std::string_view), you can consider making the constructor non-explicit. Do not make copy or move constructors explicit, as these do not perform conversions.

    28. Member functions (including constructors) may be constexpr. As of C++14, constexpr member functions are not implicitly const.

*/
int main()
{
    return 0;
}