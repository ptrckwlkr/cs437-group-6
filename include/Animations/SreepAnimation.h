#ifndef CSCI437_SREEPANIMATION_H
#define CSCI437_SREEPANIMATION_H

#include "Animation.h"
#include <entities/sreep.h>

class SreepAnimation: public Animation {

public:
    SreepAnimation(Sreep &entity);
    ~SreepAnimation();
    void update(float delta);

private:
    Sreep *sreep;
    enum Facing {
        LEFT,
        FRONT,
        RIGHT,
    } facing, prev;
    unsigned int slide;

};


#endif //CSCI437_SREEPANIMATION_H
