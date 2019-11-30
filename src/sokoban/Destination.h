#ifndef _DESTINATION_H_
#define _DESTINATION_H_


#include <map>
#include "Object.h"

class Destination : Object
{
private:
public:
    Destination();

    Destination(std::pair<int, int> position);
};

#endif
