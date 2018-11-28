#include "Projectile.h"
#include "EventManager.h"

Projectile::Projectile(float x, float y) : Entity(x, y, PROJECTILE_SIZE_DEFAULT){
  speed = PROJECTILE_SPEED_DEFAULT;
  maxRange = 500;
  traveled = 0;
  damage = 0;
  type = TYPE_PROJECTILE;
  obstructible = true; // TODO?
}

void Projectile::move(Vector2D &dir, float delta){
  old_pos = pos;
  float delta_speed = speed * delta;
  Vector2D change = dir.normal() * delta_speed;
  traveled += change.length;
  pos = pos + change;
}