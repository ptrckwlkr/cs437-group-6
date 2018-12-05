#include <EntityManager.h>
#include "entities/boss.h"
#include "entities/blood.h"

Boss::Boss(float x, float y) : Enemy(x, y, BOSS_SIZE) {
    obstructible = true;
    hostile = true;
    defence = 1;

    //uses normal orc by default
    setType("boss");

    EventManager::Instance().registerListener(EventCollision::eventType, this, &Boss::handleCollision);
}

void Boss::handleCollision(const EventCollision &event)
{
    if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType)
    {
        event.getOther().take_damage(damage);
    }
}


void Boss::die()
{
    EntityManager::Instance().removeEntity(id);
    EntityManager::Instance().createEntity<Blood>(pos.x, pos.y);
}


void Boss::attack(float delta, float delta_threshold, Vector2D dir) {
    delta_sum += delta;

    if (delta_sum > delta_threshold)
    {
        float x = pos.x;
        float y = pos.y;
        //auto projectile = EntityManager::Instance().createEntity<Projectile>(x, y);
        //projectile->set_direction(dir);
        //projectile->set_damage(projectile_damage);
        delta_sum = 0;
    }
}
