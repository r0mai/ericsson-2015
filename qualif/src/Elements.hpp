#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include <cstdint>
#include <vector>

#include <boost/variant.hpp>
#include <boost/optional.hpp>

#include "Elements.pb.h"

namespace bm {

enum class Capability {
	INCREASEMAXFLUXCAPATITOR = 1,
	INCREASEFLUXCAPATITORRADIUS = 2,
	DECREASEFLUXCAPATITORRADIUS = 3,
	INCREASEFLUXCAPATITORTIME = 4,
	DECREASEFLUXCAPATITORTIME = 5,
	DECREASEFLUXCAPATITORMAKING = 6,
	INCREASEENERGY = 7,
	KICKFLUXCAPATITOR = 8,
	THROWFLUXCAPATITOR = 9
};

struct FluxCapatitor {
	uint32_t id;
	uint32_t time_to_activated;
	uint32_t radius;
    boost::optional<uint32_t> timetravel_length;
};

struct FluxCapatitorInformations {
    boost::optional<uint32_t> next_done_time;
	uint32_t making_time;
	uint32_t max_flux_capatitors;
	FluxCapatitor next_flux_capatitor;
};

struct Doc {
	uint32_t id;
	uint32_t survive_timetravels;
    std::vector<FluxCapatitor> flux_capatitors;
	FluxCapatitorInformations informations;
    std::vector<Capability> capabilities;
};

struct Enemy {
	uint32_t id;
	uint32_t survive_timetravels;
	uint32_t intelligence;
	uint32_t radius;
};

struct Chest {
	uint32_t id;
	uint32_t survive_timetravels;
    boost::optional<Capability> capability;
};

struct DeLorean {
	uint32_t id;
	uint32_t survive_timetravels;
};

Capability fromProto(protocol::Capability c);
FluxCapatitor fromProto(const protocol::FluxCapatitor& fc);
FluxCapatitorInformations fromProto(const protocol::FluxCapatitorInformations& fci);
Doc fromProto(const protocol::Doc& doc);
Enemy fromProto(const protocol::Enemy& e);
Chest fromProto(const protocol::Chest& c);
DeLorean fromProto(const protocol::DeLorean& d);

} // namespace bm

#endif
