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
    game.state = state;

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
    game.state = state;

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
    game.state = state;

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
    game.state = state;

    Point docLocation = *game.findObject(ElementType::DOC);
    Point deLoreanLocation = *game.findObject(ElementType::DELOREAN);

    auto path = game.getPathTo(docLocation, deLoreanLocation);

    JUST_ASSERT_EQUAL(path.size(), 150);
}

JUST_TEST_CASE(is_element) {
    Field f;
    f.element = Chest{};

    JUST_ASSERT(f.is(ElementType::CHEST));
    JUST_ASSERT(!f.is(ElementType::BLANK));
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
    game.state = state;

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

JUST_TEST_CASE(Game_gotoDeloreanWithChests_1) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "WD C    C C C LW",
        "WWWWWWWWWWWWWWWW",
    });
    FluxCapatitor fc;
    fc.id = 1123;

    Game game;
    game.state = state;
    game.initExtraState();
    game.doc.flux_capatitors.push_back(fc);

    auto response = game.goToDeloreanThroughChests();
    JUST_ASSERT(bool(response));

    JUST_ASSERT(response->has_command());
    JUST_ASSERT(response->has_direction());
    JUST_ASSERT(response->has_flux_capatitor_id());
    JUST_ASSERT(response->has_flux_capatitor_time());
    JUST_ASSERT_EQUAL(response->command(), protocol::Response::PUTFLUXCAPATITOR);
    JUST_ASSERT_EQUAL(response->direction(), protocol::Response::RIGHT);
    JUST_ASSERT_EQUAL(response->flux_capatitor_id(), 1123);
    JUST_ASSERT_EQUAL(response->flux_capatitor_time(), 6);
}

JUST_TEST_CASE(Game_gotoDeloreanWithChests_2) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "W DC    C C C LW",
        "WWWWWWWWWWWWWWWW",
    });
    FluxCapatitor fc;
    fc.id = 1123;

    Game game;
    game.state = state;
    game.initExtraState();
    game.doc.flux_capatitors.push_back(fc);

    auto response = game.goToDeloreanThroughChests();
    JUST_ASSERT(bool(response));

    JUST_ASSERT(response->has_command());
    JUST_ASSERT(response->has_direction());
    JUST_ASSERT(!response->has_flux_capatitor_id());
    JUST_ASSERT(!response->has_flux_capatitor_time());
    JUST_ASSERT_EQUAL(response->command(), protocol::Response::MOVE);
    JUST_ASSERT_EQUAL(response->direction(), protocol::Response::LEFT);
}

JUST_TEST_CASE(Game_gotoDeloreanWithChests_3) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "WD  C   C C C LW",
        "WWWWWWWWWWWWWWWW",
    });
    FluxCapatitor fc;
    fc.id = 1123;

    Game game;
    game.state = state;
    game.initExtraState();
    game.doc.flux_capatitors.push_back(fc);

    auto response = game.goToDeloreanThroughChests();
    JUST_ASSERT(bool(response));

    JUST_ASSERT(response->has_command());
    JUST_ASSERT(response->has_direction());
    JUST_ASSERT(!response->has_flux_capatitor_id());
    JUST_ASSERT(!response->has_flux_capatitor_time());
    JUST_ASSERT_EQUAL(response->command(), protocol::Response::MOVE);
    JUST_ASSERT_EQUAL(response->direction(), protocol::Response::RIGHT);
}

JUST_TEST_CASE(Game_timeUntilTimeTravel_1) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "W       F      W",
        "WWWWWWWWWWWWWWWW",
    });

    JUST_ASSERT(state.at(8, 1).is<FluxCapatitor>());


    Game game;
    game.state = state;

    auto& fc = game.state.at(8, 1).as<FluxCapatitor>();
    fc.radius = 2;
    fc.time_to_activated = 3;

    game.initExtraState();

    JUST_ASSERT_EQUAL(game.state.at(10, 1).timeUntilTimeTravel, 3);
    JUST_ASSERT_EQUAL(game.state.at(9, 1).timeUntilTimeTravel, 3);
    JUST_ASSERT_EQUAL(game.state.at(8, 1).timeUntilTimeTravel, 3);
    JUST_ASSERT_EQUAL(game.state.at(7, 1).timeUntilTimeTravel, 3);
    JUST_ASSERT_EQUAL(game.state.at(6, 1).timeUntilTimeTravel, 3);

    JUST_ASSERT(!bool(game.state.at(11, 1).timeUntilTimeTravel));
    JUST_ASSERT(!bool(game.state.at(5, 1).timeUntilTimeTravel));
    JUST_ASSERT(!bool(game.state.at(8, 0).timeUntilTimeTravel));
    JUST_ASSERT(!bool(game.state.at(8, 2).timeUntilTimeTravel));
}

JUST_TEST_CASE(Game_timeUntilTimeTravel_2) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "W              W",
        "W       F W    W",
        "WWWWWWWWWWWWWWWW",
    });

    JUST_ASSERT(state.at(8, 2).is<FluxCapatitor>());


    Game game;
    game.state = state;

    auto& fc = game.state.at(8, 2).as<FluxCapatitor>();
    fc.radius = 2;
    fc.time_to_activated = 3;

    game.initExtraState();

    JUST_ASSERT_EQUAL(game.state.at(9, 2).timeUntilTimeTravel, 3);
    JUST_ASSERT_EQUAL(game.state.at(8, 2).timeUntilTimeTravel, 3);
    JUST_ASSERT_EQUAL(game.state.at(7, 2).timeUntilTimeTravel, 3);
    JUST_ASSERT_EQUAL(game.state.at(6, 2).timeUntilTimeTravel, 3);
    JUST_ASSERT_EQUAL(game.state.at(8, 1).timeUntilTimeTravel, 3);

    JUST_ASSERT(!bool(game.state.at(10, 2).timeUntilTimeTravel));
    JUST_ASSERT(!bool(game.state.at(5, 2).timeUntilTimeTravel));
    JUST_ASSERT(!bool(game.state.at(8, 3).timeUntilTimeTravel));
}

