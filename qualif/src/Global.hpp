#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "Global.pb.h"

namespace bm {

enum class ElementType {
    FLUXCAPATITOR,
    DOC,
    ENEMY,
    WALL,
    CHEST,
    DELOREAN,
    CAPABILITY
};

ElementType fromProto(protocol::Field::ElementType et);

} // namespace bm

#endif
