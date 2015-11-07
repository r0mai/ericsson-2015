#include "Global.hpp"

namespace bm {

ElementType fromProto(protocol::Field::ElementType et) {
    switch (et) {
        case protocol::Field::FLUXCAPATITOR:
	    return ElementType::FLUXCAPATITOR;
        case protocol::Field::DOC:
	    return ElementType::DOC;
        case protocol::Field::ENEMY:
	    return ElementType::ENEMY;
        case protocol::Field::WALL:
	    return ElementType::WALL;
        case protocol::Field::CHEST:
	    return ElementType::CHEST;
        case protocol::Field::DELOREAN:
	    return ElementType::DELOREAN;
        case protocol::Field::CAPABILITY:
	    return ElementType::CAPABILITY;
    }
    assert(false);
}

} // namespace bm
