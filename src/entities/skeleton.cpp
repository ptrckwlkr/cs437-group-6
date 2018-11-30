#include "entities/Projectile.h"
#include "entities/skeleton.h"

Skeleton::Skeleton(float x, float y) : Entity(x, y, SKELETON_SIZE)
{
  obstructible = true;
  hostile = true;
  //uses normal skeleton by default
  type = "white";

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


void Skeleton::updateAttributes() {


}


void Skeleton::setType(std::string param_type) {
  type = param_type;
  updateAttributes();
}
