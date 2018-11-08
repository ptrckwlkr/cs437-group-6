#include "Player.h"
#include "EventManager.h"
#include <macros.h>

Player::Player(){}

Player::~Player(){

  //unsubscibe from all events
  EventManager::Instance()->UnregisterAll(this);
}


void Player::HandleEvents( Event* event){
  if (event != nullptr){
    if ( event->EventId()== "PLAYER_HIT"){
      int x= 0; 
      x++;
    }
  }
    
}

void update(double deltaMs){
  //move(dir, delta

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

