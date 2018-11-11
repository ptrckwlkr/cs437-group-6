#include "level.h"

Level::Level(std::shared_ptr<Map> &map) : map(std::move(map))
{

}

void Level::update()
{
  map->update_entities(entities);
}
