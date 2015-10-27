#include "DisplayEvent.h"

const std::string& DisplayEvent::ADDED = "added";
const std::string& DisplayEvent::REMOVED = "removed";

DisplayEvent::DisplayEvent( const std::string& name ) :
    Event( name )
{
}

DisplayEvent::~DisplayEvent()
{
}
