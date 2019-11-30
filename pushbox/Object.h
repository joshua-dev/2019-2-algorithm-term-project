#ifndef __OBEJCT_H__
#define __OBJECT_H__

#include<map>

class Object {
private:
    int value;
    std::pair<int, int> position;
public:
    Object();
    Object(int value, std::pair<int, int> position);
    int getValue();
    std::pair<int, int> getPosition();
    void setValue(int value);
    void setPosition(std::pair<int, int> position);
};

#endif __OBJECT_H__