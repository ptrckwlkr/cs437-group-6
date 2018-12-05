#ifndef CSCI437_EXPLOSIONANIMATION_H
#define CSCI437_EXPLOSIONANIMATION_H


#include "entities/explosion.h"
#include "Animation.h"

class ExplosionAnimation : public Animation
{

public:
    ExplosionAnimation(Explosion &entity);
    void update(float delta);

private:
    Explosion *explosion;
    unsigned int slide = 0;

};


#endif //CSCI437_EXPLOSIONANIMATION_H
