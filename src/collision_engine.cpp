#include <vector>
#include <macros.h>
#include <EventManager.h>
#include "collision_engine.h"

/**
 * Given a pointer to a level's Map, check for collisions among all entities using the Map's optimized data structure
 */
void CollisionEngine::check_collisions(Map &level_map, std::vector<std::shared_ptr<Entity>> &entities)
{
  int num_entities;
  int i;
  int j;
  std::shared_ptr<Entity> entity1;
  std::shared_ptr<Entity> entity2;

  // Check every cell of the map
  for (auto &row : level_map.get_cells())
  {
    for (auto &cell : row)
    {
      // Compare every entity in each individual cell to each other
      num_entities = (int)cell.get_entities().size();
      for (i = 0; i < num_entities; ++i)
      {
        entity1 = cell.get_entities()[i];
        for (j = i + 1; j < num_entities; ++j)
        {
          entity2 = cell.get_entities()[j];

          // Handle the collision
          if (entity_collision(entity1, entity2))
          {
            // TODO Handle collision
            // TODO Needs a mechanism by which duplicate collisions (same entities, multiple cells) are properly handled
            EventManager::Instance()->SendEvent(COLLISION_EVENT, reinterpret_cast<void *>(1));
          }
        }
      }
    }
  }

  check_wall_collisions(level_map, entities);
}

/**
 * Check for a collision between two individual entities. Returns true if the entities are colliding
 */
bool CollisionEngine::entity_collision(std::shared_ptr<Entity> &entity1, std::shared_ptr<Entity> &entity2)
{
  float dx;
  float dy;
  float hypo;

  dx = entity1->get_position().x - entity2->get_position().x;
  dy = entity1->get_position().y - entity2->get_position().y;
  hypo = entity1->get_size() + entity2->get_size();

  return (hypo * hypo > dx * dx + dy * dy);
}

/**
 * For all entities, check for and correct all collisions with obstructed tiles.
 */
void CollisionEngine::check_wall_collisions(Map &level_map, std::vector<std::shared_ptr<Entity>> &entities)
{
  float x;      // Entity x-position
  float y;      // Entity y-position
  float dx;     // Change in entity's correctional x-position
  float dy;     // Change in entity's correctional y-position
  float size;   // Entity's size
  int m;        // m-index of tile entity is currently standing on
  int n;        // n-index of tile entity is currently standing on
  float top;    // Top boundary of current cell
  float right;  // Right boundary of current cell
  float bot;    // Bottom boundary of current cell
  float left;   // Left boundary of current cell

  for (auto &entity : entities)
  {
    x     = entity->get_position().x;
    y     = entity->get_position().y;
    size  = entity->get_size();
    m     = (int)(y / CELL_SIZE);
    n     = (int)(x / CELL_SIZE);
    top   = m * CELL_SIZE;
    left  = n * CELL_SIZE;
    bot   = top + CELL_SIZE;
    right = left + CELL_SIZE;
    dx = x;
    dy = y;

    // Calculate adjustments based on how far into the block the entity is interpenetrating
    if (level_map.get_cell(m - 1, n).get_cell_type() == WALL && y - size < top)    dy = top + size;    // Top bound
    if (level_map.get_cell(m, n + 1).get_cell_type() == WALL && x + size > right)  dx = right - size;  // Right bound
    if (level_map.get_cell(m + 1, n).get_cell_type() == WALL && y + size > bot)    dy = bot - size;    // Bottom bound
    if (level_map.get_cell(m, n - 1).get_cell_type() == WALL && x - size < left)   dx = left + size;   // Left bound

    // Adjust the position
    entity->set_position(dx, dy);
  }
}
