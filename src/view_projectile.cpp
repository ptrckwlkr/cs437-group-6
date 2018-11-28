#include <game_logic.h>
#include <view_manager.h>
#include "view_projectile.h"

ProjectileView::ProjectileView(GameLogic *state, Projectile &entity) : View(state)
{
  projectile = &entity;
}

void ProjectileView::update(float delta)
{
  Vector2D dir = projectile->get_direciton();
  projectile->move(dir, delta);
  if (projectile->get_travaled() > projectile->get_maxRange())
  {
    EntityManager::Instance()->removeEntity(projectile->id);
    ViewManager::Instance()->remove_view(get_id());
  }
}
