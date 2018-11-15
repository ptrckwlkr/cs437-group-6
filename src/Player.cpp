#include "EventManager.h"
#include "Player.h"
#include "macros.h"

Player::Player(float x, float y, float size) : Entity(x, y, size)
{
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

void Player::set_projectile(std::shared_ptr<Projectile> p){
  projectile = p;
}

void Player::move(Vector2D &dir, float delta)
{
  float delta_speed = PLAYER_SPEED * delta;
  Vector2D vec = dir.normal() * delta_speed;
  pos.x = pos.x + vec.x;
  pos.y = pos.y + vec.y;
}
