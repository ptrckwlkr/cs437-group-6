#ifndef CSCI437_SWORDANIMATION_H
#define CSCI437_SWORDANIMATION_H


#include "entities/sword.h"
#include "Animation.h"

class SwordAnimation : public Animation
{

public:
    SwordAnimation(Sword &entity);
    void update(float delta);

private:
    Sword *sword;
    unsigned int slide = 0;
    float offset_x;
    float offset_y;

};


#endif //CSCI437_SWORDANIMATION_H
