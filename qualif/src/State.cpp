#include "State.hpp"

#include <cassert>

namespace bm {

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

    res.fields = Fields(boost::extents[res.width][res.height]);

    assert(g.fields_size() == res.width * res.height);
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
