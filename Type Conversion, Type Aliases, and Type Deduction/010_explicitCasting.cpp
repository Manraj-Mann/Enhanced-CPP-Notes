#include <iostream>

/*
    Notes : 

    1. C++ comes with a number of different type casting operators (more commonly called casts) that can be used by the programmer to request that the compiler perform a type conversion. Because casts are explicit requests by the programmer, this form of type conversion is often called an explicit type conversion (as opposed to implicit type conversion, where the compiler performs a type conversion automatically).

    2. C++ supports 5 different types of casts: C-style casts, static casts, const casts, dynamic casts, and reinterpret casts. The latter four are sometimes referred to as named casts.

    => Const casts and reinterpret casts should generally be avoided because they are only useful in rare cases and can be harmful if used incorrectly.

    3. In standard C programming, casts are done via the () operator, with the name of the type to convert the value placed inside the parentheses. You may still see these used in code (or by programmers) that have been converted from C.

        int x { 10 };
        int y { 4 };


        double d { (double)x / y }; // convert x to a double so we get floating point division

    4. C++ will also let you use a C-style cast with a more function-call like syntax:

        double d { double(x) / y }; // convert x to a double so we get floating point division
        
        This performs identically to the prior example, but has the benefit of parenthesizing the value being converted (making it easier to tell what is being converted).

        Although a C-style cast appears to be a single cast, it can actually perform a variety of different conversions depending on context. This can include a static cast, a const cast or a reinterpret cast (the latter two of which we mentioned above you should avoid). As a result, C-style casts are at risk for being inadvertently misused and not producing the expected behavior, something which is easily avoidable by using the C++ casts instead.

        Ever wondered why C-Style casts and reinterpret_cast casts are considered evil? Let’s take an in-depth look at what goes wrong with them.

    5. C++ knows 5 different casts (yeah, C-Style casting is not reinterpret_cast):

        1. static_cast  : Least harmful, can downcast pointers
        2. const_cast   : Removes the const modifier. If used incorrectly, this can be a killer as the target might be really const and you get some invalid access errors.
        3. dynamic_cast : Safe down/cross-casting between classes, requires RTTI - and RTTI in C++ is something that is often not enabled at all.
        4. reinterpret_cast: Casts anything which has the same size, for example, int to FancyClass* on x86. Now this is not really a cast any more but just a way to tell the compiler to throw away type information and treat the data differently.
        5. C-Style casting, using the (type)variable syntax. The worst ever invented. This tries to do the following casts, in this order: 

            - const_cast
            - static_cast
            - static_cast followed by const_cast
            - reinterpret_cast
            - reinterpret_castfollowed by const_cast

        And you thought it is just a single evil cast, in fact its a hydra!

    6. The rule of the thumb should be: Never use reinterpret_cast or C-Style casting, if you need to cast pointers, cast them via void*, and only if absolutely necessary use reinterpret_cast - that means, if you really have to reinterpret the data. Remember, C++ is an expert language, it gives you all the control over your machine you wish, but with power comes responsibility!

    7. static_cast - C++ introduces a casting operator called static_cast, which can be used to convert a value of one type to a value of another type.

    The static_cast operator takes an expression as input, and returns the evaluated value converted to the type specified inside the angled brackets. static_cast is best used to convert one fundamental type into another.

    8. The main advantage of static_cast is that it provides compile-time type checking, making it harder to make an inadvertent error. static_cast is also (intentionally) less powerful than C-style casts, so you can’t inadvertently remove const or do other things you may not have intended to do.

        const int x{ 5 };
        int& ref{ static_cast<int&>(x) }; // invalid: will produce compilation error
        ref = 6;

    9. Using static_cast to make narrowing conversions explicit 

    // explicit conversion from int to char, so that a char is assigned to variable ch
    char ch { static_cast<char>(i) };







*/
int main()
{
    
    return 0;
}