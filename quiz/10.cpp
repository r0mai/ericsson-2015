#include <vector>
#include <iostream>

template<typename T>
T increasing_sum(std::vector<T>& container) {
  T sum = T();
  for(auto& item: container)
    sum += ++item;
  return sum;
}

int main() {
    std::vector<int> v = { 1, 2, 3 };
    auto a = increasing_sum(v);
    auto b = increasing_sum(v);

    std::cout << "a = " << a << ", b = " << b << std::endl;
}
