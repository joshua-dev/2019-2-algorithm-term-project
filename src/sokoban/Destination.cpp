#include <map>
#include "Destination.h"

Destination::Destination() : Object()
{
}

Destination::Destination(std::pair<int, int> position) : Object(position)
{
}
