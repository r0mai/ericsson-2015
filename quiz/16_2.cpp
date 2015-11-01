#include <iostream>

bool f() { return true; }

#define g() true; std::cout

int main() {
    std::cout << f() && g() << std::endl;
}
