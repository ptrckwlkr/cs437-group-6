#ifndef CSCI437_COLLISION_ENGINE_H
#define CSCI437_COLLISION_ENGINE_H

#include <unordered_map>
#include <set>
#include "map.h"
#include "cell.h"
#include "events/event.h"

/**
 * Encapsulates collision detection and handling
 */
class CollisionEngine
{

public:
    CollisionEngine() = default;
    void reset() {
      clear_cells();
      occupied_cells.clear();
    };
    void check_collisions(Map &level_map);
    void hash_entities(Map &level_map, std::unordered_map<long long, std::shared_ptr<Entity>> entities);

private:
    bool entity_collision(Entity &entity1, Entity &entity2);
    bool wall_collision(Map &level_map, Entity &entity);
    void clear_cells();
    void adjust_positions(Entity &entity1, Entity &entity2);
    void dispatchEvents();
    struct Line
    {
        float x1;
        float y1;
        float x2;
        float y2;
    };
    Vector2D intersection(Line line1, Line line2);

    struct EventItem
    {
        EventType type;
        Entity *entity1;
        Entity *entity2;
        bool operator< (const EventItem &other) const
        {
          if (type != other.type)            return type < other.type;
          else if (entity1 != other.entity1) return entity1 < other.entity1;
          else                               return entity2 < other.entity2;
        }
    };

    std::set<Cell*> occupied_cells;
    std::set<EventItem> event_set;
};


#endif //CSCI437_COLLISION_ENGINE_H
