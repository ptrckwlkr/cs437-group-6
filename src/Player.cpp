#include "EventManager.h"
#include "Player.h"
#include "macros.h"

Player::Player(float x, float y, float size) : Entity(x, y, size)
{
  type = TYPE_PLAYER;
  EventManager::Instance()->RegisterObject(EVENT_GOLD_COLLECTION, this);
}


Player::~Player()
{
    //unsubscirbe from events 
}

void Player::HandleEvent(Event* event)
{
  // if (event->EventId() == EVENT_GOLD_COLLECTION) printf("PLAYER: I have collected gold!\n"); // TODO
}

void Player::move(Direction dir, float delta) 
{
  float delta_speed = PLAYER_SPEED * delta;

  switch (dir)
  {
    case NORTH:
      pos.y -= delta_speed;
      break;
    case NORTHEAST:
      pos.x += delta_speed;
      pos.y -= delta_speed;
      break;
    case EAST:
      pos.x += delta_speed;
      break;
    case SOUTHEAST:
      pos.x += delta_speed;
      pos.y += delta_speed;
      break;
    case SOUTH:
      pos.y += delta_speed;
      break;
    case SOUTHWEST:
      pos.x -= delta_speed;
      pos.y += delta_speed;
      break;
    case WEST:
      pos.x -= delta_speed;
      break;
    case NORTHWEST:
      pos.x -= delta_speed;
      pos.y -= delta_speed;
      break;
    case NONE:
      break;
  }
}

