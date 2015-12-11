#include <iostream>
#include <queue>
#include <set>
#include <chrono>

#include "Game.hpp"
#include "responseHelper.hpp"
#include "stream.hpp"
#include "Util.hpp"
#include "kumbi_main_v1.12.hpp"

namespace bm {

void Game::run() {
    while (true) {
        protocol::Global global;
        if (!readProtoFromStream(global, std::cin)) {
            LOGI("EOF");
            break;
        }

        auto start = std::chrono::system_clock::now();
        if (global.has_error()) {
            LOGE("error from last tick: " << fromProto(global.error()));
        }
        state = fromProto(global);

        LOGI("Tick = " << state.tick);
        std::cerr << toString(state.fields) << std::endl;

        protocol::Response response;

        initExtraState();

        LOGI("Fluxes: " << doc.flux_capatitors.size());


        //Kumbi logic
        kumbi.add_table(state,doc);
        LOGI("Kumbi fluxes: " << kumbi.doc.flux_capatitors.size());
        kumbi.create_path(kumbi.del_x,kumbi.del_y);

        LOGI("before inDnager()");
        if(kumbi.inDanger())
        {
            LOGI("in if inDnager()");
            kumbi.find_safe_place();
            LOGI("after find_safe_place()");
            kumbi.create_path(kumbi.safe_x, kumbi.safe_y);
            LOGI("after create_path()");
            kumbi.move_doc(kumbi.escape_path());
            LOGI("after move_doc()");
        }
        else {
           LOGI("in else ");
           kumbi.move_doc(kumbi.follow_path());
           LOGI("in else end");
        }

        response = kumbi.rH.getResponse();


        //Old logic
        /*try {
            response = calculateResponse();
            response = postProcessResponse(response);
        } catch (const std::exception& ex) {
            LOGE("Exception caught: " << ex.what());
            response = response::nothing();
        }*/
        if (!writeProtoOnStream(response, std::cout)) {
            LOGE("write error");
            break;
        }

        cerr << toJSON(state) << "\n";

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end - start;
        LOGI("Tick took " << diff.count() * 1000 << "ms");
        LOGI("----------------------------");
    }
    LOGI("Game over, std::cin.eof(): " << std::cin.eof());
}

void Game::initExtraState() {
    initSpecialPositions();
    initTimeUntilTimeTravel();
}

void Game::initSpecialPositions() {
    docLocation = findObject(ElementType::DOC);
    deLoreanLocation = findObject(ElementType::DELOREAN);

    if (docLocation) {
        doc = state.at(*docLocation).as<Doc>();
    }
    if (deLoreanLocation) {
        deLorean = state.at(*deLoreanLocation).as<DeLorean>();
    }
}

void Game::initTimeUntilTimeTravelAt(const Point& p) {
    //BM_ASSERT(state.at(p).is<FluxCapatitor>());

    auto& fc = state.at(p).as<FluxCapatitor>();
    auto time = fc.time_to_activated;
    auto radius = fc.radius;

    for (int x = p.x;
        x < state.width && x <= p.x + radius && !state.at(x, p.y).isBlocker(); ++x) {
        state.at(x, p.y).setTimeUntilTimeTravel(time);
    }
    for (int x = p.x;
        x >= 0 && x >= p.x - radius && !state.at(x, p.y).isBlocker(); --x) {
        state.at(x, p.y).setTimeUntilTimeTravel(time);
    }
    for (int y = p.y;
        y < state.height && y <= p.y + radius && !state.at(p.x, y).isBlocker(); ++y) {
        state.at(p.x, y).setTimeUntilTimeTravel(time);
    }
    for (int y = p.y;
        y >= 0 && y >= p.y - radius && !state.at(p.x, y).isBlocker(); --y) {
        state.at(p.x, y).setTimeUntilTimeTravel(time);
    }
}

void Game::initTimeUntilTimeTravel() {
    for (size_t x = 0; x < state.fields.size(); ++x) {
        for (size_t y = 0; y < state.fields[0].size(); ++y) {
            if (state.at(x, y).is<FluxCapatitor>()) {
                initTimeUntilTimeTravelAt(Point(x, y));
            }
        }
    }
}

boost::optional<protocol::Response> Game::goToDelorean() {
    LOGI("goToDelorean()");
    if (!docLocation || !deLoreanLocation) {
        LOGE("doc and/or delorean missing");
        return boost::none;
    }

    auto path = getPathTo(
        *docLocation, *deLoreanLocation, PATH_AVOID_FLUX_AS_FIRST_STEP);

    if (path.empty()) {
        LOGE("can't find path to deLorean from doc");
        return boost::none;
    }

    auto direction = getDirection(*docLocation, path.front());
    return response::move(direction);
}

boost::optional<protocol::Response> Game::goToDeloreanThroughChests() {
    LOGI("goToDeloreanThroughChests()");
    if (!docLocation || !deLoreanLocation) {
        LOGE("doc and/or delorean missing");
        return boost::none;
    }

    auto path = getPathTo(*docLocation, *deLoreanLocation,
        PATH_THROUGH_CHEST |
        PATH_THROUGH_FLUX |
        PATH_AVOID_FLUX_AS_FIRST_STEP);

    auto unsafePath = getPathTo(*docLocation, *deLoreanLocation,
        PATH_THROUGH_CHEST | PATH_THROUGH_FLUX);

    if (path.empty()) {
        LOGE("no path to delorean (with chests)");
        return boost::none;
    }

    if (unsafePath.empty()) {
        LOGE("no unsafe path to delorean (with chests)");
        return boost::none;
    }

    if (state.at(unsafePath.front()).isSteppable() &&
        state.at(unsafePath.front()).timeUntilTimeTravel)
    {
        LOGI("Next step is unsafe, waiting for explosion");
        LOGI("Current field will time travel in " <<
            state.at(*docLocation).timeUntilTimeTravel);

        // Explicitly return nothing
        return response::nothing();
    }

    LOGI("Path is safe for now");

    auto next = path[0];
    if (path.size() > 1) {
        auto nextnext = path[1];
        if (state.at(next).isSteppable() &&
            state.at(nextnext).is(ElementType::CHEST))
        {
            LOGI("Chest in way will survive "
                << state.at(nextnext).as<Chest>().survive_timetravels
                << " more time travels");

            auto useDirection = getDirection(*docLocation, next);

            LOGI("Avaliable fluxes:");
            for (auto& fc : doc.flux_capatitors) {
                LOGI(fc);
            }
            if (doc.flux_capatitors.empty()) {
                LOGI("No fluxes");
                return boost::none;
            }

            auto& best_fc = minRadiusFluxCapacitor(doc.flux_capatitors);

            return response::put(useDirection, best_fc.id, kMaxTimeTravel);
        }

    }
    if (state.at(next).is(ElementType::CHEST)) {
        // We have to move back
        // FIXME this might (?) get it into infinite loop
        LOGI("Finding a blank spot");
        auto blankSpot = findSafeBlankAround(*docLocation);
        if (!blankSpot) {
            LOGE("No blank spot around Doc");
            return boost::none;
        }
        auto moveDirection = getDirection(*docLocation, *blankSpot);
        return response::move(moveDirection);
    } else {
        auto direction = getDirection(*docLocation, next);
        return response::move(direction);
    }
}

boost::optional<protocol::Response> Game::goToASafeSpot() {
    LOGI("goToASafeSpot()");

    auto safeSpot = findSafeSpotNear(*docLocation);
    if (!safeSpot) {
        LOGE("Safespot not found");
        return boost::none;
    }

    LOGI("Safespot " << *safeSpot);

    auto path = getPathTo(*docLocation, *safeSpot);
    if (path.empty()) {
        LOGE("Path not found in goToASafeSpot");
        return boost::none;
    }

    auto direction = getDirection(*docLocation, path.front());
    LOGE("Info: Moving to " << direction);
    return response::move(direction);
}

protocol::Response Game::calculateResponse() {
    initExtraState();

