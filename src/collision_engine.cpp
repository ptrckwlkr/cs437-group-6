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

  bool NW_blocked  = level_map.get_cell((int)((y - size) / CELL_SIZE), (int)((x - size) / CELL_SIZE)).get_cell_type() == WALL;
  bool NE_blocked  = level_map.get_cell((int)((y - size) / CELL_SIZE), (int)((x + size) / CELL_SIZE)).get_cell_type() == WALL;
  bool SE_blocked  = level_map.get_cell((int)((y + size) / CELL_SIZE), (int)((x + size) / CELL_SIZE)).get_cell_type() == WALL;
  bool SW_blocked  = level_map.get_cell((int)((y + size) / CELL_SIZE), (int)((x - size) / CELL_SIZE)).get_cell_type() == WALL;

  // If mid is blocked, you are too far into the wall, just go back to the old position
  if (level_map.get_cell((int)(y / CELL_SIZE), (int)(x / CELL_SIZE)).get_cell_type() == WALL)
  {
    entity.set_position(entity.get_old_position());
    return true;
  }

  if (NW_blocked + NE_blocked + SE_blocked + SW_blocked == 1)
  {
    if (NW_blocked)
    {
      Vector2D NW = Vector2D(x - size, y - size);
      Vector2D p1 = Vector2D(0, (int)(top / CELL_SIZE) * CELL_SIZE + CELL_SIZE);
      Vector2D p2 = Vector2D(100000, (int)(top / CELL_SIZE) * CELL_SIZE + CELL_SIZE);
      Vector2D inter1 = intersection(curr, NW, p1, p2); // Horizontal line
      Vector2D q1 = Vector2D((int)(left / CELL_SIZE) * CELL_SIZE + CELL_SIZE, 0);
      Vector2D q2 = Vector2D((int)(left / CELL_SIZE) * CELL_SIZE + CELL_SIZE, 100000);
      Vector2D inter2 = intersection(curr, NW, q1, q2); // Vertical line
      if ((NW - inter1).length < (NW - inter2).length)
      {
        Vector2D penetration = Vector2D(0, (int) (top / CELL_SIZE) * CELL_SIZE + CELL_SIZE - top);
        entity.set_position(entity.get_position() + penetration);
      }
      else
      {
        Vector2D penetration = Vector2D((int)(left / CELL_SIZE) * CELL_SIZE + CELL_SIZE - left, 0);
        entity.set_position(entity.get_position() + penetration);
      }
    }
    else if (NE_blocked)
    {
      Vector2D NE = Vector2D(x + size, y - size);
      Vector2D p1 = Vector2D(0, (int)(top / CELL_SIZE) * CELL_SIZE + CELL_SIZE);
      Vector2D p2 = Vector2D(100000, (int)(top / CELL_SIZE) * CELL_SIZE + CELL_SIZE);
      Vector2D inter1 = intersection(curr, NE, p1, p2); // Horizontal line
      Vector2D q1 = Vector2D((int)(right / CELL_SIZE) * CELL_SIZE, 0);
      Vector2D q2 = Vector2D((int)(right / CELL_SIZE) * CELL_SIZE, 100000);
      Vector2D inter2 = intersection(curr, NE, q1, q2); // Vertical line
      if ((NE - inter1).length < (NE - inter2).length)
      {
        Vector2D penetration = Vector2D(0, (int) (top / CELL_SIZE) * CELL_SIZE + CELL_SIZE - top);
        entity.set_position(entity.get_position() + penetration);
      }
      else
      {
        Vector2D penetration = Vector2D((int)(right / CELL_SIZE) * CELL_SIZE - right, 0);
        entity.set_position(entity.get_position() + penetration);
      }
    }
    else if (SE_blocked)
    {
      Vector2D SE = Vector2D(x + size, y + size);
      Vector2D p1 = Vector2D(0, (int)(bot / CELL_SIZE) * CELL_SIZE);
      Vector2D p2 = Vector2D(100000, (int)(bot / CELL_SIZE) * CELL_SIZE);
      Vector2D inter1 = intersection(curr, SE, p1, p2); // Horizontal line
      Vector2D q1 = Vector2D((int)(right / CELL_SIZE) * CELL_SIZE, 0);
      Vector2D q2 = Vector2D((int)(right / CELL_SIZE) * CELL_SIZE, 100000);
      Vector2D inter2 = intersection(curr, SE, q1, q2); // Vertical line
      if ((SE - inter1).length < (SE - inter2).length)
      {
        Vector2D penetration = Vector2D(0, (int)(bot / CELL_SIZE) * CELL_SIZE - bot);
        entity.set_position(entity.get_position() + penetration);
      }
      else
      {
        Vector2D penetration = Vector2D((int)(right / CELL_SIZE) * CELL_SIZE - right, 0);
        entity.set_position(entity.get_position() + penetration);
      }
    }
    else
    {
      Vector2D SW = Vector2D(x - size, y + size);
      Vector2D p1 = Vector2D(0, (int)(bot / CELL_SIZE) * CELL_SIZE);
      Vector2D p2 = Vector2D(100000, (int)(bot / CELL_SIZE) * CELL_SIZE);
      Vector2D inter1 = intersection(curr, SW, p1, p2); // Horizontal line
      Vector2D q1 = Vector2D((int)(left / CELL_SIZE) * CELL_SIZE + CELL_SIZE, 0);
      Vector2D q2 = Vector2D((int)(left / CELL_SIZE) * CELL_SIZE + CELL_SIZE, 100000);
      Vector2D inter2 = intersection(curr, SW, q1, q2); // Vertical line
      if ((SW - inter1).length < (SW - inter2).length)
      {
        Vector2D penetration = Vector2D(0, (int)(bot / CELL_SIZE) * CELL_SIZE - bot);
        entity.set_position(entity.get_position() + penetration);
      }
      else
      {
        Vector2D penetration = Vector2D((int)(left / CELL_SIZE) * CELL_SIZE + CELL_SIZE - left, 0);
        entity.set_position(entity.get_position() + penetration);
      }
    }
  }
  else
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

Vector2D CollisionEngine::intersection(Vector2D &p1, Vector2D &p2, Vector2D &q1, Vector2D &q2)
{
  float a = p1.x * p2.y - p1.y * p2.x;
  float b = q1.x * q2.y - q2.x * q1.y;
  float d = (p1.x - p2.x) * (q1.y - q2.y) - (p1.y - p2.y) * (q1.x - q2.x);
  float x = (a * (q1.x - q2.x) - b * (p1.x - p2.x)) / d;
  float y = (a * (q1.y - q2.y) - b * (p1.y - p2.y)) / d;
  return {x, y};
}
