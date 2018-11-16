#include <game_logic.h>
#include <view_manager.h>
#include "projectile_view.h"

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
    EntityManager::Instance()->removeEntity(projectile->get_id());
    ViewManager::Instance()->remove_view(get_id());
  }
}
