#include "Projectile.h"   
        
        
Projectile::Projectile(float x, float y, float size) : Entity(x, y, size){}

Projectile::~Projectile(){}

//handles events 
void Projectile::HandleEvents( Event* event){
    ///if eventid = "attack"
}

void Projectile::set_maxDamage( int mD){
    maxDamage = mD;

}
        
void Projectile::set_maxRandge(int mR){
    maxRange = mR;

}
void Projectile::attack(Direction dir, float delta){

}