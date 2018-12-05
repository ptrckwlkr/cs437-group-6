#include "views/view_boss.h"


BossView::BossView(GameLogic *state, Boss &b) : View(state) {
    boss = &b;
    cur_state = PASSIVE;
    type = boss->type;
}

void BossView::update(float delta) {
    //get player position
    Vector2D dir = state->get_level().get_player().get_position() - boss->get_position();
    float hypo = state->get_level().get_player().get_size() + boss->get_size();
    if (cur_state != PASSIVE || (dir.length < boss->aggro_dist && hypo * hypo < dir.length * dir.length)) {
        updateBoss(delta, dir);
    }
}

void BossView::updateBoss(float delta, Vector2D dir) {
    //TODO figure out how we want the final boss to act
}