#include "Weapon.h"

Weapon::Weapon(){};

Weapon::~Weapon(){}

void Weapon::set_maxDamage( int maxD){
    maxDamage = maxD;
}
        
void Weapon::set_maxRange( int maxR){
    maxRange = maxR;
}

void Weapon::HandleEvents( Event* event){
    ///if eventid = "attack"
}
void Weapon::attack(Direction dir, float delta){

};
