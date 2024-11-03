#include <iostream>
/* 
    Notes :  
    
    1. Overloading operator<< : Overloading operator<< is similar to overloading operator+ (they are both binary operators), except that the parameter types are different.

        - Consider the expression std::cout << point. If the operator is <<, what are the operands? The left operand is the std::cout object, and the right operand is your Point class object. std::cout is actually an object of type std::ostream. Therefore, our overloaded function will look like this:

            // std::ostream is the type for object std::cout
            friend std::ostream& operator<< (std::ostream& out, const Point& point);

        - Implementation of operator<< for our Point class is fairly straightforward -- because C++ already knows how to output doubles using operator<<, and our members are all doubles, we can simply use operator<< to output the member variables of our Point. Here is the above Point class with the overloaded operator<<.

            class Point
            {
            private:
                double m_x{};
                double m_y{};
                double m_z{};

            public:
                Point(double x=0.0, double y=0.0, double z=0.0)
                : m_x{x}, m_y{y}, m_z{z}
                {
                }

                friend std::ostream& operator<< (std::ostream& out, const Point& point);
            };

            std::ostream& operator<< (std::ostream& out, const Point& point)
            {
                // Since operator<< is a friend of the Point class, we can access Point's members directly.
                out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')'; // actual output done here

                return out; // return std::ostream so we can chain calls to operator<<
            }

    2. This is pretty straightforward -- note how similar our output line is to the line in the print() function we wrote previously. The most notable difference is that std::cout has become parameter out (which will be a reference to std::cout when the function is called).

        - The trickiest part here is the return type. With the arithmetic operators, we calculated and returned a single answer by value (because we were creating and returning a new result). However, if you try to return std::ostream by value, you’ll get a compiler error. This happens because std::ostream specifically disallows being copied.

        - In this case, we return the left hand parameter as a reference. This not only prevents a copy of std::ostream from being made, it also allows us to “chain” output commands together, such as std::cout << point << std::endl;

        - Any time we want our overloaded binary operators to be chainable in such a manner, the left operand should be returned (by reference). Returning the left-hand parameter by reference is okay in this case -- since the left-hand parameter was passed in by the calling function, it must still exist when the called function returns. Therefore, we don’t have to worry about referencing something that will go out of scope and get destroyed when the operator returns.

            class Point
            {
            private:
                double m_x{};
                double m_y{};
                double m_z{};

            public:
                Point(double x=0.0, double y=0.0, double z=0.0)
                : m_x{x}, m_y{y}, m_z{z}
                {
                }

                friend std::ostream& operator<< (std::ostream& out, const Point& point);
            };

            std::ostream& operator<< (std::ostream& out, const Point& point)
            {
                // Since operator<< is a friend of the Point class, we can access Point's members directly.
                out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';

                return out;
            }

            int main()
            {
                Point point1 { 2.0, 3.5, 4.0 };
                Point point2 { 6.0, 7.5, 8.0 };

                std::cout << point1 << ' ' << point2 << '\n';

                return 0;
            }

    3. Overloading operator>> : It is also possible to overload the input operator. This is done in a manner analogous to overloading the output operator. The key thing you need to know is that std::cin is an object of type std::istream. Here’s our Point class with an overloaded operator>> added:

        // note that parameter point must be non-const so we can modify the object
        // note that this implementation is a non-friend
        std::istream& operator>> (std::istream& in, Point& point)
        {
            double x{};
            double y{};
            double z{};

            in >> x >> y >> z;

            if (in)                     // if all input succeeded
                point = Point{x, y, z}; // overwrite our existing point

            return in;
        }

        int main()
        {
            std::cout << "Enter a point: ";

            Point point{};
            std::cin >> point;

            std::cout << "You entered: " << point << '\n';

            return 0;
        }

        - In this implementation, we use operator= to overwrite the values in our point. Because operator= is publicly available, this means we don’t need our operator>> to be a friend.

    4. Guarding against partial extraction : You might have expected to see our overloaded operator>> for Point implemented more like this:

        // Assume this operator is a friend of Point so we can directly access the members of point
        std::istream& operator>> (std::istream& in, Point& point)
        {
            // This version subject to partial extraction issues
            in >> point.m_x >> point.m_y >> point.m_z;

            return in;
        }

        - However, this implementation may result in a partial extraction. Consider what would happen if the user were to enter “3.0 a b” as input. 3.0 would be extracted to m_x. The extraction to m_y and m_z would both fail, meaning m_y and m_z would be set to 0.0. Our point would be partially overwritten by input and partially zero’d.

        - With a Point object, that might be an acceptable outcome. But imagine we were inputting a Fraction instead. A failed extraction to the denominator would set the denominator to 0.0, which might later cause a divide by zero.

        - For this reason, it’s better to store all inputs until we can validate that all inputs were successful, and only then overwrite the object.

    5. Overloading operator<< and operator>> make it extremely easy to output your class to screen and accept user input from the console.

*/

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0.0, double y=0.0, double z=0.0)
      : m_x{x}, m_y{y}, m_z{z}
    {
    }

    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }

    void print() const
    {
        std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ')';
    }

    friend std::ostream& operator<< (std::ostream& out, const Point& point);
    // friend void operator<< (std::ostream& out, const Point& point);

};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    // Since operator<< is a friend of the Point class, we can access Point's members directly.
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')'<<std::endl; // actual output done here

    return out; // return std::ostream so we can chain calls to operator<<
}

// void operator<< (std::ostream& out, const Point& point)
// {
//     // Since operator<< is a friend of the Point class, we can access Point's members directly.
//     out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')'; // actual output done here

//     // return out; // return std::ostream so we can chain calls to operator<<
// }

// note that parameter point must be non-const so we can modify the object
// note that this implementation is a non-friend
std::istream& operator>> (std::istream& in, Point& point)
{
    double x{};
    double y{};
    double z{};

    in >> x >> y >> z;

    if (in)                     // if all input succeeded
        point = Point{x, y, z}; // overwrite our existing point

    return in;
}

int main()
{
    const Point point1 { 2.0, 3.0, 4.0 };

    // std::cout << point1 << '\n';
    std::cout<<point1; // this also works 


    std::cout << "Enter a point: ";

    Point point{};
    std::cin >> point;

    std::cout << "You entered: " << point << '\n';

    return 0;
}