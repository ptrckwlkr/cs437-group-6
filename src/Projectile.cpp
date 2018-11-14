#include "Projectile.h"
#include <iostream>
        
Projectile::Projectile(float x, float y, float size) : Entity(x, y, size){
    type = TYPE_PROJECTILE;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    mousePos.x = 0.0f;
    mousePos.y = 0.0f;
}

Projectile::~Projectile(){}

//handles events 
void Projectile::HandleEvent( Event* event){
    ///if eventid = "attack"
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
void Projectile::set_mousePos( sf::Vector2f &mPos){
    mousePos.x = mPos.x;
    mousePos.y = mPos.y;
}

void Projectile::set_playerCenter( sf::Vector2f &pCenter){
    playerCenter.x = pCenter.x;
    playerCenter.y = pCenter.y;
}

void Projectile::set_aimDirection(){
   aimDirection = mousePos - playerCenter;
}

//normalizes the aimDirection
sf::Vector2f Projectile::set_aimDirectionNormal(){
     return aimDirectionNormal = aimDirection / sqrt((aimDirection.x *aimDirection.x )+ (aimDirection.y * aimDirection.y));
     std::cout << aimDirectionNormal.x << " " << aimDirection.y;
 }

void Projectile::set_velocity( const sf::Vector2f vel){
    velocity.x = vel.x;
    velocity.y = velocity.y;
}

void Projectile::move2( const sf::Vector2f currVelocity, float delta){
    pos.x = currVelocity.x;
    pos.y = currVelocity.y;

}

void Projectile::move(Direction dir, float delta){

}

void attack( int speed){
}