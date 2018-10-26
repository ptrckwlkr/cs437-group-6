#include "level.h"

Level::Level(std::shared_ptr<Map> &map, std::vector<std::shared_ptr<Entity>> &entities) : map(std::move(map)), entities(std::move(entities))
{
  collision_engine = std::make_shared<CollisionEngine>();
}

void Level::update()
{
  map->update_entities(entities);
  collision_engine->check_collisions(map);
}