JUST_TEST_CASE(Game_timeUntilTimeTravel_3) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "W       DF     W",
        "W       F W    W",
        "WWWWWWWWWWWWWWWW",
    });

    JUST_ASSERT(state.at(8, 2).is<FluxCapatitor>());
    JUST_ASSERT(state.at(9, 1).is<FluxCapatitor>());

    Game game;
    game.state = state;

    auto& fc1 = game.state.at(8, 2).as<FluxCapatitor>();
    auto& fc2 = game.state.at(9, 1).as<FluxCapatitor>();

    fc1.radius = 2;
    fc1.time_to_activated = 3;

    fc2.radius = 2;
    fc2.time_to_activated = 1;

    game.initExtraState();

    JUST_ASSERT_EQUAL(game.state.at(7, 1).timeUntilTimeTravel, 1);
    JUST_ASSERT_EQUAL(game.state.at(11, 1).timeUntilTimeTravel, 1);
    JUST_ASSERT_EQUAL(game.state.at(10, 1).timeUntilTimeTravel, 1);
    JUST_ASSERT_EQUAL(game.state.at(9, 2).timeUntilTimeTravel, 1);
    JUST_ASSERT_EQUAL(game.state.at(8, 2).timeUntilTimeTravel, 3);
    JUST_ASSERT_EQUAL(game.state.at(7, 2).timeUntilTimeTravel, 3);
    JUST_ASSERT_EQUAL(game.state.at(6, 2).timeUntilTimeTravel, 3);
    JUST_ASSERT_EQUAL(game.state.at(8, 1).timeUntilTimeTravel, 1);

    JUST_ASSERT(!bool(game.state.at(10, 2).timeUntilTimeTravel));
    JUST_ASSERT(!bool(game.state.at(5, 2).timeUntilTimeTravel));
    JUST_ASSERT(!bool(game.state.at(8, 3).timeUntilTimeTravel));
    JUST_ASSERT(!bool(game.state.at(6, 1).timeUntilTimeTravel));
}

JUST_TEST_CASE(Game_goToASafeSpot_1) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "WDFC    C C C LW",
        "W  W           W",
        "WWWWWWWWWWWWWWWW",
    });

    Game game;
    game.state = state;

    JUST_ASSERT(game.state.at(2, 1).is<FluxCapatitor>());

    auto& fc = game.state.at(2, 1).as<FluxCapatitor>();
    fc.radius = 5;
    fc.time_to_activated = 2;

    game.initExtraState();

    JUST_ASSERT_EQUAL(game.state.at(1, 1).timeUntilTimeTravel, 2);
    JUST_ASSERT_EQUAL(game.state.at(1, 2).timeUntilTimeTravel, boost::none);

    auto response = game.goToASafeSpot();
    JUST_ASSERT(bool(response));

    JUST_ASSERT(response->has_command());
    JUST_ASSERT(response->has_direction());
    JUST_ASSERT(!response->has_flux_capatitor_id());
    JUST_ASSERT(!response->has_flux_capatitor_time());
    JUST_ASSERT_EQUAL(response->command(), protocol::Response::MOVE);
    JUST_ASSERT_EQUAL(response->direction(), protocol::Response::DOWN);
}

JUST_TEST_CASE(Game_getPathToWithFlux) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWWW",
        "W   W   W   W  W",
        "W W   W   W    W",
        "WDWWWWWWWWWWWW W",
        "W      L       W",
        "WFWWWWWWWWWWWWWW",
        "WWWWWWWWWWWWWWWW",
    });

    Game game;
    game.state = state;

    JUST_ASSERT(game.state.at(1, 5).is<FluxCapatitor>());

    auto& fc = game.state.at(1, 5).as<FluxCapatitor>();
    fc.radius = 1;
    fc.time_to_activated = 2;

    game.initExtraState();

    JUST_ASSERT_EQUAL(game.state.at(1, 4).timeUntilTimeTravel, 2);

    auto normalPath = game.getPathTo(*game.docLocation, *game.deLoreanLocation);
    JUST_ASSERT(!normalPath.empty());
    JUST_ASSERT_EQUAL(normalPath.front(), Point(1, 4)); // towards flux

    auto avoidPath = game.getPathTo(
        *game.docLocation, *game.deLoreanLocation,
        Game::PATH_AVOID_FLUX_AS_FIRST_STEP);

    JUST_ASSERT(!avoidPath.empty());
    JUST_ASSERT_EQUAL(avoidPath.front(), Point(1, 2)); // away from flux
}

JUST_TEST_CASE(Game_getPathToWithFluxWait) {
    State state = stateFromString({
        "WWWWWWWWWWWWWWW",
        "W FC C  C   CLW",
        "WDW WCWCW W WCW",
        "WC  CCWC     CW",
        "WWWWWWWWWWWWWWW",
    });

    Game game;
    game.state = state;

    JUST_ASSERT(game.state.at(2, 1).is<FluxCapatitor>());

    auto& fc = game.state.at(2, 1).as<FluxCapatitor>();
    fc.radius = 1;
    fc.time_to_activated = 2;

    game.initExtraState();

    // response is explicit nothing
    auto response = game.goToDeloreanThroughChests();
    JUST_ASSERT(bool(response));
    JUST_ASSERT(!response->has_command());
}
