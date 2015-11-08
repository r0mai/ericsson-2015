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

    // Returns none if no path is found
    boost::optional<protocol::Response> goToDelorean();

    std::vector<Point> getPathTo(const Point& from, const Point& to) const;
    boost::optional<Point> findObject(ElementType type);

    protocol::Response::Direction getDirection(
        const Point& from, const Point& to);

    protocol::Response calculateResponse();

    static constexpr unsigned kMaxRounds = 300;
    static constexpr unsigned kMinTimeTravel = 2; //inclusive
    static constexpr unsigned kMaxTimeTravel = 6; //inclusive

    State currentState;
};

std::ostream& operator<<(std::ostream& os, protocol::Response::Direction d);

} // namespace bm

#endif
