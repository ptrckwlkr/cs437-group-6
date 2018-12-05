#include <climits>
#include "views/view_skeleton.h"
#include "engine.h"

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
void SkeletonView::updateWhite(float delta, Vector2D dir) {
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
void SkeletonView::updateRed(float delta, Vector2D dir) {
    if (cur_state == PASSIVE)
        cur_state = AGGRO;

    static Vector2D target = state->get_level().get_player().get_position();

    //note threshold for going from aggro to passive is larger than going from passive to aggro
    if (dir.length < 1.5 * skeleton->aggro_dist) {
        Vector2D temp = (target - skeleton->get_position()).normal();
        temp.x = round(temp.x);
        temp.y = round(temp.y);
        Vector2D future_pos = skeleton->get_position() + temp * CELL_SIZE;

        //if chasing the player does not result in collision with a wall then do that
        if (cur_state == AGGRO && state->get_level().get_map().get_cell((int) future_pos.y / CELL_SIZE,
                                                                        (int) future_pos.x /
                                                                        CELL_SIZE).get_cell_type() != WALL) {
            target = state->get_level().get_player().get_position();
        } else if (cur_state == SEARCH) {
            //already following path so check the distance to the current target path node
            if ((target - skeleton->get_position()).length < CELL_SIZE / 4) {
                //target path node has been reached, make target the next path node or player if there are no more path nodes
                Map::iterable_queue<Vector2D> nodes = state->get_level().get_map().getRecentNodes();
                Vector2D tmp;
                for (auto it = nodes.begin(); it != nodes.end(); ++it) {
                    if ((*it) == target && it != (nodes.end() - 1)) {
                        tmp = *(it + 1);
                    } else if ((*it) == target && it == (nodes.end() - 1)) {
                        tmp = state->get_level().get_player().get_position();
                        cur_state = AGGRO;
                    }
                }
                target = tmp;
            } else {
                //don't change target so continues following the path
            }

        } else //was chasing player but has hit a wall
        {
            //make sure not to switch to search state if the skeleton is within a cell of the player
            if ((state->get_level().get_player().get_position() - skeleton->get_position()).length < CELL_SIZE) {
                target = state->get_level().get_player().get_position();
            } else {
                cur_state = SEARCH;
                Map::iterable_queue<Vector2D> nodes = state->get_level().get_map().getRecentNodes();

                // empty list (player has not walked through path node so try chasing
                if (nodes.size() == 0) {
                    cur_state = AGGRO;
                    target = state->get_level().get_player().get_position();
                } else
                    //target is most recent path node that the player has entered
                    target = nodes.back();
            }
        }

        dir = target - skeleton->get_position();
        skeleton->move(dir, delta);
    } else
        cur_state = PASSIVE;
}


/*
 * Gold skeletons are the smartest; they know the most recent cells the player has visited
 * They will chase the player but if their next move puts them into a wall, they
 * change their target to the player's recent path
 */
void SkeletonView::updateGold(float delta, Vector2D dir) {
    if (cur_state == PASSIVE)
        cur_state = SEARCH;

    //note threshold for going from aggro to passive is larger than going from passive to aggro
    if (dir.length < 1.5 * skeleton->aggro_dist) {
        Vector2D target;

        if (cur_state == AGGRO)
        {
            Vector2D tmp = dir.normal();
            tmp.x = round(tmp.x);
            tmp.y = round(tmp.y);
            Vector2D future_pos = skeleton->get_position() + tmp * CELL_SIZE;

            //if chasing the player does not result in collision with a wall then do that
            if (state->get_level().get_map().get_cell((int) future_pos.y / CELL_SIZE,
                                                      (int) future_pos.x / CELL_SIZE).get_cell_type() != WALL)
                target = dir;
            else
            {
                cur_state = SEARCH;
            }
        }

        if (cur_state == SEARCH)
        {
            std::vector<std::vector<int>> cell_cost = state->get_level().get_map().getCellCost();
            //player has not left starting cell
            if (cell_cost.size() == 0) return;

            int min_cost = INT_MAX;
            int skeleton_i = (int) skeleton->get_position().x / CELL_SIZE;
            int skeleton_j = (int) skeleton->get_position().y / CELL_SIZE;

            int target_i, target_j;

            //iterate through 8 adjacent cells and target one with minimum cost
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    if (a == 0 && b == 0) continue;
                    if (cell_cost[skeleton_j + a][skeleton_i + b] > -1 && cell_cost[skeleton_j + a][skeleton_i + b] < min_cost)
                    {
                        min_cost = cell_cost[skeleton_j + a][skeleton_i + b];
                        target_i = skeleton_i + b, target_j = skeleton_j + a;
                    }
                }
            }


            if (min_cost > 1)
                target = Vector2D(target_i*CELL_SIZE + CELL_SIZE/2, target_j*CELL_SIZE + CELL_SIZE/2)
                         - skeleton->get_position();
            else
            {
                cur_state = AGGRO;
                target = dir;
            }
        }



        skeleton->move(target, delta);
    }
    else
        cur_state = PASSIVE;



}
