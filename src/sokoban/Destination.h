#ifndef _DESTINATION_H_
#define _DESTINATION_H_

class Destination : Object
{
private:
public:
    Destination();
    Destination(int value, std::pair<int, int> position, int state);
    ~Destination();
    void onBox();
};

#endif
