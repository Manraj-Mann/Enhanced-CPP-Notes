#include <iostream>
/* 
    Notes :  
    
    1. In procedural programming, the focus is on creating “procedures” (which in C++ are called functions) that implement our program logic. We pass data objects to these functions, those functions perform operations on the data, and then potentially return a result to be used by the caller.

    2. In object-oriented programming (often abbreviated as OOP), the focus is on creating program-defined data types that contain both properties and a set of well-defined behaviors. The term “object” in OOP refers to the objects that we can instantiate from such types.

    3. The term “object” - term “object” is overloaded a bit, and this causes some amount of confusion. In traditional programming, an object is a piece of memory to store values. And that’s it. In object-oriented programming, an “object” implies that it is both an object in the traditional programming sense, and that it combines both properties and behaviors. We will favor the traditional meaning of the term object in these tutorials, and prefer the term “class object” when specifically referring to OOP objects.

    4. The class invariant problem : In the context of class types (which include structs, classes, and unions), a class invariant is a condition that must be true throughout the lifetime of an object in order for the object to remain in a valid state. An object that has a violated class invariant is said to be in an invalid state, and unexpected or undefined behavior may result from further use of that object.

    Using an object whose class invariant has been violated may result in unexpected or undefined behavior.
    
    5. Now consider the following almost-identical struct:

        struct Fraction
        {
            int numerator { 0 };
            int denominator { 1 };
        };

        We know from mathematics that a fraction with a denominator of 0 is mathematically undefined (because the value of a fraction is its numerator divided by its denominator -- and division by 0 is mathematically undefined). Therefore, we want to ensure the denominator member of a Fraction object is never set to 0. If it is, then that Fraction object is in an invalid state, and undefined behavior may result from further use of that object.

    6. A more complex class invariant - The class invariant for Fraction is a simple one -- the denominator member cannot be 0. That’s conceptually easy to understand and not overly difficult to avoid.

        Class invariants become more of a challenge when the members of a struct must have correlated values.

        #include <string>

        struct Employee
        {
            std::string name { };
            char firstInitial { }; // should always hold first character of `name` (or `0`)
        };
        In the above (poorly designed) struct, the character value stored in member firstInitial should always match the first character of name.

    7. Relying on the user of an object to maintain class invariants is likely to result in problems.

    8. Just like structs, a class is a program-defined compound type that can have many member variables with different types.Because a class is a program-defined data type, it must be defined before it can be used. Classes are defined similarly to structs, except we use the class keyword instead of struct. For example, here is a definition for a simple employee class:

        class Employee
        {
            int m_id {};
            int m_age {};
            double m_wage {};
        };


*/
int main()
{
    return 0;
}