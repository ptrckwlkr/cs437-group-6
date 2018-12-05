#include "views/view_sreep_projectile.h"

SreepProjectileView::SreepProjectileView(GameLogic *state, SreepProjectile &entity) : View(state)
{
  projectile = &entity;
}

void SreepProjectileView::update(float delta)
{
  Vector2D dir = projectile->get_direction();
  projectile->move(dir, delta);
}
