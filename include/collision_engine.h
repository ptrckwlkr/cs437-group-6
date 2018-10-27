#ifndef CSCI437_COLLISION_ENGINE_H
#define CSCI437_COLLISION_ENGINE_H

#include <vector>
#include "map.h"

/**
 * Encapsulates collision detection and handling
 */
class CollisionEngine
{

public:
    CollisionEngine() = default;
    void check_collisions(std::shared_ptr<Map> &level_map);

private:
    bool collision(std::shared_ptr<Entity> &entity1, std::shared_ptr<Entity> &entity2);

};


#endif //CSCI437_COLLISION_ENGINE_H
