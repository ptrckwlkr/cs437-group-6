#include "EntityManager.h"
#include "entities/sreep.h"

Sreep::Sreep(float x, float y) : Enemy(x, y, SREEP_SIZE) {
  obstructible = true;
  hostile = true;
  defence = 25;
  damage = 100;
  health = 500;

  EventManager::Instance().registerListener(EventCollision::eventType, this, & Sreep::handleCollision);
}

void Sreep::handleCollision(const EventCollision &event)
{
  if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType)
  {
    event.getOther().take_damage(damage);
  }
}


void Sreep::die()
{
  EntityManager::Instance().removeEntity(id);
}
