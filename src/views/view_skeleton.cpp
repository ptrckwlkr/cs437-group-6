#include "view_manager.h"
#include "macros.h"
#include "views/view_skeleton.h"

SkeletonView::SkeletonView(GameLogic *state, Skeleton &s) : View(state)
{
  skeleton = &s;
}

void SkeletonView::update(float delta)
{
  //get player position
  Vector2D dir = state->get_level().get_player()->get_position() - skeleton->get_position();
  float hypo = state->get_level().get_player()->get_size() + skeleton->get_size();
  if (dir.length < ENEMY_ACTIVE_DISTANCE && hypo * hypo < dir.length * dir.length)
  {
    skeleton->move(dir, delta);
  }
  if (skeleton->is_dead())
  {
    EntityManager::Instance()->removeEntity(skeleton->id);
    ViewManager::Instance()->remove_view(get_id());
  }
}


void SkeletonView::AStar(Vector2D player_pos)
{

}


/*
 * Used to estimate the cost of moving from cur_pos to player_pos. Heuristic in A* since there are 8 movement directions
 */
double SkeletonView::DiagonalDistance(const Vector2D cur_pos, const Vector2D player_pos) {

  return fmax(fabs(cur_pos.x - player_pos.x), fabs(cur_pos.y - player_pos.y));
}