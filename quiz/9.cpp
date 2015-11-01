#include <iostream>
#include <memory>

// https://en.wikipedia.org/wiki/Duff%27s_device

void copy(short *to_, short *from_, short count_) {
    register short *to = to_, *from = from_;
    register short count = count_;
    {
        register short n = (count + 7) / 8;
        switch (count % 8) {
        case 0: do { *to++ = *from++;
        case 7:      *to++ = *from++;
        case 6:      *to++ = *from++;
        case 5:      *to++ = *from++;
        case 4:      *to++ = *from++;
        case 3:      *to++ = *from++;
        case 2:      *to++ = *from++;
        case 1:      *to++ = *from++;
                } while (--n > 0);
        }
    }
}

int main() {
    short from[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    short to[10] = { 20 };

    copy(to, from, 10);

    for (size_t i = 0; i < 10; ++i) {
        std::cout << from[i] << " == " << to[i] << std::endl;
    }
}
