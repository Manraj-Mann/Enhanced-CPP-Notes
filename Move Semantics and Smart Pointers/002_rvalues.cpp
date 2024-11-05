#include <iostream>
/* 
    Notes :  
    
    1. Prior to C++11, only one type of reference existed in C++, and so it was just called a “reference”. However, in C++11, it’s called an l-value reference. L-value references can only be initialized with modifiable l-values.

    2. C++11 adds a new type of reference called an r-value reference. An r-value reference is a reference that is designed to be initialized with an r-value (only). While an l-value reference is created using a single ampersand, an r-value reference is created using a double ampersand:

        int x{ 5 };
        int& lref{ x }; // l-value reference initialized with l-value x
        int&& rref{ 5 }; // r-value reference initialized with r-value 5

        - Example : 

            class Point
            {
                int _x {};
                int _y {};

                public:

                Point(int x = 0 , int y = 0)
                {
                    _x = x;
                    _y = y;
                }

                Point(const Point &point)
                {
                    std::cout<<"Copy Called"<<std::endl;
                    _x = point._x;
                    _y = point._y;
                }

                ~Point()
                {

                }

                friend std::ostream & operator <<(std::ostream &out , const Point &point)
                {
                    out<<"Point ( x = "<<point._x<<" , y = "<<point._y<<" ) ";
                    return out;
                }
            };

            int main()
            {
                Point &&rRef {Point(1 , 2)}; // r-value reference to temporary Fraction

                std::cout<<rRef<<std::endl;

                return 0;
            } // rRef (and the temporary Fraction) goes out of scope here

        - As an anonymous object, Point(1 , 2) would normally go out of scope at the end of the expression in which it is defined. However, since we’re initializing an r-value reference with it, its duration is extended until the end of the block. We can then use that r-value reference to print the Point's value.

    3. R-value references as function parameters - R-value references are more often used as function parameters. This is most useful for function overloads when you want to have different behavior for l-value and r-value arguments.

        void fun(const int& lref) // l-value arguments will select this function
        {
            std::cout << "l-value reference to const: " << lref << '\n';
        }

        void fun(int&& rref) // r-value arguments will select this function
        {
            std::cout << "r-value reference: " << rref << '\n';
        }

        int main()
        {
            int x{ 5 };
            fun(x); // l-value argument calls l-value version of function
            fun(5); // r-value argument calls r-value version of function

            return 0;
        }

        - As you can see, when passed an l-value, the overloaded function resolved to the version with the l-value reference. When passed an r-value, the overloaded function resolved to the version with the r-value reference (this is considered a better match than an l-value reference to const).

        - Why would you ever want to do this? We’ll discuss this in more detail in the next lesson. Needless to say, it’s an important part of move semantics.

    4. Rvalue reference variables are lvalues - Consider the following snippet:

            int&& ref{ 5 };
            fun(ref);
        
        Which version of fun would you expect the above to call: fun(const int&) or fun(int&&)?

        => The answer might surprise you. This calls fun(const int&).

        - Although variable ref has type int&&, when used in an expression it is an lvalue (as are all named variables). The type of an object and its value category are independent.

        - You already know that literal 5 is an rvalue of type int, and int x is an lvalue of type int. Similarly, int&& ref is an lvalue of type int&&.

        - So not only does fun(ref) call fun(const int&), it does not even match fun(int&&), as rvalue references can’t bind to lvalues.

    5. Returning an r-value reference - You should almost never return an r-value reference, for the same reason you should almost never return an l-value reference. In most cases, you’ll end up returning a hanging reference when the referenced object goes out of scope at the end of the function.

*/

class Point
{
    int _x {};
    int _y {};

    public:

    Point(int x = 0 , int y = 0)
    {
        _x = x;
        _y = y;
    }

    Point(const Point &point)
    {
        std::cout<<"Copy Called"<<std::endl;
        _x = point._x;
        _y = point._y;
    }

    ~Point()
    {

    }

    friend std::ostream & operator <<(std::ostream &out , const Point &point)
    {
        out<<"Point ( x = "<<point._x<<" , y = "<<point._y<<" ) ";
        return out;
    }
};

void print(const int &ref)
{
    std::cout<<"l-value ref called"<<std::endl;
}
void print(int &&ref)
{
    std::cout<<"r-value ref called"<<std::endl;
}

int main()
{
    Point &&rRef {Point(1 , 2)}; // r-value reference to temporary Fraction

    std::cout<<rRef<<std::endl;


    int a = 10;

    print(a);
    print(10);
    print(std::ref(a));
    
    int &&ref {10};

    print(ref);


    return 0;
} // rRef (and the temporary Fraction) goes out of scope here