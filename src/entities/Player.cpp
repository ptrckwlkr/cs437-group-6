#include "entities/Player.h"
#include "entities/Projectile.h"
#include "entities/melee.h"
#include "events/event_player_died.h"
#include "EntityManager.h"

Player::Player(float x, float y) : Entity(x, y, PLAYER_SIZE)
{
    delta_sum = 0.0;
    obstructible = true;
}

void Player::attack(Vector2D &dir, float delta) {
    delta_sum += delta;
    //prevents projectiles from being spammed

    /*
    if (delta_sum >= delta_threshold) {
        float x = pos.x;
        float y = pos.y;
        auto projectile = EntityManager::Instance().createEntity<Projectile>(x, y);
        projectile->set_direction(dir);
        projectile->set_damage(damage);
        delta_sum = 0;
    }*/

    delta_threshold = (float)(60 / 60.0);
    if (delta_sum > delta_threshold)
    {
        Vector2D p = pos + dir.normal() * size * 1.5;
        auto melee = EntityManager::Instance().createEntity<Melee>(p.x, p.y);
        melee->setRadius(30);
        melee->setDirection(dir);
        melee->set_damage(damage);
        delta_sum = 0;
    }
}

void Player::die()
{
    EventPlayerDied event;
    EventManager::Instance().sendEvent(event);
}
