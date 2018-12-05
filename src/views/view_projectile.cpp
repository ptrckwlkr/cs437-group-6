#include "views/view_projectile.h"

ProjectileView::ProjectileView(GameLogic *state, Projectile &entity) : View(state)
{
  projectile = &entity;
}

void ProjectileView::update(float delta)
{
  Vector2D dir = projectile->get_direction();
  projectile->move(dir, delta);
}
