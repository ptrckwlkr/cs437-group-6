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
  if (event->EventId() == EVENT_ENEMY_SHOT_AT && get_id() == event->Arg1()->get()){
    health -= (int)(event->Arg2());
    printf("ENEMY: I have been shoot at \n");
    event->Arg3()->destroy();
  }
}
