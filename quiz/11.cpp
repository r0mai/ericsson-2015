#include <memory>
#include <iostream>

struct S {
    S() { std::cout << "constructor : " << this << std::endl; }
    ~S() { std::cout << "destructor : " << this << std::endl; }
    int i = 10;
};
class SWrapper {
	std::auto_ptr<S> sItem;
public:
	SWrapper() : sItem(new S) { }
	void dump() { std::cout << sItem->i << std::endl; }
};

int main() {
    SWrapper s;
    s.dump();
    SWrapper b = s;
    SWrapper x;
    b.dump();
    x = b;
    x = b;
    x.dump();
}
