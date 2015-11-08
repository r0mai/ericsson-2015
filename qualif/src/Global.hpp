#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "Global.pb.h"

#include "Elements.hpp"

#include <boost/variant.hpp>

namespace bm {

enum class ElementType {
    BLANK,
    FLUXCAPATITOR,
    DOC,
    ENEMY,
    WALL,
    CHEST,
    DELOREAN,
    CAPABILITY,
};

struct Wall {};

using FieldElement = boost::variant<
    boost::blank,
    FluxCapatitor,
    Doc,
    Enemy,
    Wall,
    Chest,
    DeLorean,
    Capability
>;

bool isFieldElementA(const FieldElement& fe, ElementType type);

struct Field {
    FieldElement element; // can be blank
    boost::optional<ElementType> next_tick_arrives;

    template<class T>
    bool is() const {
        return boost::get<const T>(&element) != nullptr;
    }

    bool is(ElementType type) const;
};

ElementType fromProto(protocol::Field::ElementType et);
FieldElement fromProto(const protocol::Field::ElementInfo& ei);
Field fromProto(const protocol::Field& f);

} // namespace bm

#endif
