// file2.cpp
#include "file2.h"
#include <iostream>

static int counter = 100;  // Internal linkage, only accessible within file2.cpp

void incrementFile2Counter() {
    counter++;
}

void printFile2Counter() {
    std::cout << "File2 Counter: " << counter << std::endl;
}
