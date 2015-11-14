#include "Global.hpp"

namespace bm {

struct IsAVisitor : boost::static_visitor<bool> {
    IsAVisitor(ElementType type) : type(type) {}

    bool operator()(const boost::blank&) const { return type == ElementType::BLANK; }
    bool operator()(const FluxCapatitor&) const { return type == ElementType::FLUXCAPATITOR; }
    bool operator()(const Doc&) const { return type == ElementType::DOC; }
    bool operator()(const Enemy&) const { return type == ElementType::ENEMY; }
    bool operator()(const Wall&) const { return type == ElementType::WALL; }
    bool operator()(const Chest&) const { return type == ElementType::CHEST; }
    bool operator()(const DeLorean&) const { return type == ElementType::DELOREAN; }
    bool operator()(const Capability&) const { return type == ElementType::CAPABILITY; }

private:
    ElementType type;
};

bool Field::is(ElementType type) const {
    return boost::apply_visitor(IsAVisitor{type}, element);
}

bool Field::isBlocker() const {
    return is<Wall>() || is<Chest>() || is<DeLorean>();
}

bool Field::isSteppable() const {
    return is(ElementType::BLANK) || is(ElementType::CAPABILITY);
}

void Field::setTimeUntilTimeTravel(int new_value) {
    if (!timeUntilTimeTravel || *timeUntilTimeTravel > new_value) {
        timeUntilTimeTravel = new_value;
    }
}

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

FieldElement fromProto(const protocol::Field::ElementInfo& ei) {
    switch (fromProto(ei.type())) {
	case ElementType::FLUXCAPATITOR:
	    assert(ei.has_flux_capatitor());
	    return fromProto(ei.flux_capatitor());
	case ElementType::DOC:
	    assert(ei.has_doc());
	    return fromProto(ei.doc());
	case ElementType::ENEMY:
	    assert(ei.has_enemy());
	    return fromProto(ei.enemy());
	case ElementType::WALL:
	    return Wall{};
	case ElementType::CHEST:
	    assert(ei.has_chest());
	    return fromProto(ei.chest());
	case ElementType::DELOREAN:
	    assert(ei.has_delorean());
	    return fromProto(ei.delorean());
	case ElementType::CAPABILITY:
	    assert(ei.has_capability());
	    return fromProto(ei.capability());
        case ElementType::BLANK:
            // should never happen
            return {};
    }
    assert(false);
}

Field fromProto(const protocol::Field& f) {
    Field res;
    if (f.has_element()) {
	res.element = fromProto(f.element());
    }
    if (f.has_next_tick_arrives()) {
	res.next_tick_arrives = fromProto(f.next_tick_arrives());
    }
    return res;
}

} // namespace bm