    if (!docLocation) {
        LOGI("Doc not found, so returning nothing()");
        return response::nothing();
    }

    LOGI("doc.survive_timetravels = " << doc.survive_timetravels);
    if (deLoreanLocation) {
        LOGI("deLorean.survive_timetravels = " << deLorean.survive_timetravels);
    }

    if (state.at(*docLocation).timeUntilTimeTravel) {
        LOGI("Location of doc will time travel in "
            << *state.at(*docLocation).timeUntilTimeTravel);
        auto safeSpotResponse = goToASafeSpot();
        if (safeSpotResponse) {
            return *safeSpotResponse;
        }
    }

    if (doc.survive_timetravels > 0) {
        auto fluxCapatitorResponse = goToDeloreanThroughChests();
        if (fluxCapatitorResponse) {
            return *fluxCapatitorResponse;
        }
    }

    auto gotoResponse = goToDelorean();
    if (gotoResponse) {
        return *gotoResponse;
    }

    return response::nothing();
}

protocol::Response Game::postProcessResponse(protocol::Response response) {
    LOGI("postProcessResponse()");
    if (!docLocation) {
        return response;
    }

    Point nextPosition = *docLocation;
    if (response.has_command() &&
        response.command() == protocol::Response::MOVE &&
        response.has_direction()) // this last one should be always true
    {
        nextPosition = docLocation->moveTo(response.direction());
    }
    if (!state.at(nextPosition).next_tick_arrives) {
        return response;
    }

