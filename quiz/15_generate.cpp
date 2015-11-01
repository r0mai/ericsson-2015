#include <string>
#include <fstream>
#include <iostream>
#include <boost/format.hpp>

int main() {
    std::string code = R"(
        #include <iostream>

        struct A {
            A() { std::cout << "A"; }
        };
        struct B : %1% A {
            B() { std::cout << "B"; }
        };
        struct C : %2% A, %3% B {
            C() { std::cout << "C"; }
        };
        struct D : %4% A, %5% B, %6% C {
            D() { std::cout << "D"; }
        };

        int main() {
            D d{};
            std::cout << std::endl;
        }
    )";
    for (unsigned i = 0; i < 65; ++i) {
        std::string s1 = (i & 0b000001) ? "virtual" : "";
        std::string s2 = (i & 0b000010) ? "virtual" : "";
        std::string s3 = (i & 0b000100) ? "virtual" : "";
        std::string s4 = (i & 0b001000) ? "virtual" : "";
        std::string s5 = (i & 0b010000) ? "virtual" : "";
        std::string s6 = (i & 0b100000) ? "virtual" : "";

        std::ofstream out("15_generated_" + std::to_string(i) + ".cpp");
        out << boost::format(code) % s1 % s2 % s3 % s4 % s5 % s6;
    }
}
