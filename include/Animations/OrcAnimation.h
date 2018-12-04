#ifndef CSCI437_ORCANIMATION_H
#define CSCI437_ORCANIMATION_H

#include "Animation.h"
#include <entities/orc.h>

class OrcAnimation: public Animation {

public:
    OrcAnimation(Orc &entity);
    ~OrcAnimation() = default;
    void update(float delta);

private:
    Orc *orc;

};

#endif //CSCI437_ORCANIMATION_H
