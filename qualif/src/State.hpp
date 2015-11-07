#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <cstdint>

#include <boost/multi_array.hpp>

#include "Global.pb.h"
#include "Global.hpp"

namespace bm {

using Fields = boost::multi_array<Field, 2>;

struct State {
    uint32_t tick;

    uint32_t width;
    uint32_t height;
    Fields fields;

    boost::optional<std::string> error;
};

std::string toString(const Fields& fields);

std::string fromProto(protocol::Global::Error error);
State fromProto(const protocol::Global& g);

} // namespace bm

#endif
