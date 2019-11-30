#ifndef _MOVABLE_H_
#define _MOVABLE_H_

// ---*--- interface for Objects' movements ---*---

class Movable
{
public:
    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveUp();
    virtual void moveDown();
};

#endif
