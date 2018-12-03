#include "views/view_ghost.h"
#include "macros.h"
#include "EntityManager.h"
#include "engine.h"


GhostView::GhostView(GameLogic *state, Ghost &g) : View(state) {
    ghost = &g;
    cur_state = PASSIVE;
    type = ghost->type;
}


void GhostView::update(float delta) {
    //get player position
    Vector2D dir = state->get_level().get_player().get_position() - ghost->get_position();
    float hypo = state->get_level().get_player().get_size() + ghost->get_size();
    if (cur_state != PASSIVE || (dir.length < ghost->aggro_dist && hypo * hypo < dir.length * dir.length)) {
        updateGhost(delta, dir);
    }
}


/*
 * Note that all ghosts have the same update since they cannot collide with walls
 * and therefore don't need pathfinding
 */
void GhostView::updateGhost(float delta, Vector2D dir) {
    if (cur_state == PASSIVE)
        cur_state = AGGRO;

    //note threshold for going from aggro to passive is larger than going from passive to aggro
    if (dir.length < 1.5 * ghost->aggro_dist)
        ghost->move(dir, delta);
    else
        cur_state = PASSIVE;

}