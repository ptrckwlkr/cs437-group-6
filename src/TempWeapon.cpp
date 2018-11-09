#include "TempWeapon.h"

TempWeapon::TempWeapon(){};

TempWeapon::~TempWeapon(){}

void TempWeapon::set_position(Position new_pos){
    //should be set in same position of player
    Position = new_pos;
}

void TempWeapon::set_maxDamage( int maxD){
    maxDamage = maxD;
}
        
void TempWeapon::set_maxRange( int maxR){
    maxRange = maxR;
}

void TempWeapon::HandleEvents( Event* event){
    ///if eventid = "attack"
}
void TempWeapon::attack(Direction dir, float delta){

};
