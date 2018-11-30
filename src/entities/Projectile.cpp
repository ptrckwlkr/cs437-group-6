#include "entities/Projectile.h"
#include "EntityManager.h"

Projectile::Projectile(float x, float y) : Entity(x, y, PROJECTILE_SIZE_DEFAULT) {
    speed = PROJECTILE_SPEED_DEFAULT;
    maxRange = 500;
    traveled = 0;
    damage = 0;
    obstructible = true; // TODO?
    trail_enabled = true;
    for (int i = 0; i < 5; i++)
        trail.emplace_back(pos);

    EventManager::Instance()->registerListener(EventWallCollision::eventType, this, &handleWallCollision);
    EventManager::Instance()->registerListener(EventCollision::eventType, this, &handleCollision);
}

Projectile::~Projectile()
{

}

void Projectile::move(Vector2D &dir, float delta) {
    old_pos = pos;
    float delta_speed = speed * delta;
    Vector2D change = dir.normal() * delta_speed;
    traveled += change.length;
    pos = pos + change;

    if (trail_enabled)
        updateTrail();
}

void Projectile::handleWallCollision(const EventWallCollision &event) {
    if (event.getEntity().id == id) EntityManager::Instance()->removeEntity(id);
}

void Projectile::handleCollision(const EventCollision &event) {
    if (event.getSelf().id == id && event.getOther().is_hostile()) EntityManager::Instance()->removeEntity(id);
}


//updates coordinates of projectile's trail used for motion blur
void Projectile::updateTrail() {
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
