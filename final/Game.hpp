#ifndef GAME_HPP
#define GAME_HPP

#include "BMResponseHelper.hpp"

#include "State.hpp"
#include "Point.hpp"
#include "kumbi_main_v1.12.hpp"

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

    const static unsigned PATH_THROUGH_CHEST = 1;
    const static unsigned PATH_THROUGH_FLUX = 2;
    const static unsigned PATH_AVOID_FLUX_AS_FIRST_STEP = 4;

    int getDistanceOn(const Point& p) const;
    std::vector<Point> getPathTo(
        const Point& from, const Point& to, unsigned flags = 0) const;

    boost::optional<Point> findObject(ElementType type);

    protocol::Response::Direction getDirection(
        const Point& from, const Point& to);

    bool isSafeBlank(const Point& p, int time_travel_in_threshold = 0) const;
    boost::optional<Point> findSafeBlankAround(
        const Point& p, int time_travel_in_threshold = 0) const;

    const FluxCapatitor& minRadiusFluxCapacitor(
        const std::vector<FluxCapatitor>& fcs);

    // safe spot means that spot won't timetravel
    boost::optional<Point> findSafeSpotNear(const Point& from) const;

    protocol::Response calculateResponse();
    // Don't move or stay on places where something will be in the next round
    protocol::Response postProcessResponse(protocol::Response response);

    void logJSON();

    static constexpr unsigned kMaxRounds = 300;
    static constexpr unsigned kMinTimeTravel = 2; //inclusive
    static constexpr unsigned kMaxTimeTravel = 6; //inclusive

    State state;
    boost::optional<Point> docLocation;
    boost::optional<Point> deLoreanLocation;
    Doc doc;
    DeLorean deLorean;

    ResponseHelper  rH;

    Kumbi kumbi;
};

} // namespace bm

#endif
