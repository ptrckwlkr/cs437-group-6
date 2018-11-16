#ifndef CSCI437_ENTITY_H
#define CSCI437_ENTITY_H

#include "event.h"
#include "vector2d.h"

#define VEC_NONE         Vector2D(0, 0)
#define VEC_NORTH        Vector2D(0, -1)
#define VEC_NORTHEAST    Vector2D(1, -1)
#define VEC_EAST         Vector2D(1, 0)
#define VEC_SOUTHEAST    Vector2D(1, 1)
#define VEC_SOUTH        Vector2D(0, 1)
#define VEC_SOUTHWEST    Vector2D(-1, 1)
#define VEC_WEST         Vector2D(-1, 0)
#define VEC_NORTHWEST    Vector2D(-1, -1)

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
    Entity(float x, float y, float s) : pos(Vector2D(x, y))
    {
      static long long entity_id = 0;

      id = entity_id++;
      size = s;
      health = 0; //TODO
      mana = 0;   //TODO
      type = TYPE_NONE;
    }
    ~Entity() = default;

    void set_position(float x, float y) {pos.x = x; pos.y = y;}
    void set_position(Vector2D new_pos) {pos = new_pos;}
    void set_health(int h) {health = h;}
    void set_mana(int m) {mana = m;}
    void takedamage(int damage) {health -= damage;}

    Vector2D get_position() {return pos;}
    float get_size() {return size;}
    int get_health() {return health;}
    int get_mana() {return mana;}
    long long get_id() {return id;}
    EntityType get_type() {return type;}

    virtual void move(Vector2D &dir, float delta) = 0;
    virtual void HandleEvent(Event* event) = 0;

protected:
    Vector2D pos;
    float size;
    int health;
    int mana;
    long long id;
    EntityType type;

};

#endif //CSCI437_ENTITY_H
