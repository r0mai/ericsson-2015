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

    void initExtraState();
    void initSpecialPositions();
    void initTimeUntilTimeTravelAt(const Point& p);
    void initTimeUntilTimeTravel();

    // Returns none if no path is found
    boost::optional<protocol::Response> goToDelorean();
    boost::optional<protocol::Response> goToDeloreanThroughChests();
    boost::optional<protocol::Response> goToASafeSpot();

    std::vector<Point> getPathTo(
        const Point& from, const Point& to, bool throughChest = false) const;
    boost::optional<Point> findObject(ElementType type);

    protocol::Response::Direction getDirection(
        const Point& from, const Point& to);

    boost::optional<Point> findBlankAround(const Point& p) const;

    // safe spot means that spot won't timetravel
    boost::optional<Point> findSafeSpotNear(const Point& from) const;

    protocol::Response calculateResponse();

    static constexpr unsigned kMaxRounds = 300;
    static constexpr unsigned kMinTimeTravel = 2; //inclusive
    static constexpr unsigned kMaxTimeTravel = 6; //inclusive

    State state;
    boost::optional<Point> docLocation;
    boost::optional<Point> deLoreanLocation;
    Doc doc;
    DeLorean deLorean;
};

std::ostream& operator<<(std::ostream& os, protocol::Response::Direction d);

} // namespace bm

#endif
