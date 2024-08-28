#include <iostream>


// forward declarations of variables
extern int global_x;
extern const int global_y;
// extern constexpr int global_z; error: declaration of ‘constexpr’ variable ‘global_z’ is not a definition
extern const int global_z;


int main()
{
    std::cout<<"global_x : "<<global_x<<std::endl;
    std::cout<<"global_y : "<<global_y<<std::endl;
    std::cout<<"global_z : "<<global_z<<std::endl;

    return 0;
}