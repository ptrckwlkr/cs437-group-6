#include "Projectile.h"
#include "EventManager.h"
#include "macros.h"
#include <iostream>
        
Projectile::Projectile(float x, float y, float size) : Entity(x, y, size){

    EventManager::Instance()->RegisterObject(EVENT_GOLD_COLLECTION, this);
}

Projectile::~Projectile(){}

//handles events 
void Projectile::HandleEvent( Event* event){
//     if (event->EventId() == PROJECTILE_SHOOT)
//   {
//     printf("PROJECTILE: shooting!\n");
//     //attack(Vector2D &dir, float delta);
//     EventManager::Instance()->UnregisterObject(PROJECTILE_SHOOT, this);
//   }
}

void Projectile::set_maxDamage( int mD){
    maxDamage = mD;
}
        
void Projectile::set_maxRange(int mR){
    maxRange = mR;
}
void Projectile::set_speed ( int s){
    speed = s;
}
void Projectile::set_mousePos(  Vector2D  &mPos){
    mousePos.x = mPos.x;
    mousePos.y = mPos.y;
}

void Projectile::set_playerCenter(  Vector2D  &pCenter){
    playerCenter.x = pCenter.x;
    playerCenter.y = pCenter.y;
}

void Projectile::set_aimDirection(){
   aimDirection = mousePos - playerCenter;
}

// //normalizes the aimDirection
// sf::Vector2f Projectile::set_aimDirectionNormal(){
//      return aimDirectionNormal = aimDirection / sqrt((aimDirection.x *aimDirection.x )+ (aimDirection.y * aimDirection.y));
//      std::cout << aimDirectionNormal.x << " " << aimDirection.y;
//  }

void Projectile::set_velocity(  Vector2D  &vel){
    velocity.x = vel.x;
    velocity.y = vel.y;
}

void Projectile::move(Vector2D &dir, float delta){

}
void Projectile::attack(Vector2D &dir, float delta){

    float delta_speed = PROJECTILE_SPEED * delta;
    Vector2D vec = dir.normal() * delta_speed;
    pos.x = pos.x + vec.x;
    pos.y = pos.y + vec.y;
}