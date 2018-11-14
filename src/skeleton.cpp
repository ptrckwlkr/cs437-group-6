#include "skeleton.h"

Skeleton::Skeleton(float x, float y) : Entity(x, y, SKELETON_SIZE)
{
  type = TYPE_SKELETON;
}

void Skeleton::move(Vector2D &dir, float delta)
{
  float delta_speed = SKELETON_SPEED * delta;
  Vector2D vec = dir.normal() * delta_speed;
  pos.x = pos.x + vec.x;
  pos.y = pos.y + vec.y;
}

void Skeleton::HandleEvent(Event *event)
{

}
