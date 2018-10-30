#ifndef CSCI437_COLLISION_ENGINE_H
#define CSCI437_COLLISION_ENGINE_H

#include <vector>
#include "map.h"

struct Line
{
    float x1;
    float y1;
    float x2;
    float y2;
};

/**
 * Encapsulates collision detection and handling
 */
class CollisionEngine
{

public:
    CollisionEngine() = default;
    void check_collisions(std::shared_ptr<Map> &level_map, std::vector<std::shared_ptr<Entity>> &entities);

private:
    bool entity_collision(std::shared_ptr<Entity> &entity1, std::shared_ptr<Entity> &entity2);
    void check_wall_collisions(std::shared_ptr<Map> &level_map, std::vector<std::shared_ptr<Entity>> &entities);

};


#endif //CSCI437_COLLISION_ENGINE_H
