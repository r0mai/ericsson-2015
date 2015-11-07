#include <iostream>
#include <string>

template<class Te>
auto magic = [](Te matikus) {
    return Te{"mate"} + matikus;
};

auto magic2 = [](auto matikus) { return decltype(matikus){"mate"} + matikus; };

int main() {
    std::cout << magic<std::string>(std::string("matikus")) << std::endl;
    std::cout << magic2(std::string("matikus")) << std::endl;
}
