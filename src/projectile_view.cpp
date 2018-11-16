#include <game_logic.h>
#include "projectile_view.h"

ProjectileView::ProjectileView(GameLogic *state, Projectile &entity) : View(state)
{
  projectile = &entity;
}

void ProjectileView::update(float delta)
{
  Vector2D dir = projectile->get_direciton();
  projectile->move(dir, delta);
}
