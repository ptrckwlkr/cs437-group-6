#include "entities/sreep_projectile.h"
#include "EntityManager.h"

SreepProjectile::SreepProjectile(float x, float y) : Entity(x, y, SREEP_PROJECTILE_SIZE_DEFAULT) {
  speed = SREEP_PROJECTILE_SPEED_DEFAULT;
  hostile = false;
  maxRange = 500;
  traveled = 0;
  hit = false;
  obstructible = false;

  EventManager::Instance().registerListener(EventWallCollision::eventType, this, &SreepProjectile::handleWallCollision);
  EventManager::Instance().registerListener(EventCollision::eventType, this, &SreepProjectile::handleCollision);
}

void SreepProjectile::move(Vector2D &dir, float delta) {
  old_pos = pos;
  float delta_speed = speed * delta;
  Vector2D change = dir.normal() * delta_speed;
  traveled += change.length;
  pos = pos + change;
}

void SreepProjectile::handleWallCollision(const EventWallCollision &event) {
  if (event.getEntity().id == id) EntityManager::Instance().removeEntity(id);
}

void SreepProjectile::handleCollision(const EventCollision &event) {
  if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType && !hit)
  {
    hit = true;
    EntityManager::Instance().removeEntity(id);
    event.getOther().take_damage(damage);
    EventEntityDamaged postDamaged = EventEntityDamaged(event.getOther().id, event.getOther().getEntityType());
    EventManager::Instance().sendEvent(postDamaged);
  }
}

