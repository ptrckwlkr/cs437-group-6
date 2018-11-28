#ifndef CSCI437_SKELETONVIEW_H
#define CSCI437_SKELETONVIEW_H

#include "view.h"
#include "skeleton.h"
#include <math.h>

class SkeletonView : public View
{

public:
    SkeletonView(GameLogic *state, Skeleton &entity);
    void update(float delta) override;

private:
    Skeleton *skeleton;

    void AStar(Vector2D player_pos);
    double DiagonalDistance(const Vector2D cur_pos, const Vector2D player_pos);
};


#endif //CSCI437_SKELETONVIEW_H
