#ifndef RESPONSEHELPER_HPP
#define RESPONSEHELPER_HPP

#include <protobuf/Response.pb.h>
#include <protobuf/Elements.pb.h>
#include <protobuf/Global.pb.h>

class ResponseHelper 
{
public:
    void nothing() 
    {
        response.Clear();
    }

    void move(protocol::Response::Direction direction_to_move)
    {
        response.Clear();
        response.set_command(protocol::Response::MOVE);
        response.set_direction(direction_to_move);
    }

    void moveLeft()  { move(protocol::Response::LEFT ); }
    void moveUp()    { move(protocol::Response::UP   ); }
    void moveRight() { move(protocol::Response::RIGHT); }
    void moveDown()  { move(protocol::Response::DOWN ); }


    void put(protocol::Response::Direction direction_to_put, 
             unsigned int flux_capatitor_id, 
             unsigned int flux_capatitor_time)
    {
        response.Clear();
        response.set_command(protocol::Response::PUTFLUXCAPATITOR);
        response.set_direction(direction_to_put);
        response.set_flux_capatitor_id(flux_capatitor_id);
        response.set_flux_capatitor_time(flux_capatitor_time);
    }
    
    void putLeft (unsigned int flux_capatitor_id, unsigned int flux_capatitor_time)
    { put(protocol::Response::LEFT , flux_capatitor_id, flux_capatitor_time); }

    void putUp   (unsigned int flux_capatitor_id, unsigned int flux_capatitor_time)
    { put(protocol::Response::UP   , flux_capatitor_id, flux_capatitor_time); }

    void putRight(unsigned int flux_capatitor_id, unsigned int flux_capatitor_time)
    { put(protocol::Response::RIGHT, flux_capatitor_id, flux_capatitor_time); }

    void putDown (unsigned int flux_capatitor_id, unsigned int flux_capatitor_time)
    { put(protocol::Response::DOWN , flux_capatitor_id, flux_capatitor_time); }

    
    void putWithCapability(protocol::Response::Direction direction_to_put, 
                           unsigned int flux_capatitor_id, 
                           unsigned int flux_capatitor_time)
    {
        put(direction_to_put, flux_capatitor_id, flux_capatitor_time);
        response.set_capability(protocol::THROWFLUXCAPATITOR);
    }

    void use(protocol::Capability capability) 
    {
        response.Clear();
        response.set_command(protocol::Response::USECAPABILITY);
        response.set_capability(capability);
    }
    
    void useWithDirection(protocol::Capability capability,
                          protocol::Response::Direction direction_to_use)
    {
        use(capability);
        switch(capability)
        {
        case protocol::KICKFLUXCAPATITOR:
        case protocol::THROWFLUXCAPATITOR:
            response.set_direction(direction_to_use);
        default:
            break;
        }
    }
    
    void useLeft (protocol::Capability capability)
    { useWithDirection(capability, protocol::Response::LEFT ); }

    void useUp   (protocol::Capability capability)
    { useWithDirection(capability, protocol::Response::UP   ); }

    void useRight(protocol::Capability capability)
    { useWithDirection(capability, protocol::Response::RIGHT); }

    void useDown (protocol::Capability capability)
    { useWithDirection(capability, protocol::Response::DOWN ); }

    protocol::Response getResponse() const
    {
        return response;
    }
private:
    protocol::Response response;
};


#endif // RESPONSEHELPER_HPP
