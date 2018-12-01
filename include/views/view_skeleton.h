#ifndef CSCI437_SKELETONVIEW_H
#define CSCI437_SKELETONVIEW_H

#include <cmath>
#include "view.h"
#include "entities/skeleton.h"


class SkeletonView : public View
{


enum SkeletonState
{
    PASSIVE,
    AGGRO,
    SEARCH
};

public:
    SkeletonView(GameLogic *state, Skeleton &entity);
    void update(float delta) override;
    SkeletonState cur_state;
    std::string GetType() {return type;};

private:
    Skeleton *skeleton;
    std::string type;

    //update methods for different kinds of skeletons
    void updateWhite(float delta);
    void updateRed(float delta);
    void updateGold(float delta);


    double DiagonalDistance(Vector2D cur_pos, Vector2D player_pos);

};


#endif //CSCI437_SKELETONVIEW_H
