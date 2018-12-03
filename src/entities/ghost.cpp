#include "entities/ghost.h"
#include "entities/Projectile.h"
#include "EntityManager.h"
#include "entities/blood.h"


Ghost::Ghost(float x, float y) : Enemy(x, y, GHOST_SIZE) {
    obstructible = false;
    hostile = true;
    defence = 1;
    immovable = false;
    wall_collidable = false;

    //uses normal ghost by default
    setType("ghost-white");

    EventManager::Instance().registerListener(EventCollision::eventType, this, & Ghost::handleCollision);
}


void Ghost::handleCollision(const EventCollision &event)
{
    if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType)
    {
        event.getOther().take_damage(damage);
    }
}


void Ghost::die()
{
    EntityManager::Instance().removeEntity(id);
    EntityManager::Instance().createEntity<Blood>(pos.x, pos.y);
}
