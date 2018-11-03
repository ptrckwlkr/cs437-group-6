#include <macros.h>
#include "entity.h"

Entity::Entity(float x, float y, float size) : size(size)
{
  pos.x = x;
  pos.y = y;
}

void Entity::set_position(float x, float y)
{
  pos.x = x;
  pos.y = y;
}

void Entity::set_position(Position new_pos)
{
  pos = new_pos;
}


void Entity::move(Direction dir, float delta){

}

//moved to the player 
// void Entity::move(Direction dir, float delta) // TODO note this kind of movement is specific to the player and should be moved
// {
//   pos_old = pos;
//   float delta_speed = PLAYER_SPEED * delta;

//   switch (dir)
//   {
//     case NORTH:
//       pos.y -= delta_speed;
//       break;
//     case NORTHEAST:
//       pos.x += delta_speed;
//       pos.y -= delta_speed;
//       break;
//     case EAST:
//       pos.x += delta_speed;
//       break;
//     case SOUTHEAST:
//       pos.x += delta_speed;
//       pos.y += delta_speed;
//       break;
//     case SOUTH:
//       pos.y += delta_speed;
//       break;
//     case SOUTHWEST:
//       pos.x -= delta_speed;
//       pos.y += delta_speed;
//       break;
//     case WEST:
//       pos.x -= delta_speed;
//       break;
//     case NORTHWEST:
//       pos.x -= delta_speed;
//       pos.y -= delta_speed;
//       break;
//     case NONE:
//       break;
//   }
// }

void Entity::set_health(int h){
      health = h;
    }
void Entity::set_mana(int m){
      mana = m;
    }
void Entity::takedamage(int damage){
      health -= damage;
}
