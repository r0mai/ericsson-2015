#include "just/test.hpp"

#include "Game.hpp"
#include "TestUtil.hpp"

#include <boost/optional/optional_io.hpp>

using namespace bm;

JUST_TEST_CASE(Game_findObject) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "WD            LW",
        "WWWWWWWWWWWWWWWW",
    });

    Game game;
    game.currentState = state;

    JUST_ASSERT_EQUAL(game.findObject(ElementType::DOC), Point(1, 1));
    JUST_ASSERT_EQUAL(game.findObject(ElementType::DELOREAN), Point(14, 1));
}

JUST_TEST_CASE(Game_getPath) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "WD            LW",
        "WWWWWWWWWWWWWWWW",
    });

    Game game;
    game.currentState = state;

    Point docLocation = *game.findObject(ElementType::DOC);
    Point deLoreanLocation = *game.findObject(ElementType::DELOREAN);

    auto path = game.getPathTo(docLocation, deLoreanLocation);

    JUST_ASSERT_EQUAL(path.size(), 13);
}
