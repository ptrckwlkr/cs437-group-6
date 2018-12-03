#include <vector>
#include "collision_engine.h"
#include "events/event_wall_collision.h"
#include "events/event_collision.h"
#include "macros.h"
#include "EventManager.h"

/**
 * Given a pointer to a level's Map, check for collisions among all entities using the Map's optimized data structure
 */
void CollisionEngine::check_collisions(Map &level_map)
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

  bool NW_blocked  = level_map.get_cell((int)((top) / CELL_SIZE), (int)((left) / CELL_SIZE)).get_cell_type() == WALL;
  bool NE_blocked  = level_map.get_cell((int)((top) / CELL_SIZE), (int)((right) / CELL_SIZE)).get_cell_type() == WALL;
  bool SE_blocked  = level_map.get_cell((int)((bot) / CELL_SIZE), (int)((right) / CELL_SIZE)).get_cell_type() == WALL;
  bool SW_blocked  = level_map.get_cell((int)((bot) / CELL_SIZE), (int)((left) / CELL_SIZE)).get_cell_type() == WALL;

  // If mid is blocked, you are too far into the wall, just go back to the old position
  if (level_map.get_cell((int)(y / CELL_SIZE), (int)(x / CELL_SIZE)).get_cell_type() == WALL)
  {
    entity.set_position(entity.get_old_position());
    return true;
  }

  // Entity is colliding in one corner
  if (NW_blocked + NE_blocked + SE_blocked + SW_blocked == 1)
  {
    Vector2D penetration;
    if (NW_blocked)
    {
      Vector2D NW = Vector2D(left, top);
      float top_border = (int)(top / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
      float left_border = (int)(left / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
      Line horizontal = {0, top_border, 100000, top_border};
      Line vertical = {left_border, 0, left_border, 100000};
      Line path = {x, y, NW.x, NW.y};
      if ((NW - intersection(path, horizontal)).length < (NW - intersection(path, vertical)).length)
        penetration = Vector2D(0, top_border - top);
      else
        penetration = Vector2D(left_border - left, 0);
    }
    else if (NE_blocked) // Top-right corner
    {
      Vector2D NE = Vector2D(right, top);
      float top_border = (int)(top / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
      float right_border = (int)(right / CELL_SIZE) * CELL_SIZE;
      Line horizontal = {0, top_border, 100000, top_border};
      Line vertical = {right_border, 0, right_border, 100000};
      Line path = {x, y, NE.x, NE.y};
      if ((NE - intersection(path, horizontal)).length < (NE - intersection(path, vertical)).length)
        penetration = Vector2D(0, top_border - top);
      else
        penetration = Vector2D(right_border - right, 0);
    }
    else if (SE_blocked) // Bottom-right corner
    {
      Vector2D SE = Vector2D(right, bot);
      float bot_border = (int)(bot / CELL_SIZE) * CELL_SIZE;
      float right_border = (int)(right / CELL_SIZE) * CELL_SIZE;
      Line horizontal = {0, bot_border, 100000, bot_border};
      Line vertical = {right_border, 0, right_border, 100000};
      Line path = {x, y, SE.x, SE.y};
      if ((SE - intersection(path, horizontal)).length < (SE - intersection(path, vertical)).length)
        penetration = Vector2D(0, bot_border - bot);
      else
        penetration = Vector2D(right_border - right, 0);
    }
    else // Bottom-left corner
    {
      Vector2D SW = Vector2D(left, bot);
      float bot_border = (int)(bot / CELL_SIZE) * CELL_SIZE;
      float left_border = (int)(left / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
      Line horizontal = {0, bot_border, 100000, bot_border};
      Line vertical = {left_border, 0, left_border, 100000};
      Line path = {x, y, SW.x, SW.y};
      if ((SW - intersection(path, horizontal)).length < (SW - intersection(path, vertical)).length)
        penetration = Vector2D(0, bot_border - bot);
      else
        penetration = Vector2D(left_border - left, 0);
    }
    entity.set_position(entity.get_position() + penetration);
  }
  else // Regular cases of colliding with the walls
  {
    Vector2D correction = VEC_NONE;
    if (NW_blocked && NE_blocked)
    {
      Vector2D penetration = Vector2D(0, (int) (top / CELL_SIZE) * CELL_SIZE + CELL_SIZE - top);
      correction = correction + penetration;
    }
    if (NE_blocked && SE_blocked)
    {
      Vector2D penetration = Vector2D((int) (right / CELL_SIZE) * CELL_SIZE - right, 0);
      correction = correction + penetration;
    }
    if (SE_blocked && SW_blocked)
    {
      Vector2D penetration = Vector2D(0, (int) (bot / CELL_SIZE) * CELL_SIZE - bot);
      correction = correction + penetration;
    }
    if (SW_blocked && NW_blocked)
    {
      Vector2D penetration = Vector2D((int) (left / CELL_SIZE) * CELL_SIZE + CELL_SIZE - left, 0);
      correction = correction + penetration;
    }
    entity.set_position(curr + correction);
  }
  return (NW_blocked || NE_blocked || SE_blocked || SW_blocked);
}

/**
 * Sort a list of pointers to game entities into the map's cells, according to the entities' positions
 */
void CollisionEngine::hash_entities(Map &level_map, std::unordered_map<long long, std::shared_ptr<Entity>> entities)
{
  // TODO will probably ultimately accept the EntityManager& as a parameter, instead of a raw vector of pointers
  float radius;
  float top;
  float bot;
  float left;
  float right;
  Cell *cell;

  // Sort every entity into one or more of the game grid's cells
  clear_cells();
  for (auto &i : entities)
  {
    auto ent = i.second;
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
void CollisionEngine::clear_cells()
{
  for (auto &cell : occupied_cells)
  {
    cell->clear_entities();
  }
  occupied_cells.clear();
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
      EventManager::Instance().sendEvent(collision1);
      EventManager::Instance().sendEvent(collision2);

    }
    else if (item.type == EventWallCollision::eventType)
    {
      EventWallCollision collision(item.entity1);
      EventManager::Instance().sendEvent(collision);
    }
  }
  event_set.clear();
}

Vector2D CollisionEngine::intersection(CollisionEngine::Line line1, CollisionEngine::Line line2)
{
  float a = line1.x1 * line1.y2 - line1.y1 * line1.x2;
  float b = line2.x1 * line2.y2 - line2.x2 * line2.y1;
  float d = (line1.x1 - line1.x2) * (line2.y1 - line2.y2) - (line1.y1 - line1.y2) * (line2.x1 - line2.x2);
  float x = (a * (line2.x1 - line2.x2) - b * (line1.x1 - line1.x2)) / d;
  float y = (a * (line2.y1 - line2.y2) - b * (line1.y1 - line1.y2)) / d;
  return {x, y};
}

