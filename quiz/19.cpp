#include <iostream>

#include <boost/intrusive_ptr.hpp>

struct Counted
{
    Counted() : count(0u) { }
    std::atomic_size_t count;
};
void intrusive_ptr_add_ref(Counted* p) { ++p->count; }
void intrusive_ptr_release(Counted* p) { if (--p->count == 0u) delete p; }

class Container
{
    Counted member;
public:
    boost::intrusive_ptr<Counted> getRefCountedMember() { return boost::intrusive_ptr<Counted>(&member); }
};

//auto foo() {
//  Container c;
//  return c.getRefCountedMember();
//}
//
int main() {

}
