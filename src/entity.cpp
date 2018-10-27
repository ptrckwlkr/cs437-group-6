#include "entity.h"

Entity::Entity(float x, float y, float size) : size(size)
{
  pos.x = x;
  pos.y = y;
}

void Entity::set_position(float x, float y)
{
  pos.x = x;
  pos.y = y;
}
