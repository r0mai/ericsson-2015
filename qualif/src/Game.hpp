#ifndef GAME_HPP

#include "responseHelper.hpp"

#include "State.hpp"

namespace bm {

class Game {
public:
    Game() = default;

    void run();

private:
    protocol::Response calculateResponse(const protocol::Global& global);

    static constexpr unsigned kMaxRounds = 300;
};

} // namespace bm

#endif
