#include <iostream>

/*
    Notes : 

    1. int getVal(); // some function that returns an int by value
        auto val { getVal() }; // val deduced as type int

    2. We also noted that by default, type deduction will drop const (and constexpr) qualifiers:

        const double foo()
        {
            return 5.6;
        }

        const double cd{ 7.8 };

        auto x{ cd };    // double (const dropped)
        auto y{ foo() }; // double (const dropped)

    3. Const (or constexpr) can be (re)applied by adding the const (or constexpr) qualifier in the definition:

        const double foo()
        {
            return 5.6;
        }

        constexpr double cd{ 7.8 };

        const auto x{ foo() };  // const double (const dropped, const reapplied)
        constexpr auto y{ cd }; // constexpr double (constexpr dropped, constexpr reapplied)
        const auto z { cd };    // const double (constexpr dropped, const applied)

    4. Type deduction drops references - In addition to dropping const/constexpr qualifiers, type deduction will also drop references:

        std::string& getRef(); // some function that returns a reference

        auto ref { getRef() }; // type deduced as std::string (not std::string&)

        Just like with the dropped const qualifier, if you want the deduced type to be a reference, you can reapply the reference at the point of definition:

        auto& ref2 { getRef() }; // std::string& (reference reapplied)

    5. Top-level const and low-level const - 

        1. A top-level const is a const qualifier that applies to an object itself. For example:

            - const int x;    // this const applies to x, so it is top-level
            - int* const ptr; // this const applies to ptr, so it is top-level

        2. In contrast, a low-level const is a const qualifier that applies to the object being referenced or pointed to: 

            - const int& ref; // this const applies to the object being referenced, so it is low-level
            - const int* ptr; // this const applies to the object being pointed to, so it is low-level

        A reference to a const value is always a low-level const. A pointer can have a top-level, low-level, or both kinds of const:

        - const int* const ptr; // the left const is low-level, the right const is top-level
        
        When we say that type deduction drops const qualifiers, it only drops top-level consts. Low-level consts are not dropped. We’ll see examples of this in just a moment.

    6. Type deduction and const references - If the initializer is a reference to const (or constexpr), the reference is dropped first (and then reapplied if applicable), and then any top-level const or constexpr is dropped from the result.

        - const std::string& getConstRef(); // some function that returns a reference to const

        - auto ref1{ getConstRef() }; // std::string (reference dropped, then top-level const dropped from result)

        In the above example, since getConstRef() returns a const std::string&, the reference is dropped first, leaving us with a const std::string. This const is now a top-level const, so it is also dropped, leaving the deduced type as std::string.

        - Dropping a reference may change a low-level const to a top-level const: const std::string& is a low-level const, but dropping the reference yields const std::string, which is a top-level const.

        const std::string& getConstRef(); // some function that returns a const reference

        int main()
        {
            auto ref1{ getConstRef() };        // std::string (reference and top-level const dropped)
            const auto ref2{ getConstRef() };  // const std::string (reference dropped, const reapplied)

            auto& ref3{ getConstRef() };       // const std::string& (reference reapplied, low-level const not dropped)
            const auto& ref4{ getConstRef() }; // const std::string& (reference reapplied, low-level const not dropped)

            return 0;
        }

        - We covered the case for ref1 in the prior example. For ref2, this is similar to the ref1 case, except we’re reapplying the const qualifier, so the deduced type is const std::string.

        - Things get more interesting with ref3. Normally the reference would be dropped first, but since we’ve reapplied the reference, it is not dropped. That means the type is still const std::string&. And since this const is a low-level const, it is not dropped. Thus the deduced type is const std::string&.

        - The ref4 case works similarly to ref3, except we’ve reapplied the const qualifier as well. Since the type is already deduced as a reference to const, us reapplying const here is redundant. That said, using const here makes it explicitly clear that our result will be const (whereas in the ref3 case, the constness of the result is implicit and not obvious).

        => If you want a const reference, reapply the const qualifier even when it’s not strictly necessary, as it makes your intent clear and helps prevent mistakes.

    7. What about constexpr references?

        - Constexpr is not part of an expression’s type, so it is not deduced by auto.

        - When defining a const reference (e.g. const int&), the const applies to the object being referenced, not the reference itself.

        - When defining a constexpr reference to a const variable (e.g. constexpr const int&), we need to apply both constexpr (which applies to the reference) and const (which applies to the type being referenced).

        - When defining a const reference (e.g. const int&), the const applies to the object being referenced, not the reference itself.

        - When defining a constexpr reference to a const variable (e.g. constexpr const int&), we need to apply both constexpr (which applies to the reference) and const (which applies to the type being referenced).

        constexpr std::string_view hello { "Hello" };   // implicitly const

        constexpr const std::string_view& getConstRef() // function is constexpr, returns a const std::string_view&
        {
            return hello;
        }

        int main()
        {
            auto ref1{ getConstRef() };                  // std::string_view (reference dropped and top-level const dropped)
            constexpr auto ref2{ getConstRef() };        // constexpr const std::string_view (reference dropped and top-level const dropped, constexpr reapplied)

            auto& ref3{ getConstRef() };                 // const std::string_view& (reference reapplied, low-level const not dropped)
            constexpr const auto& ref4{ getConstRef() }; // constexpr const std::string_view& (reference reapplied, low-level const not dropped, constexpr reapplied)

            return 0;
        }

    8. Type deduction and pointers - Unlike references, type deduction does not drop pointers: 

        std::string* getPtr(); // some function that returns a pointer

        int main()
        {
            auto ptr1{ getPtr() }; // std::string*

            return 0;
        }

        We can also use an asterisk in conjunction with pointer type deduction (auto*) to make it clearer that the deduced type is a pointer:

        std::string* getPtr(); // some function that returns a pointer

        int main()
        {
            auto ptr1{ getPtr() };  // std::string*
            auto* ptr2{ getPtr() }; // std::string*

            return 0;
        }

    9. Key insight - 

        - The reason that references are dropped during type deduction but pointers are not dropped is because references and pointers have different semantics.

        - When we evaluate a reference, we’re really evaluating the object being referenced. Therefore, when deducing a type, it makes sense that we should deduce the type of the thing being referenced, not the reference itself. Also, since we deduce a non-reference, it’s really easy to make it a reference by using auto&. If type deduction were to deduce a reference instead, the syntax for removing a reference if we didn’t want it is much more complicated.

        - On the other hand, pointers hold the address of an object. When we evaluate a pointer, we are evaluating the pointer, not the object being pointed to (if we want that, we can dereference the pointer). Therefore, it makes sense that we should deduce the type of the pointer, not the thing being pointed to.

    10. The difference between auto and auto*  - 

        When we use auto with a pointer type initializer, the type deduced for auto includes the pointer. So for ptr1 above, the type substituted for auto is std::string*.

        When we use auto* with a pointer type initializer, the type deduced for auto does not include the pointer -- the pointer is reapplied afterward after the type is deduced. So for ptr2 above, the type substituted for auto is std::string, and then the pointer is reapplied.

    11. Type deduction and const pointers - If you want a const pointer, pointer to const, or const pointer to const, reapply the const qualifier(s) even when it’s not strictly necessary, as it makes your intent clear and helps prevent mistakes.

        std::string* getPtr(); // some function that returns a pointer

        int main()
        {
            const auto ptr1{ getPtr() };  // std::string* const
            auto const ptr2 { getPtr() }; // std::string* const

            const auto* ptr3{ getPtr() }; // const std::string*
            auto* const ptr4{ getPtr() }; // std::string* const

            return 0;
        }

        When we use either auto const or const auto, we’re saying, “make whatever the deduced type is const”. So in the case of ptr1 and ptr2, the deduced type is std::string*, and then const is applied, making the final type std::string* const. This is similar to how const int and int const mean the same thing.

        However, when we use auto*, the order of the const qualifier matters. A const on the left means “make the deduced pointer type a pointer to const”, whereas a const on the right means “make the deduced pointer type a const pointer”. Thus ptr3 ends up as a pointer to const, and ptr4 ends up as a const pointer.



*/


const std::string& getConstRef(); // some function that returns a const reference

const std::string& getConstRef()
{
    const static std::string s = std::string("Hello");
    return s;
}

int main()
{
    auto ref1{ getConstRef() };        // std::string (reference and top-level const dropped)
    const auto ref2{ getConstRef() };  // const std::string (reference dropped, const reapplied)

    auto& ref3{ getConstRef() };       // const std::string& (reference reapplied, low-level const not dropped)
    const auto& ref4{ getConstRef() }; // const std::string& (reference reapplied, low-level const not dropped)


    std::cout<<"Ref 1 - "<<ref1<<std::endl;
    std::cout<<"Ref 2 - "<<ref2<<std::endl;
    std::cout<<"Ref 3 - "<<ref3<<std::endl;
    std::cout<<"Ref 4 - "<<ref4<<std::endl;

    return 0;
}

