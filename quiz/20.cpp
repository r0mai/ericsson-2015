#include <iostream>

class c {
public:
  constexpr int val() { return 5; }
};

int main() {
    // ...
    const c cc = c();
    std::cout << cc.val() << std::endl;
}
