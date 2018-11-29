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
    void reset() {occupied_cells.clear();};
    void check_collisions(Map &level_map, std::vector<std::shared_ptr<Entity>> entities);
    void hash_entities(Map &level_map, std::vector<std::shared_ptr<Entity>> entities);

private:
    bool entity_collision(Entity &entity1, Entity &entity2);
    bool wall_collision(Map &level_map, Entity &entity);
    void clear_cells(Map &level_map);
    void adjust_positions(Entity &entity1, Entity &entity2);

    std::set<Cell*> occupied_cells;



};


#endif //CSCI437_COLLISION_ENGINE_H
