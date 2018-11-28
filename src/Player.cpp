#include <view_manager.h>
#include <view_projectile.h>
#include "macros.h"

Player::Player(float x, float y) : Entity(x, y, 10)
{
  speed = PLAYER_SPEED;
  type = TYPE_PLAYER;
}


Player::~Player()
{
    //unsubscirbe from events 
}

void Player::attack(Vector2D &dir)
{
  float x = EntityManager::Instance()->getPlayer()->get_position().x;
  float y = EntityManager::Instance()->getPlayer()->get_position().y;
  auto projectile = EntityManager::Instance()->createEntity<Projectile>(x, y);
  projectile->set_direction(dir);
  ViewManager::Instance()->add_view<Projectile, ProjectileView>(projectile);
}
