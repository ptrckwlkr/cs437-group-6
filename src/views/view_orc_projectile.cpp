#include "views/view_orc_projectile.h"

OrcProjectileView::OrcProjectileView(GameLogic *state, OrcProjectile &entity) : View(state)
{
  projectile = &entity;
}

void OrcProjectileView::update(float delta)
{
  Vector2D dir = projectile->get_direction();
  projectile->move(dir, delta);
}
