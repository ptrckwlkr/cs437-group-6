#include "EntityManager.h"
#include "views/view_projectile.h"
#include "engine.h"

ProjectileView::ProjectileView(GameLogic *state, Projectile &entity) : View(state)
{
  projectile = &entity;
}

void ProjectileView::update(float delta)
{
  Vector2D dir = projectile->get_direciton();
  projectile->move(dir, delta);
}
