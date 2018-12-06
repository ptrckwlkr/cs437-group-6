#include "entities/ghost.h"
#include "EntityManager.h"
#include "entities/smoke.h"


Ghost::Ghost(float x, float y) : Enemy(x, y, GHOST_SIZE) {
    obstructible = true;
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
    EntityManager::Instance().createEntity<Smoke>(pos.x, pos.y);

    //spawn a potion 1 out of every 8 enemy deaths on average
    if (rand() % 8 == 7)
    {
        EntityManager::Instance().createEntity<Potion>(pos.x, pos.y);
    }
}
