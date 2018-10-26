#include "level.h"

void Level::update()
{
  map->update_entities(entities);
}
