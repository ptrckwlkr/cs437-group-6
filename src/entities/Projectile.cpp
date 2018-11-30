#include "entities/Projectile.h"

Projectile::Projectile(float x, float y) : Entity(x, y, PROJECTILE_SIZE_DEFAULT) {
    speed = PROJECTILE_SPEED_DEFAULT;
    maxRange = 500;
    traveled = 0;
    damage = 0;
    obstructible = true; // TODO?
    trail.reserve(5);
    trail_enabled = true;

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
    if (event.getEntity().id == id) alive = false;
}

void Projectile::handleCollision(const EventCollision &event) {
    if (event.getSelf().id == id && event.getOther().is_hostile()) alive = false;
}


//updates coordinates of projectile's trail used for motion blur
void Projectile::updateTrail() {
    for (int i = 4; i > -1; i--) {
        if (i == 0)
            trail[i] = old_pos;
        else
            trail[i] = trail[i - 1];
    }
}
