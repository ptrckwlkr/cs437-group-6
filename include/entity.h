#ifndef CSCI437_ENTITY_H
#define CSCI437_ENTITY_H

#include "event.h"
#include "vector2d.h"
#include "listener.h"

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

class Entity : public Listener
{

public:
    Entity(float x, float y, float s) : Listener(), pos(Vector2D(x, y)), old_pos(Vector2D(x, y))
    {
      static long long entity_id = 0;

      id = entity_id++;
      size = s;
      health = 0; //TODO
      mana = 0;   //TODO
      speed = 0;
      obstructible = false;
      type = TYPE_NONE;
    }
    ~Entity() = default;

    void set_position(float x, float y) {pos.x = x; pos.y = y;}
    void set_position(Vector2D new_pos) {pos = new_pos;}
    void set_health(int h) {health = h;}
    void set_mana(int m) {mana = m;}
    void takedamage(int damage) {health -= damage;}

    const Vector2D &get_position() {return pos;}
    const Vector2D &get_old_position() {return old_pos;}
    const float get_size() {return size;}
    const bool is_obstructible() {return obstructible;}
    const int get_health() {return health;}
    const int get_mana() {return mana;}
    const EntityType get_type() {return type;}
    long long id;

    virtual void move(Vector2D &dir, float delta)
    {
      old_pos = pos;
      float delta_speed = speed * delta;
      pos = pos + dir.normal() * delta_speed;
    }

protected:
    Vector2D pos;
    Vector2D old_pos;
    float size;
    float speed;
    int health;
    int mana;
    bool obstructible;
    EntityType type;

};

#endif //CSCI437_ENTITY_H
