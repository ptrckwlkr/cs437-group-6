#include <view_manager.h>
#include <views/view_projectile.h>
#include "macros.h"

Player::Player(float x, float y) : Entity(x, y, PLAYER_SIZE)
{
  speed = PLAYER_SPEED;
  delta_sum = 0.0;
}


Player::~Player()
{

}

void Player::attack(Vector2D &dir, float delta) {
    delta_sum += delta;
    //prevents projectiles from being spammed
    if (delta_sum >= delta_threshold) {
        float x = EntityManager::Instance()->getPlayer()->get_position().x;
        float y = EntityManager::Instance()->getPlayer()->get_position().y;
        auto projectile = EntityManager::Instance()->createEntity<Projectile>(x, y);
        projectile->set_direction(dir);
        ViewManager::Instance()->add_view<Projectile>(projectile);
        delta_sum = 0;
    }
}
