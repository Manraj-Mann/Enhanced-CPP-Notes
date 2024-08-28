// main.cpp
#include "file1.h"
#include "file2.h"
#include <iostream>

int add(int a, int b);
void addCounter();
int main() 
{
    // incrementFile1Counter();
    // printFile1Counter();  // Output: File1 Counter: 1

    // incrementFile2Counter();
    // printFile2Counter();  // Output: File2 Counter: 101

    // g++ main.cpp file1.cpp file2.cpp  -o  main

    // *************************** To demonstrate function internal linkage comment above ********************

    std::cout<<"Value " <<add(1 , 2);

    // g++ main.cpp add.cpp -o  main = Fail to link

    // remove static and try again - it links and works fine 

    // *************************** To demonstrate unnamed or anonymous comment above ********************
    
    addCounter(); // link error due to internal linkage in anonymous namespace

    return 0;
}
