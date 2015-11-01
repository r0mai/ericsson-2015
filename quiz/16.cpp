#include <iostream>

struct Foo {};

bool operator<<(Foo b, std::ostream& (*func)(std::ostream&)) {
    return true;
}

bool f() { return true; }
Foo g() { return {}; }

int main() {
    std::cout << f() && g() << std::endl;
}
