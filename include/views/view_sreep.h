#ifndef CSCI437_VIEW_SREEP_H
#define CSCI437_VIEW_SREEP_H

#include "view.h"
#include "entities/sreep.h"


class SreepView : public View
{

public:
    SreepView(GameLogic *state, Sreep &entity);
    void update(float delta) override;

private:
    Sreep *sreep;
    bool aggro;
    bool firing;
    int fire_option;
    int shots_fired;
    int stream_fired;
    float timer;


};


#endif //CSCI437_VIEW_SREEP_H
