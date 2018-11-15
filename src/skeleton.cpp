#include "skeleton.h"
#include "skeleton.h"
#include "EventManager.h"

Skeleton::Skeleton(float x, float y) : Entity(x, y, SKELETON_SIZE)
{
  type = TYPE_SKELETON;
  EventManager::Instance()->RegisterObject(EVENT_ENEMY_SHOT_AT, this);
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
  // if (event->EventId()== EVENT_ENEMY_SHOT_AT){
  //   health -= (int)(event->Arg1());
  //   printf("ENEMY: I have been shoot at \n");
  // }
}
