#include "Player.h"
#include "EventManager.h"
#include <macros.h>
#include <iostream>

<<<<<<< HEAD
Player::Player(){}
=======
Player::Player(float x, float y, float size) : Entity(x, y, size)
{
}
>>>>>>> 07c6bc613fdaab79371ac938b2a7193b17a5b6a1


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

<<<<<<< HEAD
void update(double deltaMs){
  //move(dir, delta

}

=======
>>>>>>> 07c6bc613fdaab79371ac938b2a7193b17a5b6a1
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

