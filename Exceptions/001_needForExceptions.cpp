#include <iostream>
/* 
    Notes :  
    
    1. When return codes fail : When writing reusable code, error handling is a necessity. One of the most common ways to handle potential errors is via return codes. For example:

        int findFirstChar(std::string_view string, char ch)
        {
            // Step through each character in string
            for (std::size_t index{ 0 }; index < string.length(); ++index)
                // If the character matches ch, return its index
                if (string[index] == ch)
                    return index;

            // If no match was found, return -1
            return -1;
        }

    2. This function returns the index of the first character matching ch within string. If the character can not be found, the function returns -1 as an indicator that the character wasn’t found. The primary virtue of this approach is that it is extremely simple. However, using return codes has a number of drawbacks which can quickly become apparent when used in non-trivial cases:

        1. First, return values can be cryptic -- if a function returns -1, is it trying to indicate an error, or is that actually a valid return value? It’s often hard to tell without digging into the guts of the function or consulting documentation.

        2. Second, functions can only return one value, so what happens when you need to return both a function result and a possible error code? Consider the following function:

            double divide(int x, int y)
            {
                return static_cast<double>(x)/y;
            }

        3. Third, in sequences of code where many things can go wrong, error codes have to be checked constantly. 

        - To summarize, the primary issue with return codes is that the error handling code ends up intricately linked to the normal control flow of the code. This in turn ends up constraining both how the code is laid out, and how errors can be reasonably handled.

    3. Exception handling provides a mechanism to decouple handling of errors or other exceptional circumstances from the typical control flow of your code. This allows more freedom to handle errors when and how ever is most useful for a given situation, alleviating most (if not all) of the messiness that return codes cause. In the next lesson, we’ll take a look at how exceptions work in C++.

        
*/
int main()
{
    return 0;
}