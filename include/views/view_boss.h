#ifndef CSCI437_VIEW_BOSS_H
#define CSCI437_VIEW_BOSS_H

#include "entities/boss.h"
#include "view.h"

class BossView : public View
{
    enum BossState
    {
        PASSIVE,
        AGGRO,
        SEARCH,
    };

public:
    BossView(GameLogic *state, Boss &entity);
    void update(float delta) override;
    BossState cur_state;
    std::string GetType() {return type;}

private:
    Boss *boss;
    std::string type;

    //update methods for boss specifically
    void updateBoss(float delta, Vector2D dir);



};

#endif //CSCI437_VIEW_BOSS_H
