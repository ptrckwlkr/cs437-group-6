#ifndef CSCI437_VIEW_ORC_H
#define CSCI437_VIEW_ORC_H

#include <cmath>
#include "view.h"
#include "entities/Orc.h"


class OrcView : public View
{

enum OrcState
{
    PASSIVE,
    AGGRO,
    SEARCH
};

public:
    OrcView(GameLogic *state, Orc &entity);
    void update(float delta) override;
    OrcState cur_state;
    std::string GetType() {return type;}

private:
    Orc *orc;
    std::string type;

    //update methods for different kinds of Orcs
    void updateGreen(float delta, Vector2D dir);
    void updateRed(float delta, Vector2D dir);
    void updateGold(float delta, Vector2D dir);
};

#endif //CSCI437_VIEW_ORC_H
