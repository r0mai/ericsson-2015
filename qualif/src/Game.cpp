#include <iostream>
#include <queue>
#include <chrono>

#include "Game.hpp"
#include "responseHelper.hpp"
#include "stream.hpp"
#include "Util.hpp"

namespace bm {

void Game::run() {
    protocol::Global global;
    while (readProtoFromStream(global, std::cin)) {
        auto start = std::chrono::system_clock::now();
        if (global.has_error()) {
            std::cerr << "Error from last tick: " <<
                fromProto(global.error()) << std::endl;
        }
        state = fromProto(global);

        std::cerr << "Info: Tick = " << state.tick << std::endl;
        std::cerr << toString(state.fields) << std::endl;

        protocol::Response response = calculateResponse();
        if (!writeProtoOnStream(response, std::cout)) {
            std::cerr << "write error" << std::endl;
            break;
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end - start;

        std::cerr << "Tick took " << diff.count() * 1000 << "ms" << std::endl;
    }
    std::cerr << "Game over, std::cin.eof(): " << std::cin.eof() << std::endl;
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
    assert(state.at(p).is<FluxCapatitor>());

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
        y < state.height && y < p.y + radius && !state.at(p.x, y).isBlocker(); ++y) {
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
    std::cerr << "goToDelorean()" << std::endl;
    if (!docLocation || !deLoreanLocation) {
        std::cerr << "Error: doc and/or delorean missing" << std::endl;
        return boost::none;
    }

    auto path = getPathTo(*docLocation, *deLoreanLocation);

    if (path.empty()) {
        std::cerr << "Error: can't find path to deLorean from doc" << std::endl;
        return boost::none;
    }

    auto direction = getDirection(*docLocation, path.front());
    std::cerr << "Info: Moving to " << direction << std::endl;
    ResponseHelper helper;
    helper.move(direction);
    return helper.getResponse();
}

boost::optional<protocol::Response> Game::goToDeloreanThroughChests() {
    std::cerr << "goToDeloreanThroughChests()" << std::endl;
    if (!docLocation || !deLoreanLocation) {
        std::cerr << "Error: doc and/or delorean missing" << std::endl;
        return boost::none;
    }

    auto path = getPathTo(*docLocation, *deLoreanLocation, true);
    if (path.empty()) {
        std::cerr << "Error: no path to delorean (with chests)" << std::endl;
        return boost::none;
    }

    auto next = path[0];
    if (path.size() > 1) {
        auto nextnext = path[1];
        if (state.at(next).is(ElementType::BLANK) &&
            state.at(nextnext).is(ElementType::CHEST))
        {
            std::cerr << "Chest in way will survive "
                << state.at(nextnext).as<Chest>().survive_timetravels
                << " more time travels" << std::endl;

            auto useDirection = getDirection(*docLocation, next);

            std::cerr << "Avaliable fluxes:" << std::endl;
            for (auto& fc : doc.flux_capatitors) {
                std::cerr << fc << std::endl;
            }
            if (doc.flux_capatitors.empty()) {
                std::cerr << "No fluxes" << std::endl;
                return boost::none;
            }

            auto& best_fc = minRadiusFluxCapacitor(doc.flux_capatitors);

            ResponseHelper helper;
            helper.put(useDirection, best_fc.id, kMaxTimeTravel);
            return helper.getResponse();
        }

    }
    if (state.at(next).is(ElementType::CHEST)) {
        // We have to move back
        // FIXME this might (?) get it into infinite loop
        auto blankSpot = findBlankAround(*docLocation);
        if (!blankSpot) {
            std::cerr << "Error: No blank spot around Doc" << std::endl;
            return boost::none;
        }
        auto moveDirection = getDirection(*docLocation, *blankSpot);
        ResponseHelper helper;
        helper.move(moveDirection);
        return helper.getResponse();
    } else {
        auto direction = getDirection(*docLocation, next);
        ResponseHelper helper;
        helper.move(direction);
        return helper.getResponse();
    }
}

boost::optional<protocol::Response> Game::goToASafeSpot() {
    std::cerr << "goToASafeSpot()" << std::endl;

    auto safeSpot = findSafeSpotNear(*docLocation);
    if (!safeSpot) {
        std::cerr << "Safespot not found" << std::endl;
        return boost::none;
    }

    std::cerr << "Safespot " << *safeSpot << std::endl;

    auto path = getPathTo(*docLocation, *safeSpot);
    if (path.empty()) {
        std::cerr << "Path not found in goToASafeSpot" << std::endl;
        return boost::none;
    }

    auto direction = getDirection(*docLocation, path.front());
    std::cerr << "Info: Moving to " << direction << std::endl;
    ResponseHelper helper;
    helper.move(direction);
    return helper.getResponse();
}

protocol::Response Game::calculateResponse() {
    initExtraState();

    if (!docLocation) {
        std::cerr << "Doc not found, so returning nothing()" << std::endl;
        ResponseHelper helper;
        helper.nothing();
        return helper.getResponse();
    }

    if (state.at(*docLocation).timeUntilTimeTravel) {
        std::cerr << "Doc will time travel in "
            << *state.at(*docLocation).timeUntilTimeTravel << std::endl;
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

    ResponseHelper helper;
    helper.nothing();
    return helper.getResponse();
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
    std::cerr << "Error: getDirection called with non adjacent vertices: "
        << from << " and " << to << std::endl;
    return protocol::Response::DOWN;
}

boost::optional<Point> Game::findBlankAround(const Point& p) const {
    auto adjacents = p.getAdjacents();

    for (auto k : adjacents) {
        if (state.at(k).isSteppable()) {
            return k;
        }
    }
    return boost::none;
}

const FluxCapatitor& Game::minRadiusFluxCapacitor(
    const std::vector<FluxCapatitor>& fcs)
{
    assert(!fcs.empty());

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

// simple BFS
std::vector<Point> Game::getPathTo(
    const Point& from, const Point& to, bool throughChest) const
{
    auto parentMatrix = createMatrixWithShape<Point>(
        state.fields, Point(-1, -1));
    auto distanceMatrix = createMatrixWithShape<int>(
        state.fields, -1);

    std::queue<Point> todo;

    todo.push(from);
    distanceMatrix[from.x][from.y] = 0;

    while (!todo.empty()) {
        Point current = todo.front();
        todo.pop();

        if (current == to) {
            // Build the result
            std::vector<Point> path;
            for (Point at = current; at != from; at = parentMatrix[at.x][at.y]) {
                if (at == Point(-1, -1)) {
                    std::cerr << "Error: from not found in getPathTo()" << std::endl;
                    return {};
                }
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        auto adjacents = current.getAdjacents();
        for (const Point& p : adjacents) {
            if (p != to) {
                if (distanceMatrix[p.x][p.y] != -1) {
                    continue;
                }
                if (p.x < 0 || p.x >= int(state.width) ||
                    p.y < 0 || p.y >= int(state.height))
                {
                    continue;
                }
                if (state.at(p).is(ElementType::BLANK)) {
                    goto use_it;
                }
                if (state.at(p).is(ElementType::CAPABILITY)) {
                    goto use_it;
                }
                if (throughChest &&
                    state.at(p).is(ElementType::CHEST))
                {
                    goto use_it;
                }
                continue;
            }
use_it:
            todo.push(p);
            distanceMatrix[p.x][p.y] = distanceMatrix[current.x][current.y] + 1;
            parentMatrix[p.x][p.y] = current;
        }
    }
    return {};
}

std::ostream& operator<<(std::ostream& os, protocol::Response::Direction d) {
    switch (d) {
        case protocol::Response::UP: os << "UP"; break;
        case protocol::Response::DOWN: os << "DOWN"; break;
        case protocol::Response::LEFT: os << "LEFT"; break;
        case protocol::Response::RIGHT: os << "RIGHT"; break;
        default: os << "UNKNOWN DIRECTION"; break;
    }
    return os;
}

} // namespace bm
