#ifndef GAME_HPP

#include "responseHelper.hpp"

#include "State.hpp"
#include "Point.hpp"

#include <vector>

namespace bm {

class Game {
public:
    Game() = default;

    void run();

//private: // disabled to avoid testing boiler plate
    std::vector<Point> getPathTo(const Point& from, const Point& to) const;
    boost::optional<Point> findObject(ElementType type);

    protocol::Response::Direction getDirection(
        const Point& from, const Point& to);

    protocol::Response calculateResponse();

    static constexpr unsigned kMaxRounds = 300;

    State currentState;
};

std::ostream& operator<<(std::ostream& os, protocol::Response::Direction d);

} // namespace bm

#endif
