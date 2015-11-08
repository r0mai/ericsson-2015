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

JUST_TEST_CASE(Game_getPath_real_map) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "WD                                      W",
        "WCWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW W",
        "WLWCCCC       C C    CCC  CCC  CCC  CC  W",
        "W W W W WCW WCW WCW W W WCW W W W WCW W W",
        "W W  CCCCCC     C C CC CCC CC  C CC  C  W",
        "W W WCW WCW W W WCWCWCWCW W W WCW W WCW W",
        "W WCC       CC  C CC CCCC C CCCC        W",
        "W WCW W WCWCW W WCW W WCW W WCW W W W W W",
        "W W  CC   C     C  C  CC     C       C  W",
        "W W WCW W W WCW WCW WCW WCW WCW WCWCWCW W",
        "W W   CC     C         C CC      C   C  W",
        "W W W WCW W WCWCWCW WCWCW W W WCWCW WCW W",
        "W W   CC C  C  CC C  CCC         CC  CC W",
        "W WCW WCW W W WCWCW W W W W W W WCW W W W",
        "W W  C    C     C   C CC       C        W",
        "W W W W W W WCW W WCW W W WCWCW W W W W W",
        "W W C C  C    C C C C C   C CC  CC C    W",
        "W W WCW WCW W W W W WCW W W WCW WCW W W W",
        "W WC   C    C  CC C     C C     C     C W",
        "W W WCW W W W W W WCWCW W W W W WCWCW W W",
        "W WC    CCC C         C CCC     C       W",
        "W WCW W W W WCW W W W W W W WCWCWCW W W W",
        "W W   C C C C CC C  C               C   W",
        "W W W WCWCWCWCW WCWCW WCW W WCWCW W WCW W",
        "W W CC CCC      C        C  C   C       W",
        "W WCW WCW W WCW WCW W WCW W W W W WCW W W",
        "W W  C  CC     C  C CC C    CCC     C   W",
        "W W W W W WCWCW W W W W W W WCW W W WCW W",
        "W W   C  C CC  C C       C   C    C CC  W",
        "W W W W W W WCWCW W W W WCW W W W WCW W W",
        "W W  C    CCC   CC    CC      C C C C   W",
        "W W W W W WCWCW W WCW W W WCWCWCW W W W W",
        "W W       C  C    C   C CC C CCCC    C  W",
        "W W W W WCW WCWCWCWCWCWCW W W W W WCW W W",
        "W W    C C   C    C CC    CC     CC  CC W",
        "W WCW W W WCWCW WCWCW W W WCW WCW W W W W",
        "W WCCC  C    C       C C    C C C     C W",
        "W W W W W W WCW W WCWCW W WCW WCWCW WCW W",
        "W                                       W",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    });

    Game game;
    game.currentState = state;

    Point docLocation = *game.findObject(ElementType::DOC);
    Point deLoreanLocation = *game.findObject(ElementType::DELOREAN);

    auto path = game.getPathTo(docLocation, deLoreanLocation);

    JUST_ASSERT_EQUAL(path.size(), 150);
}

JUST_TEST_CASE(isElementA_1) {
    FieldElement f = Chest{};

    JUST_ASSERT(isFieldElementA(f, ElementType::CHEST));
    JUST_ASSERT(!isFieldElementA(f, ElementType::BLANK));
}

JUST_TEST_CASE(getDirection) {
    Game g;
    JUST_ASSERT_EQUAL(g.getDirection(Point(5, 4), Point(6, 4)), protocol::Response::RIGHT);
    JUST_ASSERT_EQUAL(g.getDirection(Point(5, 4), Point(4, 4)), protocol::Response::LEFT);
    JUST_ASSERT_EQUAL(g.getDirection(Point(5, 4), Point(5, 5)), protocol::Response::DOWN);
    JUST_ASSERT_EQUAL(g.getDirection(Point(5, 4), Point(5, 3)), protocol::Response::UP);
}

JUST_TEST_CASE(Game_getPath_simple_corridor_with_Chests) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "WD      C C C LW",
        "WWWWWWWWWWWWWWWW",
    });

    Game game;
    game.currentState = state;

    Point docLocation = *game.findObject(ElementType::DOC);
    Point deLoreanLocation = *game.findObject(ElementType::DELOREAN);

    auto path = game.getPathTo(docLocation, deLoreanLocation, true);

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
