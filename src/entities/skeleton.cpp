#include "entities/Projectile.h"
#include "entities/skeleton.h"

Skeleton::Skeleton(float x, float y) : Entity(x, y, SKELETON_SIZE)
{
  health = SKELETON_HEALTH;
  speed = SKELETON_SPEED;
  obstructible = true;
  hostile = true;

  EventManager::Instance()->registerListener(EventCollision::eventType, this, &handleCollision);
}

Skeleton::~Skeleton()
{

}

void Skeleton::handleCollision(const EventCollision &event)
{
  if (event.getSelf().id == id && event.getOther().getEntityType() == Projectile::entityType)
  {
    health -= 3;
    if (health <= 0)
    {
      alive = false;
    }
  }
}
