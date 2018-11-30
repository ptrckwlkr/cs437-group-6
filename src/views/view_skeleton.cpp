#include "views/view_skeleton.h"
#include "macros.h"
#include "EntityManager.h"

SkeletonView::SkeletonView(GameLogic *state, Skeleton &s) : View(state)
{
  skeleton = &s;
  cur_state = PASSIVE;
  type = skeleton->type;
}

void SkeletonView::update(float delta)
{
  //get player position
  Vector2D dir = state->get_level().get_player().get_position() - skeleton->get_position();
  float hypo = state->get_level().get_player().get_size() + skeleton->get_size();
  if (dir.length < skeleton->aggro_dist && hypo * hypo < dir.length * dir.length)
  {
    skeleton->move(dir, delta);
  }
  if (skeleton->is_dead())
  {
    EntityManager::Instance()->removeEntity(skeleton->id);
  }
}




/*
 * Used to estimate the cost of moving from cur_pos to player_pos. Heuristic in A* since there are 8 movement directions
 */
double SkeletonView::DiagonalDistance(const Vector2D cur_pos, const Vector2D player_pos) {

  return fmax(fabs(cur_pos.x - player_pos.x), fabs(cur_pos.y - player_pos.y));
}