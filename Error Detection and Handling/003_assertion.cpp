/*

    Notes : 


    1. Preconditions, invariants, and postconditions

        1.1. a precondition is any condition that must be true prior to the execution of some section of code

            => Preconditions for a function are best placed at the top of a function, using an early return to return back to the caller if the precondition isn’t met. For example:

            void printDivision(int x, int y)
            {
                if (y == 0) // handle
                {
                    std::cerr << "Error: Could not divide by zero\n";
                    return; // bounce the user back to the caller
                }

                // We now know that y != 0
                std::cout << static_cast<double>(x) / y;
            }
            This is sometimes known as the “bouncer pattern”.

        1.2. An invariant is a condition that must be true while some section of code is executing. This is often used with loops, where the loop body will only execute so long as the invariant is true.

        1.3. Similarly, a postcondition is something that must be true after the execution of some section of code. Our function doesn’t have any postconditions.

    2. An assertion is an expression that will be true unless there is a bug in the program. If the expression evaluates to true, the assertion statement does nothing. If the conditional expression evaluates to false, an error message is displayed and the program is terminated (via std::abort). This error message typically contains the expression that failed as text, along with the name of the code file and the line number of the assertion.

    3. When an assertion evaluates to false, your program is immediately stopped. This gives you an opportunity to use debugging tools to examine the state of your program and determine why the assertion failed. Working backwards, you can then find and fix the issue.

    4. In C++, runtime assertions are implemented via the assert preprocessor macro, which lives in the <cassert> header.

    5. Although we told you previously to avoid preprocessor macros, asserts are one of the few preprocessor macros that are considered acceptable to use. We encourage you to use assert statements liberally throughout your code.

    6. Making your assert statements more descriptive - 

        Don't : assert(found);

        Do : assert(found && "Car could not be found in database");

        A string literal always evaluates to Boolean true. So if found is false, false && true is false. If found is true, true && true is true. Thus, logical AND-ing a string literal doesn’t impact the evaluation of the assert.

    7. Asserts vs error handling: 

        The goal of an assertion is to catch programming errors by documenting something that should never happen. 
        
        If that thing does happen, then the programmer made an error somewhere, and that error can be identified and fixed. Assertions do not allow recovery from errors (after all, if something should never happen, there’s no need to recover from it), and the program will not produce a friendly error message.

        On the other hand, error handling is designed to gracefully handle cases that could happen (however rarely) in release configurations. These may or may not be recoverable, but one should always assume a user of the program may encounter them.

    8. NDEBUG : 

        => The assert macro comes with a small performance cost that is incurred each time the assert condition is checked. Furthermore, asserts should (ideally) never be encountered in production code (because your code should already be thoroughly tested).

        => C++ comes with a way to turn off asserts in production code. If the macro NDEBUG is defined, the assert macro gets disabled.

        // Disable assertions
        #define NDEBUG
        #include <cassert>  // Re-include to apply NDEBUG

        assert(y != 0);  // This assertion is ignored because NDEBUG is defined

        // Re-enable assertions
        #undef NDEBUG
        #include <cassert>  // Re-include to apply the change

        assert(x != 10);  // This assertion will be checked and will fail

    => Use ir in CMake : 

        # Check the build type and define NDEBUG for release builds
        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            target_compile_definitions(my_program PRIVATE NDEBUG)
        else()
            # Optionally add definitions or flags for debug builds
            message(STATUS "Assertions are enabled (NDEBUG not defined).")
        endif()

    9. Some assert limitations and warnings : 

        Also note that the abort() function terminates the program immediately, without a chance to do any further cleanup (e.g. close a file or database). Because of this, asserts should be used only in cases where corruption isn’t likely to occur if the program terminates unexpectedly.

    10. static_assert - 

        A static_assert is an assertion that is checked at compile-time rather than at runtime, with a failing static_assert causing a compile error. Unlike assert, which is declared in the <cassert> header, static_assert is a keyword, so no header needs to be included to use it.

        A static_assert takes the following form: -> static_assert(condition, diagnostic_message)

        If the condition is not true, the diagnostic message is printed. Here’s an example of using static_assert to ensure types have a certain size:

            static_assert(sizeof(long) == 8, "long must be 8 bytes");
            static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

    11. A few useful notes about static_assert:

        - Because static_assert is evaluated by the compiler, the condition must be a constant expression.
        - static_assert can be placed anywhere in the code file (even in the global namespace).
        - static_assert is not deactivated in release builds (like normal assert is).


    


*/


#include <cassert> // for assert()
#include <cmath> // for std::sqrt
#include <iostream>

double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity)
{
  assert(gravity > 0.0); // The object won't reach the ground unless there is positive gravity.

  if (initialHeight <= 0.0)
  {
    // The object is already on the ground. Or buried.
    return 0.0;
  }

  return std::sqrt((2.0 * initialHeight) / gravity);
}

int main()
{
    // std::cout << "Took " << calculateTimeUntilObjectHitsGround(100.0, -9.8) << " second(s)\n";
    // The actual message varies depending on which compiler you use.

  return 0;
}