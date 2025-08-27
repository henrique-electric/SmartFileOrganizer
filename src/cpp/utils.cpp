#include <iostream>
#include <limits>

extern "C" {
    int read_int(void) {
        int ret = 0;
        std::cin >> ret;
        return ret;
    }
}