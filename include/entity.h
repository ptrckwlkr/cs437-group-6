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
    ~Entity();

    void set_position(float x, float y);
    void set_position(Position new_pos);
    Position get_position() {return pos;}
    Position get_old_position() {return pos_old;}

    float get_size() {return size;}
    void move(Direction dir, float delta); // TODO maybe encapsulate into a "Moveable" component?
    void correct_position(float delta);

    void set_health(int h);
    int get_health(){
        return health;
    }

    void set_mana(int m);
    int get_mana(){
        return mana;
    }

    void takedamage(int damage);

protected:
    Position pos{};
    float size;
    Position pos_old{};       // TODO maybe encapsulate into a "Moveable" component?

    int health;
    int mana;

};

#endif //CSCI437_ENTITY_H
