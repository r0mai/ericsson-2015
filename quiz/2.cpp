#include <iostream>

int main() {
    int a = 5;
    unsigned int b = -10;
    if (b > a) {
        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
        std::cout << "unsigned(a) = " << unsigned(a) << std::endl;
        std::cout << "int(b) = " << int(b) << std::endl;
        std::cout << "universe broken!" << std::endl;
    }
}
