/*

Notes : 

    1. When a control flow statement causes point of execution to change to a non-sequential statement, this is called branching.

    Conditional statements	Causes a sequence of code to execute only if some condition is met.                     	if, else, switch
    Jumps	                Tells the CPU to start executing the statements at some other location.	                    goto, break, continue
    Function calls	        Jump to some other location and back.	                                                    function calls, return
    Loops	                Repeatedly execute some sequence of code zero or more times, until some condition is met.	while, do-while, for, ranged-for
    Halts	                Terminate the program.	                                                                    std::exit(), std::abort()
    Exceptions	            A special kind of flow control structure designed for error handling.	                    try, throw, catch

    2. A conditional statement is a statement that specifies whether some associated statement(s) should be executed or not.

       C++ supports two basic kinds of conditionals: if statements and switch statements .

    3. Code : 

       if (x >= 0) // outer if statement
        // it is bad coding style to nest if statements this way
        if (x <= 20) // inner if statement
            std::cout << x << " is between 0 and 20\n";

        // which if statement does this else belong to?
        else
            std::cout << x << " is negative\n";
        
        The above program introduces a source of potential ambiguity called a dangling else problem. Is the else statement in the above program matched up with the outer or inner if statement?

        The answer is that an else statement is paired up with the last unmatched if statement in the same block. Thus, in the program above, the else is matched up with the inner if statement,

    4. Evaluating a constexpr conditional at runtime is wasteful (since the result will never vary). It is also wasteful to compile code into the executable that can never be executed.

    5. Constexpr if statements C++17 - C++17 introduces the constexpr if statement, which requires the conditional to be a constant expression. The conditional of a constexpr-if-statement will be evaluated at compile-time.

    if constexpr (gravity == 9.8) // now using constexpr if
		std::cout << "Gravity is normal.\n";
	else
		std::cout << "We are not on Earth.\n";

    Favor constexpr if statements over non-constexpr if statements when the conditional is a constant expression.

    6. Modern compilers and if statements with constexpr conditionals C++17

    => For optimization purposes, modern compilers will generally treat non-constexpr if-statements that have constexpr conditionals as if they were constexpr-if-statements. However, they are not required to do so.

    => A compiler that encounters a non-constexpr if-statement with a constexpr conditional may issue a warning advising you to use if constexpr instead. This will ensure that compile-time evaluation will occur (even if optimizations are disabled).
    
    7. The idea behind a switch statement is simple: an expression (sometimes called the condition) is evaluated to produce a value. If the expression’s value is equal to the value after any of the case labels, the statements after the matching case label are executed. If no matching value can be found and a default label exists, the statements after the default label are executed instead.

    The one restriction is that the condition must evaluate to an integral type , or an enumerated type ,  or be convertible to one. Expressions that evaluate to floating point types, strings, and most other non-integral types may not be used here.

    8. Why does the switch type only allow for integral (or enumerated) types? The answer is because switch statements are designed to be highly optimized. Historically, the most common way for compilers to implement switch statements is via Jump tables -- and jump tables only work with integral values.

    9. The [[fallthrough]] attribute - Attributes are a modern C++ feature that allows the programmer to provide the compiler with some additional data about the code. To specify an attribute, the attribute name is placed between double brackets. Attributes are not statements -- rather, they can be used almost anywhere where they are contextually relevant.

    The [[fallthrough]] attribute modifies a null statement to indicate that fallthrough is intentional (and no warnings should be triggered).

    10. Variable declaration and initialization inside case statements - You can declare or define (but not initialize) variables inside the switch, both before and after the case labels - 

        switch (1)
        {
            int a; // okay: definition is allowed before the case labels
            int b{ 5 }; // illegal: initialization is not allowed before the case labels

        case 1:
            int y; // okay but bad practice: definition is allowed within a case
            y = 4; // okay: assignment is allowed
            break;

        case 2:
            int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
            y = 5; // okay: y was declared above, so we can use it here too
            break;

        case 3:
            break;
        }
    
    11. Although variable y was defined in case 1, it was used in case 2 as well. All statements inside the switch are considered to be part of the same scope. Thus, a variable declared or defined in one case can be used in a later case, even if the case in which the variable is defined is never executed (because the switch jumped over it)!

    12. In C++, unconditional jumps are implemented via a goto statement, and the spot to jump to is identified through use of a statement label. Just like with switch case labels, statement labels are conventionally not indented.

    13. Statement labels have function scope

        In the chapter on object scope (chapter 7), we covered two kinds of scope: local (block) scope, and file (global) scope. 
        
        Statement labels utilize a third kind of scope: function scope, which means the label is visible throughout the function even before its point of declaration. The goto statement and its corresponding statement label must appear in the same function.

    14.  

*/ 

int main()
{

    switch (1)
    {
        int a; // okay: definition is allowed before the case labels
        int b{ 5 }; // illegal: initialization is not allowed before the case labels

        case 1:
            int y; // okay but bad practice: definition is allowed within a case
            y = 4; // okay: assignment is allowed
            break;

        case 2:
            int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
            y = 5; // okay: y was declared above, so we can use it here too
            break;

        case 3:
            break;
    }

    return 0;
}