#ifndef CSCI437_VIEW_GHOST_H
#define CSCI437_VIEW_GHOST_H

#include <cmath>
#include "view.h"
#include "entities/ghost.h"


class GhostView : public View
{


enum GhostState
{
    PASSIVE,
    AGGRO
};

public:
    GhostView(GameLogic *state, Ghost &entity);
    void update(float delta) override;
    GhostState cur_state;
    std::string GetType() {return type;}

private:
    Ghost *ghost;
    std::string type;

    //update methods for ghosts specifically
    void updateGhost(float delta, Vector2D dir);



};

#endif //CSCI437_VIEW_GHOST_H
