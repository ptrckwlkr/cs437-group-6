#include <vector>
#include "collision_engine.h"

/**
 * Given a pointer to a level's Map, check for collisions among all entities using the Map's optimized data structure
 */
void CollisionEngine::check_collisions(std::shared_ptr<Map> &level_map)
{
  int entities;
  int i;
  int j;
  std::shared_ptr<Entity> entity1;
  std::shared_ptr<Entity> entity2;

  // Check every cell of the map
  for (auto &row : level_map->get_cells())
  {
    for (auto &cell : row)
    {
      // Compare every entity in each individual cell to each other
      entities = (int)cell.get_entities().size();
      for (i = 0; i < entities; ++i)
      {
        entity1 = cell.get_entities()[i];
        for (j = i + 1; j < entities; ++j)
        {
          entity2 = cell.get_entities()[j];

          // Handle the collision
          if (collision(entity1, entity2))
          {
            // TODO Handle collision
            // TODO Needs a mechanism by which duplicate collisions (same entities, multiple cells) are properly handled
            printf("Collision!\n");
          }
        }
      }
    }
  }
}

/**
 * Check for a collision between two individual entities. Returns true if the entities are colliding
 */
bool CollisionEngine::collision(std::shared_ptr<Entity> &entity1, std::shared_ptr<Entity> &entity2)
{
  float dx;
  float dy;
  float hypo;
  float temp;

  temp = entity1->get_position().x - entity2->get_position().x;
  dx = temp * temp;
  temp = entity1->get_position().y - entity2->get_position().y;
  dy = temp * temp;
  temp = entity1->get_size() + entity2->get_size();
  hypo = temp * temp;

  return (hypo > dx + dy);
}
