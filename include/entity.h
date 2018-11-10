#ifndef CSCI437_ENTITY_H
#define CSCI437_ENTITY_H

#include "event.h"

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

enum EntityType
{
    TYPE_NONE,
    TYPE_PLAYER,
    TYPE_ENEMY,
    TYPE_SKELETON,
    TYPE_PROJECTILE,
    TYPE_GOLD,
};

class Entity
{


public:
    Entity(float x, float y, float s)
    {
      static long long entity_id = 0;

      id = entity_id++;
      pos.x = x;
      pos.y = y;
      size = s;
      health = 0; //TODO
      mana = 0;   //TODO
      type = TYPE_NONE;
    }
    ~Entity() = default;

    void set_position(float x, float y) {pos.x = x; pos.y = y;}
    void set_position(Position new_pos) {pos = new_pos;}
    void set_health(int h) {health = h;}
    void set_mana(int m) {mana = m;}
    void takedamage(int damage) {health -= damage;}

    Position get_position() {return pos;}
    float get_size() {return size;}
    int get_health() {return health;}
    int get_mana() {return mana;}
    long long get_id() {return id;}
    EntityType get_type() {return type;}

    virtual void move(Direction dir, float delta) = 0;
    virtual void animate() = 0;
    virtual void HandleEvent(Event* event) = 0;

protected:
    Position pos{};
    float size;
    int health;
    int mana;
    long long id;
    EntityType type;

};

#endif //CSCI437_ENTITY_H
