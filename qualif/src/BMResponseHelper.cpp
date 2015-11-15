#include "BMResponseHelper.hpp"

#include <iostream>

namespace bm {
namespace response {

protocol::Response nothing() {
    std::cerr << "Response = nothing" << std::endl;
    ResponseHelper helper;
    helper.nothing();
    return helper.getResponse();
}

protocol::Response move(protocol::Response::Direction direction) {
    std::cerr << "Response = move(" << direction << ")" << std::endl;
    ResponseHelper helper;
    helper.move(direction);
    return helper.getResponse();
}

protocol::Response put(
    protocol::Response::Direction direction,
    unsigned int flux_capatitor_id,
    unsigned int flux_capatitor_time)
{
    std::cerr << "Response = put("
        << direction
        << ", id = " << flux_capatitor_id
        << ", time = " << flux_capatitor_time << ")" << std::endl;

    ResponseHelper helper;
    helper.put(direction, flux_capatitor_id, flux_capatitor_time);
    return helper.getResponse();
}

} // namespace response
} // namespace bm

namespace protocol {
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
} // namespace protocol
