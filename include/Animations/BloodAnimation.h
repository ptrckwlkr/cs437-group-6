#ifndef CSCI437_BLOODANIMATION_H
#define CSCI437_BLOODANIMATION_H


#include "entities/blood.h"
#include "Animation.h"

class BloodAnimation : public Animation
{

public:
    BloodAnimation(Blood &entity);
    void update(float delta);

private:
    Blood *blood;
    unsigned int slide = 0;

};


#endif //CSCI437_BLOODANIMATION_H
