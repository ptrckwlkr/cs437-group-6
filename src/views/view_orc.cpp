#include "views/view_orc.h"
#include "macros.h"
#include "EntityManager.h"
#include "engine.h"
#include <climits>

OrcView::OrcView(GameLogic *state, Orc &s) : View(state) {
    orc = &s;
    cur_state = PASSIVE;
    type = orc->type;
}

void OrcView::update(float delta) {
    //get player position
    Vector2D dir = state->get_level().get_player().get_position() - orc->get_position();
    float hypo = state->get_level().get_player().get_size() + orc->get_size();
    if (cur_state != PASSIVE || (dir.length < orc->aggro_dist && hypo * hypo < dir.length * dir.length)) {
        if (type == "orc-green")
            updateGreen(delta, dir);
        else if (type == "orc-red")
            updateRed(delta, dir);
        else if (type == "orc-gold")
            updateGold(delta, dir);
    }
}


/*
 * green orcs are not smart and just chase the player and fire while it is in range.
 * This kind of orc has no need for search as a result
 */
void OrcView::updateGreen(float delta, Vector2D dir) {
    if (cur_state == PASSIVE)
        cur_state = AGGRO;

    //note threshold for going from aggro to passive is larger than going from passive to aggro
    if (dir.length < 1.5 * orc->aggro_dist)
        //this is just a value that makes things look good
        if ( dir.length > 7 * CELL_SIZE/2)
            orc->move(dir, delta);
        else
            orc->attack(delta, 75/60.f, dir);
    else
        cur_state = PASSIVE;

}

/*
 * Red orcs are smarter; they know when the player visits certain path nodes.
 * They will chase the player but if their next move puts them into a wall, they
 * change their target to path nodes recently visited by the player
 */
void OrcView::updateRed(float delta, Vector2D dir) {
    if (cur_state == PASSIVE)
        cur_state = AGGRO;

    static Vector2D target = state->get_level().get_player().get_position();

    //note threshold for going from aggro to passive is larger than going from passive to aggro
    if (dir.length < 1.5 * orc->aggro_dist) {
        if ( dir.length > 7 * CELL_SIZE/2)
        {
            Vector2D temp = (target - orc->get_position()).normal();
            temp.x = round(temp.x);
            temp.y = round(temp.y);
            Vector2D future_pos = orc->get_position() + temp * CELL_SIZE;

            //if chasing the player does not result in collision with a wall then do that
            if (cur_state == AGGRO && state->get_level().get_map().get_cell((int) future_pos.y / CELL_SIZE,
                                                                            (int) future_pos.x /
                                                                            CELL_SIZE).get_cell_type() != WALL) {
                target = state->get_level().get_player().get_position();
            } else if (cur_state == SEARCH) {
                //already following path so check the distance to the current target path node
                if ((target - orc->get_position()).length < CELL_SIZE / 4) {
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
                //make sure not to switch to search state if the orc is within a cell of the player
                if ((state->get_level().get_player().get_position() - orc->get_position()).length < CELL_SIZE) {
                    target = state->get_level().get_player().get_position();
                } else {
                    cur_state = SEARCH;
                    Map::iterable_queue<Vector2D> nodes = state->get_level().get_map().getRecentNodes();

                    // empty list (player has not walked through path node so try chasing
                    if (nodes.size() == 0) {
                        cur_state = AGGRO;
                        target = state->get_level().get_player().get_position();
                    } else
                        target = nodes.back();
                }

            }

            dir = target - orc->get_position();
            orc->move(dir, delta);
        }
        else
            orc->attack(delta, 60/60.f, dir);


    } else
        cur_state = PASSIVE;
}


/*
 * Gold orcs are the smartest; they know the most recent cells the player has visited
 * They will chase the player but if their next move puts them into a wall, they
 * change their target to the player's recent path
 */
void OrcView::updateGold(float delta, Vector2D dir) {
    if (cur_state == PASSIVE)
        cur_state = SEARCH;

    //note threshold for going from aggro to passive is larger than going from passive to aggro
    if (dir.length < 1.5 * orc->aggro_dist) {

        Vector2D target;

        if (cur_state == AGGRO)
        {
            Vector2D tmp = dir.normal();
            tmp.x = round(tmp.x);
            tmp.y = round(tmp.y);
            Vector2D future_pos = orc->get_position() + tmp * CELL_SIZE;

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
            int orc_i = (int) orc->get_position().x / CELL_SIZE;
            int orc_j = (int) orc->get_position().y / CELL_SIZE;

            int target_i, target_j;

            //iterate through 8 adjacent cells and target one with minimum cost
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    if (a == 0 && b == 0) continue;
                    if (cell_cost[orc_j + a][orc_i + b] > -1 && cell_cost[orc_j + a][orc_i + b] < min_cost)
                    {
                        min_cost = cell_cost[orc_j + a][orc_i + b];
                        target_i = orc_i + b, target_j = orc_j + a;
                    }
                }
            }


            if (min_cost > 1)
                target = Vector2D(target_i*CELL_SIZE + CELL_SIZE/2, target_j*CELL_SIZE + CELL_SIZE/2)
                         - orc->get_position();
            else
            {
                cur_state = AGGRO;
                target = dir;
            }
        }

        if (dir.length > 7 * CELL_SIZE/2){
            orc->move(target, delta);
        }
        else
            orc->attack(delta, 45/60.f, dir);
    }
    else
        cur_state = PASSIVE;



}
