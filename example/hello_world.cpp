#include <iostream>

#include "example/example.h"

int main() {
    std::string embedded = example_example_bin::GetContentString();
    std::cout << embedded << std::endl;
    return 0;
}