    LOGI("Next position of doc won't be safe");

    if (nextPosition != *docLocation) {
        if (isSafeBlank(*docLocation, /*threshold =*/ 2)) {
            LOGI("Doc would move, but current pos is safe");
            return response::nothing();
        } else {
            LOGI("nextPosition is unsafe and our position is unsafe as well");
        }
    }

    auto safeSpot = findSafeBlankAround(*docLocation, 2);
    if (!safeSpot) {
        LOGE("No safe spot for doc. goodbye :(");
        return response;
    }
    auto direction = docLocation->getDirection(*safeSpot);
    if (!direction) {
        LOGE("Direction invalid in postProcessResponse");
        return response;
    }
    LOGI("Moving with doc out of danger");
    return response::move(*docLocation->getDirection(*safeSpot));
}

boost::optional<Point> Game::findObject(ElementType type) {
    for (size_t x = 0; x < state.fields.size(); ++x) {
        for (size_t y = 0; y < state.fields[0].size(); ++y) {
            if (state.at(x, y).is(type)) {
                return Point(x, y);
            }
        }
    }
    return boost::none;
}

protocol::Response::Direction Game::getDirection(
    const Point& from, const Point& to)
{
    if (from.x + 1 == to.x && from.y == to.y) {
        return protocol::Response::RIGHT;
    }
    if (from.x - 1 == to.x && from.y == to.y) {
        return protocol::Response::LEFT;
    }
    if (from.x == to.x && from.y + 1 == to.y) {
        return protocol::Response::DOWN;
    }
    if (from.x == to.x && from.y - 1 == to.y) {
        return protocol::Response::UP;
    }
    LOGE("Error: getDirection called with non adjacent vertices: "
        << from << " and " << to);
    return protocol::Response::DOWN;
}

bool Game::isSafeBlank(const Point& p, int time_travel_in_threshold) const {
    const auto& f = state.at(p);
    return f.isSteppable() &&
        (!f.timeUntilTimeTravel || *f.timeUntilTimeTravel >= time_travel_in_threshold) &&
        !f.next_tick_arrives;
}

boost::optional<Point> Game::findSafeBlankAround(
    const Point& p, int time_travel_in_threshold) const
{
    auto adjacents = p.getAdjacents();

    for (auto k : adjacents) {
        if (isSafeBlank(k, time_travel_in_threshold)) {
            auto second_adjacents = k.getAdjacents();
            for (auto kk : second_adjacents) {
                if (p == kk) {
                    continue;
                }
                if (state.at(kk).isSteppable()) {
                    return k;
                    LOGI("Double safe spot = " << kk);
                }
            }
        }
    }
    LOGI("No double safe spot do Doc, searching for single one");
    for (auto k : adjacents) {
        if (isSafeBlank(k, time_travel_in_threshold)) {
            LOGI("Single safe spot = " << k);
            return k;
        }
    }
    LOGI("No safe spot at all");
    return boost::none;
}

const FluxCapatitor& Game::minRadiusFluxCapacitor(
    const std::vector<FluxCapatitor>& fcs)
{
    //BM_ASSERT(!fcs.empty());

    const FluxCapatitor* best = &fcs.front();

    for (int i = 1; i < fcs.size(); ++i) {
        if (best->radius > fcs[i].radius) {
            best = &fcs[i];
        }
    }
    return *best;
}

boost::optional<Point> Game::findSafeSpotNear(const Point& from) const {
    std::queue<Point> todo;

    todo.push(from);

    while (!todo.empty()) {
        Point current = todo.front();
        todo.pop();

        if (!state.at(current).timeUntilTimeTravel) {
            return current;
        }
        auto adjacents = current.getAdjacents();
        for (const Point& p : adjacents) {
            if (state.at(p).isSteppable()) {
                todo.push(p);
            }
        }
    }

    return boost::none;
}

int Game::getDistanceOn(const Point& p) const {
    if (state.at(p).isSteppable()) {
        return 1;
    }
    if (state.at(p).is<FluxCapatitor>()) {
        return 1;
    }
    if (state.at(p).is<Chest>()) {
        return 5;
    }
    // Wall and other stuff. doesn't matter
    return 100000;
}

// simple Dijkstraish
std::vector<Point> Game::getPathTo(
    const Point& from, const Point& to, unsigned flags) const
{
    auto parentMatrix = createMatrixWithShape<Point>(
        state.fields, Point(-1, -1));
    auto distanceMatrix = createMatrixWithShape<int>(
        state.fields, -1);

    std::set<std::pair<int, Point>> todo;

    distanceMatrix[from.x][from.y] = 0;
    todo.insert({distanceMatrix[from.x][from.y], from});

    while (!todo.empty()) {
        Point current = todo.begin()->second;
        todo.erase(todo.begin());

        if (current == to) {
            // Build the result
            std::vector<Point> path;
            for (Point at = current; at != from; at = parentMatrix[at.x][at.y]) {
                if (at == Point(-1, -1)) {
                    LOGE("Error: from not found in getPathTo()");
                    return {};
                }
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        auto adjacents = current.getAdjacents();
        auto current_distance = distanceMatrix[current.x][current.y];
        for (const Point& p : adjacents) {
            auto edge_distance = getDistanceOn(p);
            auto p_distance = distanceMatrix[p.x][p.y];
            if (p != to) {
                if (p_distance != -1 &&
                    p_distance <= current_distance + edge_distance) {
                    continue;
                }
                if (p.x < 0 || p.x >= int(state.width) ||
                    p.y < 0 || p.y >= int(state.height))
                {
                    continue;
                }
                if ((flags & PATH_AVOID_FLUX_AS_FIRST_STEP) &&
                    current == from &&
                    state.at(p).timeUntilTimeTravel)
                {
                    continue;
                }
                if (state.at(p).is(ElementType::BLANK)) {
                    goto use_it;
                }
                if (state.at(p).is(ElementType::CAPABILITY)) {
                    goto use_it;
                }
                if ((flags & PATH_THROUGH_CHEST) &&
                    state.at(p).is(ElementType::CHEST))
                {
                    goto use_it;
                }
                if ((flags & PATH_THROUGH_FLUX) &&
                    state.at(p).is(ElementType::FLUXCAPATITOR))
                {
                    goto use_it;
                }
                continue;
            }
use_it:
            todo.erase({p_distance, p});
            distanceMatrix[p.x][p.y] = current_distance + edge_distance;
            todo.insert({distanceMatrix[p.x][p.y], p});
            parentMatrix[p.x][p.y] = current;
        }
    }
    return {};
}

    void Game::logJSON()
    {
        LOGI("//JSON Log: { \"doc\": "+toJSON(doc)+" }");
    }

} // namespace bm
