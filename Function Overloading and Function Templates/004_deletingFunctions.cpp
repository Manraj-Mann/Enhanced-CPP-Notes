#include <iostream>

/*
    Notes : 

    1. Deleting a function using the = delete specifier - 

        In cases where we have a function that we explicitly do not want to be callable, we can define that function as deleted by using the = delete specifier. If the compiler matches a function call to a deleted function, compilation will be halted with a compile error.

        void printInt(int x)
        {
            std::cout << x << '\n';
        }

        void printInt(char) = delete; // calls to this function will halt compilation
        void printInt(bool) = delete; // calls to this function will halt compilation

        int main()
        {
            printInt(97);   // okay

            printInt('a');  // compile error: function deleted
            printInt(true); // compile error: function deleted

            printInt(5.0);  // compile error: ambiguous match

            return 0;
        }

    2. = delete means “I forbid this”, not “this doesn’t exist”.

        Deleted function participate in all stages of function overload resolution (not just in the exact match stage). If a deleted function is selected, then a compilation error results.

    3. Deleting all non-matching overloads - 

        Deleting a bunch of individual function overloads works fine, but can be verbose. There may be times when we want a certain function to be called only with arguments whose types exactly match the function parameters. 

        // This function will take precedence for arguments of type int
        void printInt(int x)
        {
            std::cout << x << '\n';
        }

        // This function template will take precedence for arguments of other types
        // Since this function template is deleted, calls to it will halt compilation
        template <typename T>
        void printInt(T x) = delete;

*/


void printInt(int x)
{
    std::cout << x << '\n';
}

void printInt(char) = delete; // calls to this function will halt compilation
void printInt(bool) = delete; // calls to this function will halt compilation

int main()
{
    printInt(97);   // okay

    // printInt('a');  // compile error: function deleted
    // printInt(true); // compile error: function deleted

    // printInt(5.0);  // compile error: ambiguous match

    return 0;
}