#include "State.hpp"
#include "Util.hpp"

#include <sstream>
#include <stream>

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
    char operator()(const Capability&) const { return 'P'; }
    char operator()(const boost::blank&) const { return ' '; }
};

std::ostream& operator<<(std::ostream& os, const Field& f) {
    os << boost::apply_visitor(ToCharVisitor{}, f.element);
    return os;
}

std::string toString(const Fields& fields) {
    std::vector<Point> fluxes;
    std::stringstream ss;
	ss << fields.size() << "\n";
	ss << fields[0].size() << "\n";
    for (size_t y = 0; y < fields[0].size(); ++y) {
        for (size_t x = 0; x < fields.size(); ++x) {
            ss << fields[x][y];
            if (fields[x][y].is<FluxCapatitor>()) {
                fluxes.push_back(Point(x, y));
            }
        }
        ss << '\n';
    }
	for (size_t y = 0; y < fields[0].size(); ++y) {
        for (size_t x = 0; x < fields.size(); ++x) {
            if (fields[x][y].is<Chest>()) {
                ss << fields[x][y].as<Chest>().survive_timetravels << " ";
            }
			else
				ss << 0 << " ";
        }
        ss << '\n';
    }
    for (const Point& p : fluxes) {
        ss << "Flux at " << p << ": "
            << fields[p.x][p.y].as<FluxCapatitor>() << '\n';
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

    std::string toJSON(struct State s)
    {
        std::string s;
        s="{ ";
        s+="\"grid\": [";

        for (size_t y = 0; y < fields[0].size(); ++y) {
            s+="[";
            for (size_t x = 0; x < fields.size(); ++x) {
                if (fields[x][y].is<FluxCapatitor>()) s+=toJSON(fields[x][y].as<FluxCapatitor>());
                if (fields[x][y].is<Doc>()) s+=toJSON(fields[x][y].as<Doc>());
                if (fields[x][y].is<Chest>()) s+=toJSON(fields[x][y].as<Chest>());
                if (fields[x][y].is<DeLorean>()) s+=toJSON(fields[x][y].as<DeLorean>());
                if (fields[x][y].is<Capability>()) s+=toJSON(fields[x][y].as<Capability>());
                if (fields[x][y].is<boost::blank>()) s+="{ \'elementType\" : \"blank\" }";
                if (fields[x][y].is<Wall>()) s+="{ \'elementType\" : \"wall\" }";

                if(x<fields.size()-1)
                    s+=",";
            }
            s+="]";
            if(y<fields[0].size()-1)
                s+=",";
        }

        s+="]";
        s+="}";
    }

} // namespace bm