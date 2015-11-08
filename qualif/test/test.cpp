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

JUST_TEST_CASE(Game_getPath_simple_corridor) {
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

    JUST_ASSERT_EQUAL(path[0], Point(2, 1));
    JUST_ASSERT_EQUAL(path[1], Point(3, 1));
    JUST_ASSERT_EQUAL(path[2], Point(4, 1));
    JUST_ASSERT_EQUAL(path[3], Point(5, 1));
    JUST_ASSERT_EQUAL(path[4], Point(6, 1));
    JUST_ASSERT_EQUAL(path[5], Point(7, 1));
    JUST_ASSERT_EQUAL(path[6], Point(8, 1));
    JUST_ASSERT_EQUAL(path[7], Point(9, 1));
    JUST_ASSERT_EQUAL(path[8], Point(10, 1));
    JUST_ASSERT_EQUAL(path[9], Point(11, 1));
    JUST_ASSERT_EQUAL(path[10], Point(12, 1));
    JUST_ASSERT_EQUAL(path[11], Point(13, 1));
    JUST_ASSERT_EQUAL(path[12], Point(14, 1));
}

JUST_TEST_CASE(Game_getPath_next_to_each_other) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "WDL            W",
        "WWWWWWWWWWWWWWWW",
    });

    Game game;
    game.currentState = state;

    Point docLocation = *game.findObject(ElementType::DOC);
    Point deLoreanLocation = *game.findObject(ElementType::DELOREAN);

    auto path = game.getPathTo(docLocation, deLoreanLocation);

    JUST_ASSERT_EQUAL(path.size(), 1);
    JUST_ASSERT_EQUAL(path[0], Point(2, 1));
}
