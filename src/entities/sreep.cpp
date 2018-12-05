#include "entities/explosion.h"
#include "EntityManager.h"
#include "entities/sreep.h"
#include "entities/sreep_projectile.h"

Sreep::Sreep(float x, float y) : Enemy(x, y, SREEP_SIZE) {
  obstructible = true;
  hostile = true;
  defence = 25;
  damage = 25;
  health = 500;
  speed = 75;

  EventManager::Instance().registerListener(EventCollision::eventType, this, & Sreep::handleCollision);
}

void Sreep::handleCollision(const EventCollision &event)
{
  if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType)
  {
    event.getOther().take_damage(damage);
  }
}


void Sreep::die()
{
  EntityManager::Instance().removeEntity(id);
  EntityManager::Instance().createEntity<Explosion>(pos.x, pos.y);
}

void Sreep::fire_all_dirs()
{
  Vector2D loc = pos + VEC_NORTH.normal() * size;
  auto projectile = EntityManager::Instance().createEntity<SreepProjectile>(loc.x, loc.y);
  projectile->set_direction(VEC_NORTH);
  projectile->set_damage(damage);

  loc = pos + VEC_NORTHEAST.normal() * size;
  projectile = EntityManager::Instance().createEntity<SreepProjectile>(loc.x, loc.y);
  projectile->set_direction(VEC_NORTHEAST);
  projectile->set_damage(damage);

  loc = pos + VEC_EAST.normal() * size;
  projectile = EntityManager::Instance().createEntity<SreepProjectile>(loc.x, loc.y);
  projectile->set_direction(VEC_EAST);
  projectile->set_damage(damage);

  loc = pos + VEC_SOUTHEAST.normal() * size;
  projectile = EntityManager::Instance().createEntity<SreepProjectile>(loc.x, loc.y);
  projectile->set_direction(VEC_SOUTHEAST);
  projectile->set_damage(damage);

  loc = pos + VEC_SOUTH.normal() * size;
  projectile = EntityManager::Instance().createEntity<SreepProjectile>(loc.x, loc.y);
  projectile->set_direction(VEC_SOUTH);
  projectile->set_damage(damage);

  loc = pos + VEC_SOUTHWEST.normal() * size;
  projectile = EntityManager::Instance().createEntity<SreepProjectile>(loc.x, loc.y);
  projectile->set_direction(VEC_SOUTHWEST);
  projectile->set_damage(damage);

  loc = pos + VEC_WEST.normal() * size;
  projectile = EntityManager::Instance().createEntity<SreepProjectile>(loc.x, loc.y);
  projectile->set_direction(VEC_WEST);
  projectile->set_damage(damage);

  loc = pos + VEC_NORTHWEST.normal() * size;
  projectile = EntityManager::Instance().createEntity<SreepProjectile>(loc.x, loc.y);
  projectile->set_direction(VEC_NORTHWEST);
  projectile->set_damage(damage);
}

void Sreep::fire_at_player()
{
  Vector2D dir = EntityManager::Instance().getPlayer()->get_position() - pos;
  Vector2D loc = pos + dir.normal() * size;
  auto projectile = EntityManager::Instance().createEntity<SreepProjectile>(loc.x, loc.y);
  projectile->set_direction(dir);
  projectile->set_damage(damage);
}
