#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <ostream>

#include "Response.pb.h"

namespace bm {

struct Point {
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}

    int x = 0;
    int y = 0;

    Point moveTo(protocol::Response::Direction d);

    std::array<Point, 4> getAdjacents() const;
};

inline
bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline
bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Point& p);

} // namespace bm

#endif
