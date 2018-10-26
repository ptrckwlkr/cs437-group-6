#ifndef CSCI437_ENTITY_H
#define CSCI437_ENTITY_H

struct Position
{
    float x;
    float y;
};

class Entity
{

public:
    Position get_position() {return pos;}
    float get_size() {return size;}

protected:
    Position pos;
    float size;

};

#endif //CSCI437_ENTITY_H
