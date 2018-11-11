#ifndef CSCI437_VIEW_H
#define CSCI437_VIEW_H

#include "game_logic.h"

/**
 * Abstract base class for all controllers.
 */
class View
{

public:
    explicit View(GameLogic *state) : state(state) {};
    ~View() = default;
    virtual void update(float delta) = 0;
    GameLogic &get_state() {return *state;}

protected:
    GameLogic *state;

};

#endif //CSCI437_VIEW_H
