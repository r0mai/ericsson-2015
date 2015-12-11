#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <cstdint>

#include "Point.hpp"

#include "Global.pb.h"
#include "Global.hpp"

namespace bm {

using Fields = std::vector<std::vector<Field>>;

struct State {
    uint32_t tick;

    uint32_t width;
    uint32_t height;
    Fields fields;

    boost::optional<std::string> error;

    Field& at(const Point& p);
    const Field& at(const Point& p) const;

    Field& at(int x, int y);
    const Field& at(int x, int y) const;
};

std::ostream& operator<<(std::ostream& os, const Field& f);
std::string toString(const Fields& fields);

std::string fromProto(protocol::Global::Error error);
State fromProto(const protocol::Global& g);

    std::string toJSON(State &state);

} // namespace bm

#endif
