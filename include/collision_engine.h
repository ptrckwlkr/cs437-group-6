#ifndef CSCI437_COLLISION_ENGINE_H
#define CSCI437_COLLISION_ENGINE_H

#include <vector>
#include <set>
#include "map.h"

/**
 * Encapsulates collision detection and handling
 */
class CollisionEngine
{

public:
    CollisionEngine() = default;
    void check_collisions(Map &level_map, std::vector<std::shared_ptr<Entity>> &entities);
    void hash_entities(Map &level_map, std::vector<std::shared_ptr<Entity>> &entities);

private:
    bool entity_collision(Entity &entity1, Entity &entity2);
    bool types(Entity &entity1, Entity &entity2, EntityType type1, EntityType type2);
    void check_wall_collisions(Map &level_map, std::vector<std::shared_ptr<Entity>> &entities);
    void clear_cells(Map &level_map);

    std::set<Cell*> occupied_cells;

};


#endif //CSCI437_COLLISION_ENGINE_H
