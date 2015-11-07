#ifndef GAME_HPP

#include "responseHelper.hpp"

namespace bm {

class Game {
public:
    Game() = default;

    void run();

private:
    static constexpr unsigned kMaxRounds = 300;
};

} // namespace bm

#endif
