#include <iostream>

/*

    Notes : 

    1. Qualified and unqualified names : 

        +> A qualified name is a name that includes an associated scope. Most often, names are qualified with a namespace using the scope resolution operator (::). For example:

            std::cout // identifier cout is qualified by namespace std
            ::foo // identifier foo is qualified by the global namespace

            A name can also be qualified by a class name using the scope resolution operator (::), or by a class object using the member selection operators (. or ->)
    
        +> An unqualified name is a name that does not include a scoping qualifier. For example, cout and x are unqualified names, as they do not include an associated scope.

    2. Using-declarations : A using declaration allows us to use an unqualified name (with no scope) as an alias for a qualified name.

        using std::cout; // this using declaration tells the compiler that cout should resolve to std::cout
        cout << "Hello world!\n"; // so no std:: prefix is needed here!
      
        The using-declaration is active from the point of declaration to the end of the scope in which it is declared.

    3. Using-directives :  A using directive allows all identifiers in a given namespace to be referenced without qualification from the scope of the using-directive.

        using namespace std; // all names from std namespace now accessible without qualification
        cout << "Hello world!\n"; // so no std:: prefix is needed here

    4. Problems with using-directives (a.k.a. why you should avoid “using namespace std;”) : 

        In modern C++, using-directives generally offer little benefit (saving some typing) compared to the risk. This is due to two factors:

        => Using-directives allow unqualified access to all of the names from a namespace (potentially including lots of names you’ll never use).
        
        => Using-directives do not prefer names from the namespace of the using-directive over other names.

    5. If a using-declaration or using-directive is used within a block, the names are applicable to just that block (it follows normal block scoping rules). This is a good thing, as it reduces the chances for naming collisions to occur to just within that block.

    




*/
int main()
{
    return 0;
}