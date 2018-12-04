#include "entities/orc_projectile.h"
#include "EntityManager.h"
#include "events/event_projectile_fired.h"
#include "events/event_entity_damaged.h"

OrcProjectile::OrcProjectile(float x, float y) : Entity(x, y, PROJECTILE_SIZE_DEFAULT) {
  speed = PROJECTILE_SPEED_DEFAULT;
  hostile = true;
  maxRange = 500;
  traveled = 0;
  hit = false;
  obstructible = false;
  trail_enabled = true;
  for (int i = 0; i < 5; i++)
    trail.emplace_back(pos);

  EventProjectileFired postFired = EventProjectileFired(id);
  EventManager::Instance().sendEvent(postFired);

  EventManager::Instance().registerListener(EventWallCollision::eventType, this, &OrcProjectile::handleWallCollision);
  EventManager::Instance().registerListener(EventCollision::eventType, this, &OrcProjectile::handleCollision);
}

void OrcProjectile::move(Vector2D &dir, float delta) {
  old_pos = pos;
  float delta_speed = speed * delta;
  Vector2D change = dir.normal() * delta_speed;
  traveled += change.length;
  pos = pos + change;

  if (trail_enabled)
    updateTrail();
}

void OrcProjectile::handleWallCollision(const EventWallCollision &event) {
  if (event.getEntity().id == id) EntityManager::Instance().removeEntity(id);
}

void OrcProjectile::handleCollision(const EventCollision &event) {
  if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType && !hit)
  {
    hit = true;
    EntityManager::Instance().removeEntity(id);
    event.getOther().take_damage(damage);
    EventEntityDamaged postDamaged = EventEntityDamaged(event.getOther().id, event.getOther().getEntityType());
    EventManager::Instance().sendEvent(postDamaged);
  }
}


//updates coordinates of projectile's trail used for motion blur
void OrcProjectile::updateTrail() {
  for (int i = 4; i > -1; i--) {
    if (i == 0)
    {
      trail[i].x = pos.x;
      trail[i].y = pos.y;
    }
    else
    {
      trail[i].x = trail[i - 1].x;
      trail[i].y = trail[i - 1].y;
    }
  }
}
