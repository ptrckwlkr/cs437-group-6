#include "Player.h"
#include <macros.h>
#include <iostream>

Player::Player(float x, float y, float size) : Entity(x, y, size)
{
}


Player::~Player()
{
    //unsubscirbe from events 
}

void Player::HandleEvent( Event* event)
{
    
}

void Player::move(Direction dir, float delta) 
{
  pos_old = pos;
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

