#include <macros.h>
#include "entity.h"
#include <iostream>

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
	printf("in entity move\n");
}

void Entity::set_health(int h){
      health = h;
    }
void Entity::set_mana(int m){
      mana = m;
    }
void Entity::takedamage(int damage){
      health -= damage;
}

void Entity::HandleEvents( Event* event){
  
}