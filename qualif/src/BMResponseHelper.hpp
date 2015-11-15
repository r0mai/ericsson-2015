#ifndef BMRESPONSEHELPER_HPP
#define BMRESPONSEHELPER_HPP

#include "responseHelper.hpp"

#include <ostream>

namespace bm {
namespace response {

protocol::Response nothing();
protocol::Response move(protocol::Response::Direction direction);
protocol::Response put(
    protocol::Response::Direction direction,
    unsigned int flux_capatitor_id,
    unsigned int flux_capatitor_time);

} // namespace response
} // namespace bm

namespace protocol {

std::ostream& operator<<(std::ostream& os, protocol::Response::Direction d);

} // namespace protocol

#endif
