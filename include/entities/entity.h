#ifndef CSCI437_ENTITY_H
#define CSCI437_ENTITY_H

#include <vector>
#include <array>
#include "vector2d.h"
#include "listener.h"
#include "EventManager.h"
#include "ResourceManager.h"

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
    Entity(float x, float y, float s) : Listener(), pos(Vector2D(x, y)), old_pos(Vector2D(x, y))
    {
      static long long entity_id = 0;

      id = entity_id++;
      size = s;
      health = 0; //TODO
      mana = 0;   //TODO
      speed = 0;
      obstructible = false;
      hostile = false;
    }
    ~Entity() {
      EventManager::Instance()->unregisterAll(this);
    };

    void set_position(float x, float y) {pos.x = x; pos.y = y;}
    void set_position(Vector2D new_pos) {pos = new_pos;}
    void set_speed( float s) {speed = s;}
    void set_health(int h) {health = h;}
    void set_mana(int m) {mana = m;}
    void takedamage(int damage) {health -= damage;}

    const Vector2D &get_position() const {return pos;}
    const Vector2D &get_old_position() const {return old_pos;}
    const float get_size() const {return size;}
    const float get_speed() const {return speed;}
    const bool is_obstructible() const {return obstructible;}
    const bool is_hostile() const {return hostile;}
    const int get_health() const {return health;}
    const int get_mana() const {return mana;}
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
    float speed;
    int health;
    int mana;
    bool obstructible;
    bool hostile;

    //ensures the xml file text does not go out of scope
    rapidxml::xml_node<> *root_node;
    std::shared_ptr <std::vector<char>> buffer;

};

//global access to resource manager
extern ResourceManager resources;

#endif //CSCI437_ENTITY_H
