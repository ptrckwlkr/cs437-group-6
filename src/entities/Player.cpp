#include "macros.h"
#include "entities/Player.h"
#include "entities/Projectile.h"
#include "events/event_player_died.h"
#include "EntityManager.h"

Player::Player(float x, float y) : Entity(x, y, PLAYER_SIZE)
{
    speed = PLAYER_SPEED;
    delta_sum = 0.0;
    health = 100;
    max_health = 100;
    mana = 100;
    defence = 10;
    damage = 5;
}

void Player::attack(Vector2D &dir, float delta) {
    delta_sum += delta;
    //prevents projectiles from being spammed
    if (delta_sum >= delta_threshold) {
        float x = pos.x;
        float y = pos.y;
        auto projectile = EntityManager::Instance().createEntity<Projectile>(x, y);
        projectile->set_direction(dir);
        projectile->set_damage(damage);
        delta_sum = 0;
    }
}

void Player::die()
{
    EventPlayerDied event;
    EventManager::Instance().sendEvent(event);
}
