#ifndef CSCI437_SMOKEANIMATION_H
#define CSCI437_SMOKEANIMATION_H


#include "entities/smoke.h"
#include "Animation.h"

class SmokeAnimation : public Animation
{

public:
    SmokeAnimation(Smoke &entity);
    void update(float delta);

private:
    Smoke *smoke;
    unsigned int slide = 0;

};


#endif //CSCI437_SMOKEANIMATION_H
