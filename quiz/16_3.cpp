#include <iostream>

struct Foo {};

bool operator<<(std::ostream&, Foo f) {
    return false;
}

bool operator<<(Foo b, std::ostream& (*func)(std::ostream&)) {
    return true;
}

Foo f() { return {}; }
Foo g() { return {}; }

int main() {
    std::cout << f() && g() << std::endl;
}
