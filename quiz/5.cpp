#include <array>
#include <iostream>

// http://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special
// It is guaranteed that there will be no padding in the beginning of a POD object.
// In other words, if a POD-class A's first member is of type T, you can safely
// reinterpret_cast from A* to T* and get the pointer to the first member and vice versa.
//
// http://stackoverflow.com/questions/3674247/is-stdarrayt-s-guaranteed-to-be-pod-if-t-is-pod
//
// In C++03, POD was defined in terms of aggregate: a class where every subobject
// is native or an aggregate is POD. So, by backwards compatibility, a C++0x
// std::array is POD.

int main() {
    int data[] = {1, 2, 3, 4, 5};
    std::array<int, 5> &a = reinterpret_cast<std::array<int, 5>&>(data);
    for (int n : a) {
        std::cout << n << std::endl;
    }
}
