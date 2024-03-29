#include <iostream>

struct Foo {};

bool operator<<(Foo b, std::ostream& (*func)(std::ostream&)) {
    std::cout << "operator<<(Foo)" << std::endl;
    return true;
}

bool f() { std::cout << "f()" << std::endl; return false; }
Foo g() { std::cout << "g()" << std::endl; return {}; }

int main() {
    std::cout << f() && g() << std::endl;
}
