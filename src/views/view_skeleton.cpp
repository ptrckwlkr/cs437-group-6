#include "view_manager.h"
#include "macros.h"
#include "views/view_skeleton.h"

SkeletonView::SkeletonView(GameLogic *state, Skeleton &s) : View(state)
{
  skeleton = &s;
}

void SkeletonView::update(float delta)
{
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


