#include <iostream>

/*
    Notes : 

    1. Favor explicit return types over function return type deduction for normal functions.

    2. A major downside of functions that use an auto return type is that such functions must be fully defined before they can be used (a forward declaration is not sufficient). 

    3. Trailing return type syntax - The auto keyword can also be used to declare functions using a trailing return syntax, where the return type is specified after the rest of the function prototype.

    Using the trailing return syntax, this could be equivalently written as:

    auto add(int x, int y) -> int
    {
        return (x + y);
    }
    
    In this case, auto does not perform type deduction -- it is just part of the syntax to use a trailing return type.

*/


// auto check(); //error

auto add() -> int;


auto ping()
{

    std::cout<<"pinging...\n";
}

int main()
{
    // std::cout<<"Check = "<<check();
    
    ping();

    std::cout<<add();

    return 0;
}

int add()
{

    return 2 + 1;
}

int check()
{

    std::cout<<"Check called\n";

    return 10;
}