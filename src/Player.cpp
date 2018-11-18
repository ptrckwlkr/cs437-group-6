#include <view_manager.h>
#include <view_projectile.h>
#include "EventManager.h"
#include "EntityManager.h"
#include "Player.h"
#include "macros.h"

Player::Player(float x, float y) : Entity(x, y, 10)
{
  speed = PLAYER_SPEED;
  type = TYPE_PLAYER;
  EventManager::Instance()->RegisterObject(EVENT_GOLD_COLLECTION, this);
  //EventManager::Instance()->RegisterObject(EVENT_PLAYER_PROJECTILE_COLLISION, this);
}


Player::~Player()
{
    //unsubscirbe from events 
}

void Player::HandleEvent(Event* event)
{
  // if (event->EventId() == EVENT_GOLD_COLLECTION) printf("PLAYER: I have collected gold!\n"); // TODO
  // if (event->EventId()==EVENT_PLAYER_PROJECTILE_COLLISION){
  //   health -= (int)(event->Arg1());
  //   printf("PLAYER: I have been shoot at \n");
  // }
}

void Player::attack(Vector2D &dir)
{
  float x = EntityManager::Instance()->getPlayer()->get_position().x;
  float y = EntityManager::Instance()->getPlayer()->get_position().y;
  auto projectile = EntityManager::Instance()->createEntity<Projectile>(x, y);
  projectile->set_direction(dir);
  ViewManager::Instance()->add_view<Projectile, ProjectileView>(projectile);
}
