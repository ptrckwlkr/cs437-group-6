
#ifndef CSCI437_SKELETONANIMATION_H
#define CSCI437_SKELETONANIMATION_H

#include "Animation.h"
#include <entities/skeleton.h>

class SkeletonAnimation: public Animation {

public:
    SkeletonAnimation(Skeleton &entity);
    ~SkeletonAnimation();
    //void initSprite(sf::Texture &texture, sf::Vector2u imageCount, float switchTime);
    void update(float delta);

private:
    Skeleton *skeleton;



};


#endif //CSCI437_SKELETONANIMATION_H
