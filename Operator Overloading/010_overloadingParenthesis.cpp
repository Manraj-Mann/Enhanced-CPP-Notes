#include <iostream>
/* 
    Notes :  
    
    1. There are two things to keep in mind: first, the parenthesis operator must be implemented as a member function. Second, in non-object-oriented C++, the () operator is used to call functions. In the case of classes, operator() is just a normal operator that calls a function (named operator()) like any other overloaded operator.

    2. Example : 

        class Matrix
        {
        private:
            double m_data[4][4]{};

        public:
            double& operator()(int row, int col);
            double operator()(int row, int col) const; // for const objects
        };

        double& Matrix::operator()(int row, int col)
        {
            assert(row >= 0 && row < 4);
            assert(col >= 0 && col < 4);

            return m_data[row][col];
        }

        double Matrix::operator()(int row, int col) const
        {
            assert(row >= 0 && row < 4);
            assert(col >= 0 && col < 4);

            return m_data[row][col];
        }

    3. Because the () operator is so flexible, it can be tempting to use it for many different purposes. However, this is strongly discouraged, since the () symbol does not really give any indication of what the operator is doing.

    4. Having fun with functors - Operator() is also commonly overloaded to implement functors (or function object), which are classes that operate like functions. The advantage of a functor over a normal function is that functors can store data in member variables (since they are classes).

        class Accumulator
        {
        private:
            int m_counter{ 0 };

        public:
            int operator() (int i) { return (m_counter += i); }

            void reset() { m_counter = 0; } // optional
        };

        int main()
        {
            Accumulator acc{};
            std::cout << acc(1) << '\n'; // prints 1
            std::cout << acc(3) << '\n'; // prints 4

            Accumulator acc2{};
            std::cout << acc2(10) << '\n'; // prints 10
            std::cout << acc2(20) << '\n'; // prints 30

            return 0;
        }

        - The nice thing about functors is that we can instantiate as many separate functor objects as we need, and use them all simultaneously. Functors can also have other member functions (e.g. reset()) that do convenient things.

    5. Conclusion : 
        
        - Operator() is sometimes overloaded with two parameters to index multidimensional arrays, or to retrieve a subset of a one dimensional array (with the two parameters defining the subset to return). Anything else is probably better written as a member function with a more descriptive name.

        - Operator() is also often overloaded to create functors. Although simple functors (such as the example above) are fairly easily understood, functors are typically used in more advanced programming topics, and deserve their own lesson.

*/

class Accumulator
{
private:
    int m_counter{ 0 };

public:
    int operator() (int i) { return (m_counter += i); }

    void reset() { m_counter = 0; } // optional
};

int main()
{
    Accumulator acc{};
    std::cout << acc(1) << '\n'; // prints 1
    std::cout << acc(3) << '\n'; // prints 4

    Accumulator acc2{};
    std::cout << acc2(10) << '\n'; // prints 10
    std::cout << acc2(20) << '\n'; // prints 30

    return 0;
}