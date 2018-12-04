#ifndef CSCI437_ENTITY_H
#define CSCI437_ENTITY_H

#include <vector>
#include <array>
#include "vector2d.h"
#include "listener.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "events/event_entity_damaged.h"

#define VEC_NONE         Vector2D(0, 0)
#define VEC_NORTH        Vector2D(0, -1)
#define VEC_NORTHEAST    Vector2D(1, -1)
#define VEC_EAST         Vector2D(1, 0)
#define VEC_SOUTHEAST    Vector2D(1, 1)
#define VEC_SOUTH        Vector2D(0, 1)
#define VEC_SOUTHWEST    Vector2D(-1, 1)
#define VEC_WEST         Vector2D(-1, 0)
#define VEC_NORTHWEST    Vector2D(-1, -1)

typedef long long EntityType;

class Entity : public Listener
{

public:
    Entity(float x, float y, float s) : Listener()
    {
      static long long entity_id = 0;

      id = entity_id++;
      size = s;
      pos = Vector2D(x, y);
      old_pos = Vector2D(x, y);
    }
    ~Entity() {
      EventManager::Instance().unregisterAll(this);
    };

    void set_position(float x, float y) {pos.x = x; pos.y = y;}
    void set_position(Vector2D new_pos) {pos = new_pos;}
    void takedamage(int damage) {health -= damage;}
    void set_health(float h) {health = h;}
    void set_speed(float s) {speed = s;}
    void set_damage(float d) {damage = d;}
    void set_defence(float d) {defence = d;}
    void set_attack_speed(float s) {attack_speed = s;}
    void take_damage(float damage) {
      health -= damage / defence;
      if (health < 0) die();
      else {
        EventEntityDamaged e(id, getEntityType());
        EventManager::Instance().sendEvent(e);
      }
    }
    //virtual void set_attributes(rapidxml::xml_node<> *root_node) {}
    virtual void die() {};

    const Vector2D &get_position() const {return pos;}
    const Vector2D &get_old_position() const {return old_pos;}
    const float get_size() const {return size;}
    const bool is_obstructible() const {return obstructible;}
    const bool is_immovable() const {return immovable;}
    const bool is_wall_collidable() const {return wall_collidable;}
    const bool is_hostile() const {return hostile;}
    const float get_health() const {return health;}
    const float get_speed() const {return speed;}
    const float get_damage() const {return damage;}
    const float get_defence() const {return defence;}
    const float get_attack_speed() const {return attack_speed;}
    long long id;

    virtual const EntityType& getEntityType() const = 0;

    //trail behind the a circle projectile, helps show ball speed
    std::vector<Vector2D> trail;
    bool trail_enabled = false;

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
    float health = 1;
    float speed = 0;
    float damage = 0;
    float defence = 1;
    float attack_speed = 1;
    bool obstructible = false;
    bool immovable = false;
    bool hostile = false;
    bool wall_collidable = true;

    //ensures the xml file text does not go out of scope
    rapidxml::xml_node<> *root_node = nullptr;
    std::shared_ptr<std::vector<char>> buffer;

};

//global access to resource manager
extern ResourceManager resources;

#endif //CSCI437_ENTITY_H
