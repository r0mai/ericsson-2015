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
        currentState = fromProto(global);

        std::cerr << "Info: Tick = " << currentState.tick << std::endl;
        std::cerr << toString(currentState.fields) << std::endl;

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
    docLocation = findObject(ElementType::DOC);
    deLoreanLocation = findObject(ElementType::DELOREAN);
}

boost::optional<protocol::Response> Game::goToDelorean() {
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

boost::optional<protocol::Response> Game::fireAFluxCapacitor() {
    if (!docLocation || !deLoreanLocation) {
        std::cerr << "Error: doc and/or delorean missing" << std::endl;
        return boost::none;
    }

    const Doc& doc = boost::get<Doc>(
        currentState.fields[docLocation->x][docLocation->y].element);

    auto path = getPathTo(*docLocation, *deLoreanLocation, true);
    if (path.empty()) {
        std::cerr << "Error: no path to delorean (with chests)" << std::endl;
        return boost::none;
    }

    auto next = path[0];
    if (path.size() > 1) {
        auto nextnext = path[1];
        if (isFieldElementA(currentState.fields[next.x][next.y].element, ElementType::BLANK) &&
            isFieldElementA(currentState.fields[next.x][next.y].element, ElementType::CHEST))
        {
            auto useDirection = getDirection(*docLocation, next);
            ResponseHelper helper;
            helper.put(useDirection, doc.flux_capatitors.front().id, kMinTimeTravel);
            return helper.getResponse();
        }

    }
    if (isFieldElementA(currentState.fields[next.x][next.y].element, ElementType::CHEST)) {
        if (doc.flux_capatitors.empty()) {
            std::cerr << "Error: no flux capacitors" << std::endl;
            return boost::none;
        }
        auto blankSpot = findBlankAround(*docLocation);
        if (!blankSpot) {
            std::cerr << "Error: No blank spot around Doc" << std::endl;
            return boost::none;
        }
        auto useDirection = getDirection(*docLocation, *blankSpot);
        ResponseHelper helper;
        helper.put(useDirection, doc.flux_capatitors.front().id, kMinTimeTravel);
        return helper.getResponse();
    } else {
        auto direction = getDirection(*docLocation, next);
        ResponseHelper helper;
        helper.move(direction);
        return helper.getResponse();
    }
}

protocol::Response Game::calculateResponse() {
    initExtraState();

    auto gotoResponse = goToDelorean();
    if (gotoResponse) {
        return *gotoResponse;
    }

    ResponseHelper helper;
    helper.nothing();
    return helper.getResponse();
}

boost::optional<Point> Game::findObject(ElementType type) {
    for (size_t x = 0; x < currentState.fields.size(); ++x) {
        for (size_t y = 0; y < currentState.fields[0].size(); ++y) {
            if (isFieldElementA(currentState.fields[x][y].element, type)) {
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
    std::cerr << "Error: getDirection called with non adjacent vertices: " <<
        from << " and " << to << std::endl;
    return protocol::Response::DOWN;
}

boost::optional<Point> Game::findBlankAround(const Point& p) const {
    std::array<Point, 4> adjacents = {{
        {p.x + 1, p.y},
        {p.x - 1, p.y},
        {p.x, p.y + 1},
        {p.x, p.y - 1},
    }};
    for (auto k : adjacents) {
        if (isFieldElementA(currentState.fields[k.x][k.y].element, ElementType::BLANK) ||
            isFieldElementA(currentState.fields[k.x][k.y].element, ElementType::CAPABILITY))
        {
            return k;
        }
    }
    return boost::none;
}

// simple BFS
std::vector<Point> Game::getPathTo(
    const Point& from, const Point& to, bool throughChest) const
{
    auto parentMatrix = createMatrixWithShape<Point>(
        currentState.fields, Point(-1, -1));
    auto distanceMatrix = createMatrixWithShape<int>(
        currentState.fields, -1);

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

        std::array<Point, 4> adjacents = {{
            {current.x + 1, current.y},
            {current.x - 1, current.y},
            {current.x, current.y + 1},
            {current.x, current.y - 1},
        }};
        for (const Point& p : adjacents) {
            if (p != to) {
                if (distanceMatrix[p.x][p.y] != -1) {
                    continue;
                }
                if (p.x < 0 || p.x >= int(currentState.width) ||
                    p.y < 0 || p.y >= int(currentState.height))
                {
                    continue;
                }
                if (isFieldElementA(
                        currentState.fields[p.x][p.y].element,
                        ElementType::BLANK))
                {
                    goto use_it;
                }
                if (isFieldElementA(
                        currentState.fields[p.x][p.y].element,
                        ElementType::CAPABILITY))
                {
                    goto use_it;
                }
                if (throughChest && isFieldElementA(
                        currentState.fields[p.x][p.y].element,
                        ElementType::CHEST))
                {
                    goto use_it;
                }
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
