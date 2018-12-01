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
    std::string GetType() {return type;}

private:
    Skeleton *skeleton;
    std::string type;

    //update methods for different kinds of skeletons
    void updateWhite(float delta, Vector2D dir);
    void updateRed(float delta, Vector2D dir);
    void updateGold(float delta, Vector2D dir);


};


#endif //CSCI437_SKELETONVIEW_H
