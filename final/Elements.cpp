#include "Elements.hpp"
#include <string>

namespace bm {

std::ostream& operator<<(std::ostream& os, const FluxCapatitor& fc) {
    os << "flux(id = " << fc.id
        << ", radius = " << fc.radius
        << ", time_to_activated = " << fc.time_to_activated
        << ", timetravel_length = " << fc.timetravel_length;
    return os;
}

Capability fromProto(protocol::Capability c) {
    switch (c) {
	case protocol::INCREASEMAXFLUXCAPATITOR:
	    return Capability::INCREASEMAXFLUXCAPATITOR;
	case protocol::INCREASEFLUXCAPATITORRADIUS:
	    return Capability::INCREASEFLUXCAPATITORRADIUS;
	case protocol::DECREASEFLUXCAPATITORRADIUS:
	    return Capability::DECREASEFLUXCAPATITORRADIUS;
	case protocol::INCREASEFLUXCAPATITORTIME:
	    return Capability::INCREASEFLUXCAPATITORTIME;
	case protocol::DECREASEFLUXCAPATITORTIME:
	    return Capability::DECREASEFLUXCAPATITORTIME;
	case protocol::DECREASEFLUXCAPATITORMAKING:
	    return Capability::DECREASEFLUXCAPATITORMAKING;
	case protocol::INCREASEENERGY:
	    return Capability::INCREASEENERGY;
	case protocol::KICKFLUXCAPATITOR:
	    return Capability::KICKFLUXCAPATITOR;
	case protocol::THROWFLUXCAPATITOR:
	    return Capability::THROWFLUXCAPATITOR;
    }
    BM_ASSERT(false);
}

FluxCapatitor fromProto(const protocol::FluxCapatitor& fc) {
    FluxCapatitor res;
    res.id = fc.id();
    res.time_to_activated = fc.time_to_activated();
    res.radius = fc.radius();
    if (fc.has_timetravel_length()) {
	res.timetravel_length = fc.timetravel_length();
    }
    return res;
}

FluxCapatitorInformations fromProto(const protocol::FluxCapatitorInformations& fci) {
    FluxCapatitorInformations res;
    if (fci.has_next_done_time()) {
	res.next_done_time = fci.next_done_time();
    }
    res.making_time = fci.making_time();
    res.max_flux_capatitors = fci.max_flux_capatitors();
    res.next_flux_capatitor = fromProto(fci.next_flux_capatitor());
    return res;
}

Doc fromProto(const protocol::Doc& doc) {
    Doc res;
    res.id = doc.id();
    res.survive_timetravels = doc.survive_timetravels();
    for (int i = 0; i < doc.flux_capatitors_size(); ++i) {
	res.flux_capatitors.push_back(fromProto(doc.flux_capatitors(i)));
    }
    res.informations = fromProto(doc.informations());
    for (int i = 0; i < doc.capabilities_size(); ++i) {
	res.capabilities.push_back(fromProto(doc.capabilities(i)));
    }
    return res;
}

Enemy fromProto(const protocol::Enemy& e) {
    Enemy res;
    res.id = e.id();
    res.survive_timetravels = e.survive_timetravels();
    res.intelligence = e.intelligence();
    res.radius = e.radius();
    return res;
}

Chest fromProto(const protocol::Chest& c) {
    Chest res;
    res.id = c.id();
    res.survive_timetravels = c.survive_timetravels();
    if (c.has_capability()) {
	res.capability = fromProto(c.capability());
    }
    return res;
}

DeLorean fromProto(const protocol::DeLorean& d) {
    DeLorean res;
    res.id = d.id();
    res.survive_timetravels = d.survive_timetravels();
    return res;
}

    std::string toJSON(Doc &doc)
    {
        std::string s;
        s="{ ";
        s+=" \"elementType: \"doc\",";
        s+=" \"id\" : ";
        s+=std::to_string(doc.id);
        s+=", \"survive_timetravels\" : ";
        s+=std::to_string(doc.survive_timetravels);
        s+=", \"flux_capatitors\" : [ ";

        for(unsigned int i=0;i<doc.flux_capatitors.size();++i)
        {
            s+=toJSON(doc.flux_capatitors[i]);
            if(i<doc.flux_capatitors.size()-1)
                s+=",";
        }

        s+=" ], ";
        s+=" \"informations\" : ";
        s+=toJSON(doc.informations);
        s+=" }";


        return s;
    }

    std::string toJSON(FluxCapatitor &fluxCapatitor)
    {
        std::string s;
        s="{ ";
        s+=" \"elementType: \"fluxCapatitor\",";
        s+=" \"id\" : ";
        s+=std::to_string(fluxCapatitor.id);
        s+=", \"time_to_activated\" : ";
        s+=std::to_string(fluxCapatitor.time_to_activated);
        s+=", \"radius\" : ";
        s+=std::to_string(fluxCapatitor.radius);
        if(fluxCapatitor.timetravel_length)
        {
            s+=", \"timetravel_length\" : ";
            s+=std::to_string(*fluxCapatitor.timetravel_length);
        }
        s+=" }";

        return s;
    }

    std::string toJSON(FluxCapatitorInformations &fluxCapatitorInformations)
    {
        std::string s;

        s="{ ";
        s+=" \"elementType: \"fluxCapatitorInformations\",";

        if(fluxCapatitorInformations.next_done_time)
        {
            s+=" \"next_done_time\" : ";
            s+=std::to_string(*fluxCapatitorInformations.next_done_time);
        }

        s+=", \"making_time\" : ";
        s+=std::to_string(fluxCapatitorInformations.making_time);
        s+=", \"max_flux_capatitors\" : ";
        s+=std::to_string(fluxCapatitorInformations.max_flux_capatitors);
        s+=", \"next_flux_capatitor\" : ";
        s+=toJSON(fluxCapatitorInformations.next_flux_capatitor);

        s+=" }";

        return s;
    }

    std::string toJSON(Chest &chest)
    {
        std::string s;
        s="{ ";
        s+=" \"elementType: \"chest\",";
        s+=" \"id\" : ";
        s+=std::to_string(chest.id);
        s+=", \"survive_timetravels\" : ";
        s+=std::to_string(chest.survive_timetravels);

        if(chest.capability)
        {
            //TODO
            //s+=", \"capability\" : ";
            //s+=toJSON(*fluxCapatitor.capability);
        }
        s+=" }";

        return s;
    }

    std::string toJSON(DeLorean &delorean)
    {
        std::string s;
        s="{ ";
        s+=" \"elementType: \"delorean\",";
        s+=" \"id\" : ";
        s+=std::to_string(delorean.id);
        s+=", \"survive_timetravels\" : ";
        s+=std::to_string(delorean.survive_timetravels);
        s+=" }";

        return s;
    }

} // namespace bm
