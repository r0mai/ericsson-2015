#include <iostream>

auto foo(int c) { return c <= 0 ? -1 : foo(c - 1); }

int main() {

}
