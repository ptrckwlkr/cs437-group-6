#include "Enemy.h"
#include <macros.h>

Enemy::Enemy(){
}

Enemy::~Enemy(){

    //unsubscirbe from events 
}

void Enemy::HandleEvents( Event* event){
     ///if eventid = "walk"
        //move
    
}

void Enemy::move(Direction dir, float delta) 
{
  pos_old = pos;
  float delta_speed = ENEMY_SPEED * delta;

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