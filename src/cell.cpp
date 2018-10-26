#include "cell.h"

void Cell::insert_entity(std::shared_ptr<Entity> &entity)
{
  entities.push_back(entity);
}

void Cell::clear_entities()
{
  entities.clear();
}
