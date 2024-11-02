#include <iostream>
/* 
    Notes :  
    
    1. Command line arguments are optional string arguments that are passed by the operating system to the program when it is launched. The program can then use them as input (or ignore them). Much like function parameters provide a way for a function to provide inputs to another function, command line arguments provide a way for people or programs to provide inputs to a program.

    2. Passing command line arguments - Executable programs can be run on the command line by invoking them by name.

    3. Using command line arguments - Now that you know how to provide command line arguments to a program, the next step is to access them from within our C++ program. To do that, we use a different form of main() than we’ve seen before. This new form of main() takes two arguments (named argc and argv by convention) as follows:

        => int main(int argc, char* argv[])

        => int main(int argc, char** argv)

        - argc is an integer parameter containing a count of the number of arguments passed to the program (think: argc = argument count). argc will always be at least 1, because the first argument is always the name of the program itself. Each command line argument the user provides will cause argc to increase by 1.

        - argv is where the actual argument values are stored (think: argv = argument values, though the proper name is “argument vectors”). Although the declaration of argv looks intimidating, argv is really just a C-style array of char pointers (each of which points to a C-style string). The length of this array is argc.

    4. Dealing with numeric arguments -Command line arguments are always passed as strings, even if the value provided is numeric in nature. To use a command line argument as a number, you must convert it from a string to a number. Unfortunately, C++ makes this a little more difficult than it should be.

        - Example : 

        	if (argc <= 1)
            {
                // On some operating systems, argv[0] can end up as an empty string instead of the program's name.
                // We'll conditionalize our response on whether argv[0] is empty or not.
                if (argv[0])
                    std::cout << "Usage: " << argv[0] << " <number>" << '\n';
                else
                    std::cout << "Usage: <program name> <number>" << '\n';

                return 1;
            }

            std::stringstream convert{ argv[1] }; // set up a stringstream variable named convert, initialized with the input from argv[1]

            int myint{};
            if (!(convert >> myint)) // do the conversion
                myint = 0; // if conversion fails, set myint to a default value

            std::cout << "Got integer: " << myint << '\n'; 
        
        - std::stringstream works much like std::cin. In this case, we’re initializing it with the value of argv[1], so that we can use operator>> to extract the value to an integer variable (the same as we would with std::cin).

    5. The OS parses command line arguments first - 

        - When you type something at the command line (or run your program from the IDE), it is the operating system’s responsibility to translate and route that request as appropriate. This not only involves running the executable, it also involves parsing any arguments to determine how they should be handled and passed to the application.

        - Generally, operating systems have special rules about how special characters like double quotes and backslashes are handled.
    
    6. Command line arguments provide a great way for users or other programs to pass input data into a program at startup. Consider making any input data that a program requires at startup to operate a command line parameter. If the command line isn’t passed in, you can always detect that and ask the user for input. That way, your program can operate either way.

*/

#include <sstream> // for std::stringstream
#include <string>

int main(int argc, char* argv[])
{
    std::cout << "There are " << argc << " arguments:\n";

    // Loop through each argument and print its number and value
    for (int count{ 0 }; count < argc; ++count)
    {
        std::cout << count << ' ' << argv[count] << '\n';
    }

    if (argc <= 1)
	{
		// On some operating systems, argv[0] can end up as an empty string instead of the program's name.
		// We'll conditionalize our response on whether argv[0] is empty or not.
		if (argv[0])
			std::cout << "Usage: " << argv[0] << " <number>" << '\n';
		else
			std::cout << "Usage: <program name> <number>" << '\n';

		return 1;
	}

	std::stringstream convert{ argv[1] }; // set up a stringstream variable named convert, initialized with the input from argv[1]

	int myint{};
	if (!(convert >> myint)) // do the conversion
		myint = 0; // if conversion fails, set myint to a default value

	std::cout << "Got integer: " << myint << '\n';

    return 0;
}