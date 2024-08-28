// file1.cpp
#include "file1.h"
#include <iostream>

static int counter = 0;  // Internal linkage, only accessible within file1.cpp

void incrementFile1Counter() {
    counter++;
}

void printFile1Counter() {
    std::cout << "File1 Counter: " << counter << std::endl;
}
