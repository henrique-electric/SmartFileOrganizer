#include <iostream>

// A function wrapper to yse C++ std::cin to read an integer in C
extern "C" int read_int() {
    int ret = 0;
    std::cin >> ret;
    return ret;
}