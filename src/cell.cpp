#include "cell.h"

/**
 * Add an entitiy to set
 */
void Cell::insert_entity(std::shared_ptr<Entity> &entity)
{
  entities.insert(entity);
}

/**
 * Clear the set of all entities
 */
void Cell::clear_entities()
{
  entities.clear();
}

/**
 * Get a vector of pointers to entities associated with the cell
 */
std::vector<std::shared_ptr<Entity>> Cell::get_entities()
{
  return std::vector<std::shared_ptr<Entity>>(entities.begin(), entities.end());
}
