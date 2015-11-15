#include "State.hpp"
#include "Util.hpp"

#include <sstream>

namespace bm {

Field& State::at(const Point& p) {
    return at(p.x, p.y);
}

const Field& State::at(const Point& p) const {
    return at(p.x, p.y);
}

Field& State::at(int x, int y) {
    BM_ASSERT(x >= 0);
    BM_ASSERT(y >= 0);
    BM_ASSERT(x < width);
    BM_ASSERT(y < height);

    return fields[x][y];
}

const Field& State::at(int x, int y) const {
    BM_ASSERT(x >= 0);
    BM_ASSERT(y >= 0);
    BM_ASSERT(x < width);
    BM_ASSERT(y < height);

    return fields[x][y];
}

struct ToCharVisitor : boost::static_visitor<char> {
    char operator()(const FluxCapatitor&) const { return 'F'; }
    char operator()(const Doc&) const { return 'D'; }
    char operator()(const Enemy&) const { return 'E'; }
    char operator()(const Wall&) const { return 'W'; }
    char operator()(const Chest&) const { return 'C'; }
    char operator()(const DeLorean&) const { return 'L'; }
    char operator()(const Capability&) const { return 'F'; }
    char operator()(const boost::blank&) const { return ' '; }
};

std::ostream& operator<<(std::ostream& os, const Field& f) {
    os << boost::apply_visitor(ToCharVisitor{}, f.element);
    return os;
}

std::string toString(const Fields& fields) {
    std::stringstream ss;
    for (size_t y = 0; y < fields[0].size(); ++y) {
        for (size_t x = 0; x < fields.size(); ++x) {
            ss << fields[x][y];
        }
        ss << '\n';
    }
    return ss.str();
}

std::string fromProto(protocol::Global::Error error) {
    switch (error) {
    case protocol::Global::NOTSETDIRECTION:
        return "NOTSETDIRECTION";
    case protocol::Global::WRONGDIRECTION:
        return "WRONGDIRECTION";
    case protocol::Global::WRONGMOVE:
        return "WRONGMOVE";
    case protocol::Global::NOTSETFLUXCAPATITORID:
        return "NOTSETFLUXCAPATITORID";
    case protocol::Global::NOTSETFLUXCAPATITORTIME:
        return "NOTSETFLUXCAPATITORTIME";
    case protocol::Global::WRONGFLUXCAPATITORID:
        return "WRONGFLUXCAPATITORID";
    case protocol::Global::WRONGFLUXCAPATITORTIME:
        return "WRONGFLUXCAPATITORTIME";
    case protocol::Global::NOTSETCAPABILITY:
        return "NOTSETCAPABILITY";
    case protocol::Global::WRONGCAPABILITY:
        return "WRONGCAPABILITY";
    case protocol::Global::WRONGUSECAPABILITY:
        return "WRONGUSECAPABILITY";
    }
    return "UNKNOWN ERROR";
}

State fromProto(const protocol::Global& g) {
    State res;

    res.tick = g.tick();

    res.width = g.width();
    res.height = g.height();

    res.fields =
        std::vector<std::vector<Field>>(res.width,
        std::vector<Field>(res.height));

    BM_ASSERT(g.fields_size() == int(res.width * res.height));
    for (uint32_t y = 0; y < res.height; ++y) {
        for (uint32_t x = 0; x < res.width; ++x) {
            res.fields[x][y] = fromProto(g.fields(y * res.height + x));
        }
    }

    if (g.has_error()) {
        res.error = fromProto(g.error());
    }
    return res;
}

} // namespace bm
