#include "views/view_skeleton.h"
#include "macros.h"
#include "EntityManager.h"

SkeletonView::SkeletonView(GameLogic *state, Skeleton &s) : View(state) {
    skeleton = &s;
    cur_state = PASSIVE;
    type = skeleton->type;
}

void SkeletonView::update(float delta) {
    //get player position
    Vector2D dir = state->get_level().get_player().get_position() - skeleton->get_position();
    float hypo = state->get_level().get_player().get_size() + skeleton->get_size();
    if (cur_state == AGGRO || (dir.length < skeleton->aggro_dist && hypo * hypo < dir.length * dir.length)) {
        if (type == "skeleton-white")
            updateWhite(delta, dir);
        else if (type == "skeleton-red")
            updateRed(delta, dir);
        else if (type == "skeleton-gold")
            updateGold(delta, dir);
    }
}


/*
 * White skeletons are not smart and just chase the player while it is in range.
 * This kind of skeleton has no need for search as a result
 */
void SkeletonView::updateWhite(float delta, Vector2D dir)
{
    if (cur_state == PASSIVE)
        cur_state = AGGRO;

    //note threshold for going from aggro to passive is larger than going from passive to aggro
    if (dir.length < 1.5 * skeleton->aggro_dist)
        skeleton->move(dir, delta);
    else
        cur_state = PASSIVE;

}

/*
 * Red skeletons are smarter; they know when the player visits certain path nodes.
 * They will chase the player but if their next move puts them into a wall, they
 * change their target to path nodes recently visited by the player
 */
void SkeletonView::updateRed(float delta, Vector2D dir)
{
    if (cur_state == PASSIVE)
        cur_state = AGGRO;

    //note threshold for going from aggro to passive is larger than going from passive to aggro
    if (dir.length < 1.5 * skeleton->aggro_dist)
    {
        Vector2D future_pos = skeleton->get_position() + dir.normal() * delta * skeleton->get_speed();

        if (state->get_level().get_map().get_cell((int)future_pos.x / CELL_SIZE,
                (int) future_pos.y / CELL_SIZE).get_cell_type() == WALL)
        {

        }
        skeleton->move(dir, delta);
    }
    else
        cur_state = PASSIVE;

}

/*
 * Gold skeletons are the smartest; they know the most recent cells the player has visited
 * They will chase the player but if their next move puts them into a wall, they
 * change their target to the player's recent path
 */
void SkeletonView::updateGold(float delta, Vector2D dir) {

}