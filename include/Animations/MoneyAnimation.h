#ifndef CSCI437_MONEYANIMATION_H
#define CSCI437_MONEYANIMATION_H

#include "entities/money.h"
#include "Animation.h"

class MoneyAnimation : public Animation
{

public:
    MoneyAnimation(Money &entity);
    void update(float delta);

private:
    Money *money;
    unsigned int slide = 0;

};


#endif //CSCI437_MONEYANIMATION_H
