#include "view_skeleton.h"

SkeletonView::SkeletonView(GameLogic *state, Entity &entity) : View(state)
{
  skeleton = (Skeleton*)&entity;
}

void SkeletonView::update(float delta)
{

}
