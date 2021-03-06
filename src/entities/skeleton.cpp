#include "EntityManager.h"
#include "entities/Projectile.h"
#include "entities/skeleton.h"
#include "entities/blood.h"

Skeleton::Skeleton(float x, float y) : Enemy(x, y, SKELETON_SIZE) {
    obstructible = true;
    hostile = true;
    defence = 1;

    //uses normal skeleton by default
    setType("skeleton-white");

    EventManager::Instance().registerListener(EventCollision::eventType, this, & Skeleton::handleCollision);
}

void Skeleton::handleCollision(const EventCollision &event)
{
    if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType)
    {
        event.getOther().take_damage(damage);
    }
}


void Skeleton::die()
{
    Engine::Instance().get_state().get_player_data().add_enemy_count();
    EntityManager::Instance().removeEntity(id);
    EntityManager::Instance().createEntity<Blood>(pos.x, pos.y);

    //spawn a potion 1 out of every 8 enemy deaths on average
    if (rand() % 8 == 7)
    {
        EntityManager::Instance().createEntity<Potion>(pos.x, pos.y);
    }
}
