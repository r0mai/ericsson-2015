#include <iostream>
#include <iomanip>

//...
void * operator new(std::size_t size) throw(std::bad_alloc)
{
  void* addr = ::operator new(size);
  std::cout << "New size: " << std::dec << size << " address: " << std::hex << (long)addr << std::endl;
  return addr;
}

struct some_type {};

int main() {
  unsigned array_size = 10;
  some_type* p = new some_type[array_size];
  std::cout << "Object size: " << std::dec << sizeof(some_type) * array_size << " address: " << std::hex << (long)p << std::endl;
}
