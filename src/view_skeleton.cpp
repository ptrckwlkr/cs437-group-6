#include "view_skeleton.h"

SkeletonView::SkeletonView(GameLogic *state, Entity &entity) : View(state)
{
  skeleton = (Skeleton*)&entity;
}

void SkeletonView::update(float delta)
{
  Position posP = state->get_level().get_player()->get_position();
  Position posS = skeleton->get_position();

  float dx = posP.x - posS.x;
  float dy = posP.y - posS.y;
  float hypo = state->get_level().get_player()->get_size() + skeleton->get_size();

  if (hypo * hypo < dx * dx + dy * dy)
  {
    auto dir = Vector2D(dx, dy);
    skeleton->move(dir, delta);
  }
}
