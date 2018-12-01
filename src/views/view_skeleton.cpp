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
    if (cur_state != PASSIVE || (dir.length < skeleton->aggro_dist && hypo * hypo < dir.length * dir.length)) {
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

    static Vector2D target = state->get_level().get_player().get_position();

    //note threshold for going from aggro to passive is larger than going from passive to aggro
    if (dir.length < 1.5 * skeleton->aggro_dist)
    {
        Vector2D future_pos = skeleton->get_position() + (target - skeleton->get_position()).normal() * CELL_SIZE;

        int temp1 = (int) future_pos.y / CELL_SIZE, temp2 = (int)future_pos.x / CELL_SIZE;
        CellType temp3 = state->get_level().get_map().get_cell((int) future_pos.y / CELL_SIZE, (int)future_pos.x / CELL_SIZE).get_cell_type();

        //if chasing the player does not result in collision with a wall then do that
        if (cur_state == AGGRO && state->get_level().get_map().get_cell((int) future_pos.y / CELL_SIZE, (int) future_pos.x / CELL_SIZE).get_cell_type() != WALL)
        {
            target = state->get_level().get_player().get_position();
        }
        else if (cur_state == SEARCH)
        {
            //already following path so check the distance to the current target path node
            if ((target - skeleton->get_position()).length < CELL_SIZE/3)
            {
                //target path node has been reached, make target the next path node or player if there are no more path nodes
                Map::iterable_queue<Vector2D> nodes = state->get_level().get_map().getRecentNodes();
                Vector2D tmp;
                for(auto it = nodes.begin(); it != nodes.end(); ++it)
                {
                    if ((*it) == target && it != (nodes.end() - 1))
                    {
                        tmp = *(it + 1);
                    }
                    else if ((*it) == target && it == (nodes.end() - 1))
                    {
                        tmp = state->get_level().get_player().get_position();
                        cur_state = AGGRO;
                    }
                }
                target = tmp;
            }
            else
            {
                //don't change target so continues following the path
                if (state->get_level().get_map().get_cell((int) future_pos.y / CELL_SIZE, (int) future_pos.x / CELL_SIZE).get_cell_type() == WALL)
                {
                    cur_state = AGGRO;
                    target = state->get_level().get_player().get_position();
                }
            }

        }
        else //was chasing player but has hit a wall
        {
            //make sure not to switch to search state if the skeleton is within a cell of the player
            if ((state->get_level().get_player().get_position() - skeleton->get_position()).length < CELL_SIZE) {
                target = state->get_level().get_player().get_position();
            }
            else {
                cur_state = SEARCH;
                Map::iterable_queue<Vector2D> nodes = state->get_level().get_map().getRecentNodes();

                // empty list (player has not walked through path node so try chasing
                if (nodes.size() == 0)
                {
                    cur_state = AGGRO;
                    target = state->get_level().get_player().get_position();
                }
                else
                    target = nodes.back();
            }

        }

        dir = target - skeleton->get_position();
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