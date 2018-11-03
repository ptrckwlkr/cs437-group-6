#include "Player.h"
#include <macros.h>

Player::Player(){
}

Player::~Player(){

    //unsubscirbe from events 
}

void Player::HandleEvents( Event* event){
    
}

void Player::move(Direction dir, float delta) // TODO note this kind of movement is specific to the player and should be moved
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

