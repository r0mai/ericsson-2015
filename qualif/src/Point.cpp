#include "Point.hpp"

namespace bm {

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

Point Point::moveTo(protocol::Response::Direction d) {
    switch (d) {
        case protocol::Response::DOWN: return Point(x, y + 1);
        case protocol::Response::UP: return Point(x, y - 1);
        case protocol::Response::RIGHT: return Point(x + 1, y);
        case protocol::Response::LEFT: return Point(x - 1, y);
    }
    return *this;
}

std::array<Point, 4> Point::getAdjacents() const {
    return {{
        {x + 1, y},
        {x - 1, y},
        {x, y + 1},
        {x, y - 1}
    }};
}

} // namespace bm
