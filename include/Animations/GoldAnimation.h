#ifndef CSCI437_GOLDANIMATION_H
#define CSCI437_GOLDANIMATION_H

#include "Animation.h"
#include "entities/gold.h"

class GoldAnimation : public Animation
{

public:
    GoldAnimation(Gold &entity);
    void update(float delta);

private:
    Gold *gold;
    unsigned int slide = 0;
    float random_interval;

};


#endif //CSCI437_GOLDANIMATION_H
