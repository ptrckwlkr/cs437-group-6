#include "skeleton.h"
#include "skeleton.h"
#include "EventManager.h"

Skeleton::Skeleton(float x, float y) : Entity(x, y, SKELETON_SIZE)
{
  speed = SKELETON_SPEED;
  type = TYPE_SKELETON;
  EventManager::Instance()->RegisterObject(EVENT_ENEMY_SHOT_AT, this);
}

void Skeleton::HandleEvent(Event *event)
{
  // if (event->EventId()== EVENT_ENEMY_SHOT_AT){
  //   health -= (int)(event->Arg1());
  //   printf("ENEMY: I have been shoot at \n");
  // }
}
