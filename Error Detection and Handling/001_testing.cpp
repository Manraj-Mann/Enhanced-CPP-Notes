#include <iostream>


/*

    Notes : 


    1. Testing a small part of your code in isolation to ensure that “unit” of code is correct is called unit testing. Each unit test is designed to ensure that a particular behavior of the unit is correct.

    => Write your program in small, well defined units (functions or classes), compile often, and test your code as you go.

    2. Informal testing - One way you can test code is to do informal testing as you write the program. After writing a unit of code (a function, a class, or some other discrete “package” of code), you can write some code to test the unit that was just added, and then erase the test once the test passes.

    3. Automating your test functions - One problem with the above test function is that it relies on you to manually verify the results when you run it. This requires you to remember what the expected answer was at worst (assuming you didn’t document it), and manually compare the actual results to the expected results.

    4. A better method is to use assert, which will cause the program to abort with an error message if any test fails. We don’t have to create and handle test case numbers this way.

    5. Code coverage - The term code coverage is used to describe how much of the source code of a program is executed while testing. There are many different metrics used for code coverage. We’ll cover a few of the more useful and popular ones in the following sections.

        5.1. Statement coverage - The term statement coverage refers to the percentage of statements in your code that have been exercised by your testing routines.

        5.2. Branch coverage - Branch coverage refers to the percentage of branches that have been executed, each possible branch counted separately. 

        5.3. Loop coverage - Loop coverage (informally called the 0, 1, 2 test) says that if you have a loop in your code, you should ensure it works properly when it iterates 0 times, 1 time, and 2 times.

    6. Test different categories of input values to make sure your unit handles them properly.


*/

int main()
{

    return 0;
}