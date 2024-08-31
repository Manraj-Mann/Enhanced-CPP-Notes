#include <iostream>

/*

    notes : 

    1. While statements - The while statement (also called a while loop) is the simplest of the three loop types that C++ provides, and it has a definition very similar to that of an if-statement:

        while (condition)
            statement;

    => Favor while(true) for intentional infinite loops.

    => Integral loop variables should generally be a signed integral type.

    2. Do while statements - A do while statement is a looping construct that works just like a while loop, except the statement always executes at least once. After the statement has been executed, the do-while loop checks the condition. If the condition evaluates to true, the path of execution jumps back to the top of the do-while loop and executes it again.
    
    do
        statement; // can be a single statement or a compound statement
    while (condition);

    => Favor while loops over do-while when given an equal choice.

    3. For Loops : The for statement (also called a for loop) is preferred when we have an obvious loop variable because it lets us easily and concisely define, initialize, test, and change the value of loop variables.

    The for-statement looks pretty simple in abstract:

        for (init-statement; condition; end-expression)
        statement;

    => Avoid operator!= when doing numeric comparisons in the for-loop condition. Prefer operator< or operator<= where possible.

    4. Defining multiple variables (in the init-statement) and using the comma operator (in the end-expression) is acceptable inside a for-statement.

        for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
            std::cout << x << ' ' << y << '\n';

    5. Break - The break statement causes a while loop, do-while loop, for loop, or switch statement to end, with execution continuing with the next statement after the loop or switch being broken out of.

    6. Break vs return - 

    New programmers sometimes have trouble understanding the difference between break and return. A break statement terminates the switch or loop, and execution continues at the first statement beyond the switch or loop. A return statement terminates the entire function that the loop is within, and execution continues at point where the function was called.

    => Use break and continue when they simplify your loop logic.

    7. Continue - The continue statement provides a convenient way to end the current iteration of a loop without terminating the entire loop.

    8. The debate over use of early returns - Use early returns when they simplify your function’s logic.

    => A return statement that is not the last statement in a function is called an early return.




*/

int main()
{
    return 0;
}