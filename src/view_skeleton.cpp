#include "view_skeleton.h"

SkeletonView::SkeletonView(GameLogic *state, Entity &entity) : View(state)
{
  skeleton = (Skeleton*)&entity;
}

void SkeletonView::update(float delta)
{
  Position posP = state->get_level().get_player().get_position();
  Position posS = skeleton->get_position();

  float dx = posP.x - posS.x;
  float dy = posP.y - posS.y;
  float hypo = state->get_level().get_player().get_size() + skeleton->get_size();

  Direction dir = NONE;
  if (hypo * hypo < dx * dx + dy * dy)
  {
    int x_dir = 0, y_dir = 0;

    if (dx > 0) x_dir++;
    if (dx < 0) x_dir--;
    if (dy > 0) y_dir--;
    if (dy < 0) y_dir++;

    if (x_dir == 1 && y_dir == 1)			    dir = NORTHEAST;
    else if (x_dir == 1 && y_dir == 0)		dir = EAST;
    else if (x_dir == 1 && y_dir == -1)		dir = SOUTHEAST;
    else if (x_dir == 0 && y_dir == 1)		dir = NORTH;
    else if (x_dir == 0 && y_dir == -1)		dir = SOUTH;
    else if (x_dir == -1 && y_dir == 1)		dir = NORTHWEST;
    else if (x_dir == -1 && y_dir == 0)		dir = WEST;
    else if (x_dir == -1 && y_dir == -1)	dir = SOUTHWEST;
  }
  skeleton->move(dir, delta);
}
