#include <iostream>
#include <string_view>

/*

Note:

1. C++ has introduced two additional string types into the language that are much easier and safer to work with: std::string and std::string_view (C++17).

2. std::string and std::string_view aren’t fundamental types (they’re class types, which we’ll cover in the future). However, basic usage of each is straightforward and useful enough that we’ll introduce them here.

3. If std::string doesn’t have enough memory to store a string, it will request additional memory (at runtime) using a form of memory allocation known as dynamic memory allocation. This ability to acquire additional memory is part of what makes std::string so flexible, but also comparatively slow.

It turns out that when using operator>> to extract a string from std::cin, operator>> only returns characters up to the first whitespace it encounters. Any other characters are left inside std::cin, waiting for the next extraction.

4. Use std::getline() to input text : To read a full line of input into a string, you’re better off using the std::getline() function instead. std::getline() requires two arguments: the first is std::cin, and the second is your string variable.

std::cout << "Enter your full name: ";
std::string name{};
std::getline(std::cin >> std::ws, name); // read a full line of text into name

C++ also supports input manipulators, which alter the way that input is accepted. The std::ws input manipulator tells std::cin to ignore any leading whitespace before extraction. Leading whitespace is any whitespace character (spaces, tabs, newlines) that occur at the start of the string.

5. The length of a std::string : If we want to know how many characters are in a std::string, we can ask a std::string object for its length. The syntax for doing this is different than you’ve seen before, but is pretty straightforward.

6. Also note that std::string::length() returns an unsigned integral value (most likely of type size_t). If you want to assign the length to an int variable, you should static_cast it to avoid compiler warnings about signed/unsigned conversions:

int length { static_cast<int>(name.length()) };
In C++20, you can also use the std::ssize() function to get the length of a std::string as a large signed integral type (usually std::ptrdiff_t):

7. When a std::string is passed to a function by value, the std::string function parameter must be instantiated and initialized with the argument. This results in an expensive copy. We’ll discuss what to do instead (use std::string_view)When a function returns by value to the caller, the return value is normally copied from the function back to the caller. So you might expect that you should not return std::string by value, as doing so would return an expensive copy of a std::string.

8. std::string supports a capability called move semantics, which allows an object that will be destroyed at the end of the function to instead be returned by value without making a copy.

9. Constexpr strings : If you try to define a constexpr std::string, your compiler will probably generate an error.This happens because constexpr std::string isn’t supported at all in C++17 or earlier, and only works in very limited cases in C++20/23. If you need constexpr strings, use std::string_view instead.

10. std::string_view C++17 : To address the issue with std::string being expensive to initialize (or copy), C++17 introduced std::string_view (which lives in the <string_view> header). std::string_view provides read-only access to an existing string (a C-style string, a std::string, or another std::string_view) without making a copy. Read-only means that we can access and use the value being viewed, but we can not modify it.

// str provides read-only access to whatever argument is passed in
void printSV(std::string_view str) // now a std::string_view
{
    std::cout << str << '\n';
}

int main()
{
    std::string_view s{ "Hello, world!" }; // now a std::string_view
    printSV(s);

    return 0;
}

Prefer std::string_view over std::string when you need a read-only string, especially for function parameters.


11 . Some facts about string_view : 

    1. One of the neat things about a std::string_view is how flexible it is. A std::string_view object can be initialized with a C-style string, a std::string, or another std::string_view
    2. Both a C-style string and a std::string will implicitly convert to a std::string_view. Therefore, a std::string_view parameter will accept arguments of type C-style string, a std::string, or std::string_view:
    3. std::string_view will not implicitly convert to std::string
        However, if this is desired, we have two options:

        1. Explicitly create a std::string with a std::string_view initializer (which is allowed, since this will rarely be done unintentionally)
        2. Convert an existing std::string_view to a std::string using static_cast
    4. Assigning a new string to a std::string_view causes the std::string_view to view the new string. It does not modify the prior string being viewed in any way.

        std::string name { "Alex" };
        std::string_view sv { name }; // sv is now viewing name
        std::cout << sv << '\n'; // prints Alex

        sv = "John"; // sv is now viewing "John" (does not change name)
        std::cout << sv << '\n'; // prints John

        std::cout << name << '\n'; // prints Alex

    5. constexpr std::string_view: Unlike std::string, std::string_view has full support for constexpr:

        constexpr std::string_view s{ "Hello, world!" }; // s is a string symbolic constant
        std::cout << s << '\n'; // s will be replaced with "Hello, world!" at compile-time

    This makes constexpr std::string_view the preferred choice when string symbolic constants are needed.

12. Ownership can be expensive. As an owner, it is your responsibility to acquire, manage, and properly dispose of the objects you own.Viewing is inexpensive. As a viewer, you have no responsibility for the objects you are viewing, but you also have no control over those objects.

    1. std::string is an owner : why std::string makes an expensive copy of its initializer.

        When an object is instantiated, memory is allocated for that object to store whatever data it needs to use throughout its lifetime. This memory is reserved for the object, and guaranteed to exist for as long as the object does. It is a safe space. std::string (and most other objects) copy the initialization value they are given into this memory so that they can have their own independent value to access and manipulate later. Once the initialization value has been copied, the object is no longer reliant on the initializer in any way.

        Because the initializer generally can’t be trusted after initialization is complete. If you imagine the initialization process as a function call that initializes the object, who is passing in the initializer? The caller. When initialization is done, control returns back to the caller. At this point, the initialization statement is complete, and one of two things will typically happen:

            1. If the initializer was a temporary value or object, that temporary will be destroyed immediately.
            2. If the initializer was a variable, the caller still has access to that object. The caller can then do whatever it wants with the object, including modify or destroy it.

    2. std::string_view is a viewer : std::string_view takes a different approach to initialization. Instead of making an expensive copy of the initialization string, std::string_view creates an inexpensive view of the initialization string. The std::string_view can then be used whenever access to the string is required.

    Warning : A view is dependent on the object being viewed. If the object being viewed is modified or destroyed while the view is still being used, unexpected or undefined behavior will result.

    A std::string_view that is viewing a string that has been destroyed is sometimes called a dangling view.

13. Should I prefer std::string_view or const std::string& function parameters?  Prefer std::string_view in most cases.

14. Improperly using std::string_view:

    1. Case 1:

        std::string_view sv{};

        { // create a nested block
            std::string s{ "Hello, world!" }; // create a std::string local to this nested block
            sv = s; // sv is now viewing s
        } // s is destroyed here, so sv is now viewing an invalid string

        std::cout << sv << '\n'; // undefined behavior

    2. Case 2:
    
        std::string getName()
        {
            std::string s { "Alex" };
            return s;
        }

        int main()
        {
            std::string_view name { getName() }; // name initialized with return value of function
            std::cout << name << '\n'; // undefined behavior
            return 0;
        }

    3. Case 3 :
    
        using namespace std::string_literals;
        std::string_view name { "Alex"s }; // "Alex"s creates a temporary std::string
        std::cout << name << '\n'; // undefined behavior
        Do not initialize a std::string_view with a std::string literal, as this will leave the std::string_view dangling.

    4. Modifying a std::string invalidates all views into that std::string.

        std::string s { "Hello, world!" };
        std::string_view sv { s }; // sv is now viewing s

        s = "Hello, universe!";    // modifies s, which invalidates sv (s is still valid)
        std::cout << sv << '\n';   // undefined behavior

        Solution : Revalidating an invalid std::string_view (sv = s)

15. std::string_view can view a substring

This brings up an important use of std::string_view. While std::string_view can be used to view an entire string without making a copy, they are also useful when we want to view a substring without making a copy. A substring is a contiguous sequence of characters within an existing string. For example, given the string “snowball”, some substrings are “snow”, “all”, and “now”. “owl” is not a substring of “snowball” because these characters do not appear contiguously in “snowball”.

A C-style string literal and a std::string are always null-terminated.
A std::string_view may or may not be null-terminated.


*/

void printSV(std::string_view str) // now a std::string_view
{
    std::cout << str << '\n';
}
int main()
{

    std::string_view s{ "Hello, world!" }; // now a std::string_view
    printSV(s);

    std::string_view sv{};

    { // create a nested block
        std::string s{ "Hello, world!" }; // create a std::string local to this nested block
        sv = s; // sv is now viewing s
    } // s is destroyed here, so sv is now viewing an invalid string

    std::cout << sv << '\n'; // undefined behavior
    return 0;
}