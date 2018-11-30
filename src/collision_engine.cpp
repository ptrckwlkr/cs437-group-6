#include <vector>
#include "collision_engine.h"
#include "events/event_wall_collision.h"
#include "events/event_collision.h"
#include "macros.h"
#include "EventManager.h"

/**
 * Given a pointer to a level's Map, check for collisions among all entities using the Map's optimized data structure
 */
void CollisionEngine::check_collisions(Map &level_map, std::vector<std::shared_ptr<Entity>> entities)
{
  int num_entities;
  int i;
  int j;
  std::shared_ptr<Entity> entity1;
  std::shared_ptr<Entity> entity2;

  // Check every cell of the map
  for (auto cell : occupied_cells)
  {
    // Compare every entity in each individual cell to each other
    num_entities = (int)cell->get_entities().size();
    for (i = 0; i < num_entities; ++i)
    {
      entity1 = cell->get_entities()[i];
      for (j = i + 1; j < num_entities; ++j)
      {
        entity2 = cell->get_entities()[j];

        // Handle the collision
        if (entity_collision(*entity1, *entity2))
        {
          EventItem item = {EventCollision::eventType, entity1.get(), entity2.get()};
          event_set.insert(item);
          if (entity1->is_obstructible() && entity2->is_obstructible()) adjust_positions(*entity1, *entity2);
        }
      }
      if (wall_collision(level_map, *entity1))
      {
        EventItem item = {EventWallCollision::eventType, entity1.get(), nullptr};
        event_set.insert(item);
      }
    }
  }
  dispatchEvents();
}

/**
 * Check for a collision between two individual entities. Returns true if the entities are colliding
 */
bool CollisionEngine::entity_collision(Entity &entity1, Entity &entity2)
{
  float hypo = entity1.get_size() + entity2.get_size();
  Vector2D vec = entity1.get_position() - entity2.get_position();
  return (hypo * hypo > vec.x * vec.x + vec.y * vec.y);
}

/**
 * Sort a list of pointers to game entities into the map's cells, according to the entities' positions
 */
void CollisionEngine::hash_entities(Map &level_map, std::vector<std::shared_ptr<Entity>> entities)
{
  // TODO will probably ultimately accept the EntityManager& as a parameter, instead of a raw vector of pointers
  float radius;
  float top;
  float bot;
  float left;
  float right;
  Cell *cell;

  // Sort every entity into one or more of the game grid's cells
  clear_cells(level_map);
  for (auto &ent : entities)
  {
    Vector2D pos = ent->get_position();
    radius  = ent->get_size();
    top     = pos.y - radius - COLLISION_BUFFER;
    bot     = pos.y + radius + COLLISION_BUFFER;
    left    = pos.x - radius - COLLISION_BUFFER;
    right   = pos.x + radius + COLLISION_BUFFER;

    // Consider the 4 "corners" of the entity, and insert into every cell that contains a corner
    cell = &level_map.get_cell((int)top / CELL_SIZE, (int)left / CELL_SIZE);
    cell->insert_entity(ent);
    occupied_cells.insert(cell);
    cell = &level_map.get_cell((int)top / CELL_SIZE, (int)right / CELL_SIZE);
    cell->insert_entity(ent);
    occupied_cells.insert(cell);
    cell = &level_map.get_cell((int)bot / CELL_SIZE, (int)left / CELL_SIZE);
    cell->insert_entity(ent);
    occupied_cells.insert(cell);
    cell = &level_map.get_cell((int)bot / CELL_SIZE, (int)right / CELL_SIZE);
    cell->insert_entity(ent);
    occupied_cells.insert(cell);
  }
}

/**
 * Clear every cell of its registered entities
 */
void CollisionEngine::clear_cells(Map &level_map)
{
  for (auto &cell : occupied_cells)
  {
    cell->clear_entities();
  }
  occupied_cells.clear();
}

/**
 * For a given entity, check for and correct all collisions with obstructed tiles.
 */
bool CollisionEngine::wall_collision(Map &level_map, Entity &entity)
{
  float size = entity.get_size();
  Vector2D curr = entity.get_position();
  float x = curr.x;
  float y = curr.y;

  float left = x - size;
  float top = y - size;
  float right = x + size;
  float bot = y + size;

  bool left_blocked   = level_map.get_cell((int)(y / CELL_SIZE), (int)((x - size) / CELL_SIZE)).get_cell_type() == WALL;
  bool top_blocked    = level_map.get_cell((int)((y - size) / CELL_SIZE), (int)(x / CELL_SIZE)).get_cell_type() == WALL;
  bool right_blocked  = level_map.get_cell((int)(y / CELL_SIZE), (int)((x + size) / CELL_SIZE)).get_cell_type() == WALL;
  bool bot_blocked    = level_map.get_cell((int)((y + size) / CELL_SIZE), (int)(x / CELL_SIZE)).get_cell_type() == WALL;

  if (top_blocked + left_blocked + bot_blocked + right_blocked > 2)
  {
    entity.set_position(entity.get_old_position());
    return true;
  }

  if (left_blocked)
  {
    Vector2D penetration = Vector2D((int)(left / CELL_SIZE) * CELL_SIZE + CELL_SIZE - left, 0);
    entity.set_position(entity.get_position() + penetration);
  }
  if (right_blocked)
  {
    Vector2D penetration = Vector2D((int)(right / CELL_SIZE) * CELL_SIZE - right, 0);
    entity.set_position(entity.get_position() + penetration);
  }
  if (top_blocked)
  {
    Vector2D penetration = Vector2D(0, (int)(top / CELL_SIZE) * CELL_SIZE + CELL_SIZE - top);
    entity.set_position(entity.get_position() + penetration);
  }
  if (bot_blocked)
  {
    Vector2D penetration = Vector2D(0, (int)(bot / CELL_SIZE) * CELL_SIZE - bot);
    entity.set_position(entity.get_position() + penetration);
  }

  return left_blocked || right_blocked || top_blocked || bot_blocked;
}

void CollisionEngine::adjust_positions(Entity &entity1, Entity &entity2)
{
  Vector2D actual = entity1.get_position() - entity2.get_position();
  Vector2D theo = actual.normal() * (entity1.get_size() + entity2.get_size());
  Vector2D correction = theo - actual;
  float dx = correction.x / 2;
  float dy = correction.y / 2;
  entity1.set_position(entity1.get_position().x + dx, entity1.get_position().y + dy);
  entity2.set_position(entity2.get_position().x - dx, entity2.get_position().y - dy);
}

void CollisionEngine::dispatchEvents()
{
  for (auto &item : event_set)
  {
    if (item.type == EventCollision::eventType)
    {
      EventCollision collision1(item.entity1, item.entity2);
      EventCollision collision2(item.entity2, item.entity1);
      EventManager::Instance()->sendEvent(collision1);
      EventManager::Instance()->sendEvent(collision2);

    }
    else if (item.type == EventWallCollision::eventType)
    {
      EventWallCollision collision(item.entity1);
      EventManager::Instance()->sendEvent(collision);
    }
  }
  event_set.clear();
}
