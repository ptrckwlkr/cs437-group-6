#ifndef CSCI437_ENTITY_H
#define CSCI437_ENTITY_H

struct Position
{
    float x;
    float y;
};

enum Direction
{
    NONE,
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST,
};

class Entity
{

public:
    Entity(float x, float y, float size);
    void set_position(float x, float y);
    Position get_position() {return pos;}
    float get_size() {return size;}
    void move(Direction dir, float delta); // TODO maybe encapsulate into a "Moveable" component?

protected:
    Position pos{};
    float size;
    Position pos_old{};       // TODO maybe encapsulate into a "Moveable" component?

};

#endif //CSCI437_ENTITY_H
