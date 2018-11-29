#include "entities/Projectile.h"
#include "EventManager.h"

Projectile::Projectile(float x, float y) : Entity(x, y, PROJECTILE_SIZE_DEFAULT){
  speed = PROJECTILE_SPEED_DEFAULT;
  maxRange = 500;
  traveled = 0;
  damage = 0;
  obstructible = true; // TODO?

  EventManager::Instance()->registerListener(EventWallCollision::eventType, this, &handleWallCollision);
}

Projectile::~Projectile()
{
  EventManager::Instance()->unregisterListener(EventWallCollision::eventType, this);
}

void Projectile::move(Vector2D &dir, float delta){
  old_pos = pos;
  float delta_speed = speed * delta;
  Vector2D change = dir.normal() * delta_speed;
  traveled += change.length;
  pos = pos + change;
}

void Projectile::handleWallCollision(const EventWallCollision &event)
{
  if (event.getEntity().id == id) alive = false;
}
