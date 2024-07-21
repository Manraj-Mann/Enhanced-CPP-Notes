#include <iostream>


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


*/
int main()
{

    return 0;
}