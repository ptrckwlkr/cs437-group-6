#ifndef CSCI437_GHOSTANIMATION_H
#define CSCI437_GHOSTANIMATION_H

#include "Animation.h"
#include <entities/ghost.h>


class GhostAnimation : public Animation {

public:
    GhostAnimation(Ghost &entity);
    ~GhostAnimation() = default;
    void update(float delta);

private:
    Ghost *ghost;
};


#endif //CSCI437_GHOSTANIMATION_H
