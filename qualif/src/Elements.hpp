#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include <cstdint>
#include <vector>
#include <ostream>

#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>

#include "Util.hpp"
#include "Elements.pb.h"

namespace bm {

enum class Capability {
    INCREASEMAXFLUXCAPATITOR,
    INCREASEFLUXCAPATITORRADIUS,
    DECREASEFLUXCAPATITORRADIUS,
    INCREASEFLUXCAPATITORTIME,
    DECREASEFLUXCAPATITORTIME,
    DECREASEFLUXCAPATITORMAKING,
    INCREASEENERGY,
    KICKFLUXCAPATITOR,
    THROWFLUXCAPATITOR
};

struct FluxCapatitor {
    uint32_t id;
    uint32_t time_to_activated;
    int radius;
    boost::optional<uint32_t> timetravel_length;
};

std::ostream& operator<<(std::ostream& os, const FluxCapatitor& fc);

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
    int radius;
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
