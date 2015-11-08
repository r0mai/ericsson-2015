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

private:
    std::vector<Point> getPathTo(const Point& from, const Point& to) const;
    boost::optional<Point> findObject(ElementType type);

    protocol::Response calculateResponse();

    static constexpr unsigned kMaxRounds = 300;

    State currentState;
};

} // namespace bm

#endif
