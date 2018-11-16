#include "Projectile.h"
#include "EventManager.h"
#include "macros.h"
#include <iostream>
        
Projectile::Projectile(float x, float y) : Entity(x, y, PROJECTILE_SIZE_DEFAULT){
    speed = PROJECTILE_SPEED_DEFAULT;
    maxRange = 500;
    traveled = 0;
    damage = 0;
    type = TYPE_PROJECTILE;
    EventManager::Instance()->RegisterObject(EVENT_GOLD_COLLECTION, this);
}

//handles events 
void Projectile::HandleEvent( Event* event){
//     if (event->EventId() == PROJECTILE_SHOOT)
//   {
//     printf("PROJECTILE: shooting!\n");
//     //attack(Vector2D &dir, float delta);
//     EventManager::Instance()->UnregisterObject(PROJECTILE_SHOOT, this);
//   }
}

void Projectile::move(Vector2D &dir, float delta){
  float delta_speed = speed * delta;
  Vector2D change = dir.normal() * delta_speed;
  traveled += change.length;
  pos = pos + change;
}