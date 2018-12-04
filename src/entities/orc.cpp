#include "entities/orc.h"
#include "entities/Player.h"
#include "entities/Projectile.h"
#include "EntityManager.h"
#include "entities/blood.h"

Orc::Orc(float x, float y) : Enemy(x, y, ORC_SIZE) {
    obstructible = true;
    hostile = true;
    defence = 1;

    //uses normal orc by default
    setType("orc-green");

    EventManager::Instance().registerListener(EventCollision::eventType, this, & Orc::handleCollision);
}

void Orc::handleCollision(const EventCollision &event)
{
    if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType)
    {
        event.getOther().take_damage(damage);
    }
}


void Orc::die()
{
    EntityManager::Instance().removeEntity(id);
    EntityManager::Instance().createEntity<Blood>(pos.x, pos.y);
}
