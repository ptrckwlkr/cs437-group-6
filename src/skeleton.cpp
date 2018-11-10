#include "skeleton.h"

Skeleton::Skeleton(float x, float y) : Entity(x, y, SKELETON_SIZE)
{
  type = TYPE_SKELETON;
}

void Skeleton::move(Direction dir, float delta)
{

}

void Skeleton::HandleEvent(Event *event)
{

}
