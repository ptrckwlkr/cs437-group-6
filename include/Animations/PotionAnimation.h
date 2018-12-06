#ifndef CSCI437_POTIONANIMATION_H
#define CSCI437_POTIONANIMATION_H


#include "Animation.h"
#include "entities/potion.h"

class PotionAnimation : public Animation
{

public:
    PotionAnimation(Potion &entity);
    void update(float delta);

private:
    Potion *potion;

};


#endif //CSCI437_POTIONANIMATION_H
