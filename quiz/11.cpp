#include <memory>
#include <iostream>

struct S { int i = 10; };
class SWrapper {
	std::auto_ptr<S> sItem;
public:
	SWrapper() : sItem(new S) { }
	void dump() { std::cout << sItem->i; }
};

int main() {
    SWrapper s;
    s.dump();
    SWrapper b = s;
    SWrapper x;
    b.dump();
    x = b;
    x.dump();
}
