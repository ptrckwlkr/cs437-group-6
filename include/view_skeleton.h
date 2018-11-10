#ifndef CSCI437_SKELETONVIEW_H
#define CSCI437_SKELETONVIEW_H

#include "view.h"
#include "skeleton.h"

class SkeletonView : public View
{

public:
    SkeletonView(GameLogic *state, Entity &entity);
    void update(float delta) override;

private:
    Skeleton *skeleton;

};


#endif //CSCI437_SKELETONVIEW_H
