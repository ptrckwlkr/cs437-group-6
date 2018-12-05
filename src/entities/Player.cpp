#include "entities/Player.h"
#include "entities/Projectile.h"
#include "entities/melee.h"
#include "events/event_player_died.h"
#include "EntityManager.h"

Player::Player(float x, float y) : Entity(x, y, PLAYER_SIZE)
{
    obstructible = true;
}

void Player::l_attack(Vector2D &dir, float delta) {

    if (l_delta <= 0 && mana > data->get_l_mana_cost()) {
        float x = pos.x;
        float y = pos.y;
        auto projectile = EntityManager::Instance().createEntity<Projectile>(x, y);
        projectile->set_direction(dir);
        projectile->set_damage(damage);
        projectile->trail_enabled = true;
        l_delta = l_cooldown;
        mana -= data->get_l_mana_cost();
    }
}

void Player::r_attack(Vector2D &dir, float delta) {

    if (r_delta <= 0) {
        Vector2D p = pos + dir.normal() * size * 1.5;
        auto melee = EntityManager::Instance().createEntity<Melee>(p.x, p.y);
        melee->setRadius(36);
        melee->setDirection(dir);
        melee->set_damage(damage);
        r_delta = r_cooldown;
    }
}

void Player::die()
{
    EventPlayerDied event;
    EventManager::Instance().sendEvent(event);
}

void Player::update(float delta)
{
    data->set_health(health);
    data->set_mana(mana);
    if (mana < max_mana)
        mana += delta * mana_regen;
    else
        mana = max_mana;
    if (l_delta > 0) l_delta -= delta;
    if (r_delta > 0) r_delta -= delta;
}

void Player::set_player_data(PlayerData *d)
{
    data        = d;
    health      = d->get_health();
    mana        = d->get_mana();
    max_health  = d->get_max_health();
    max_mana    = d->get_max_mana();
    l_cooldown  = d->get_l_cooldown();
    r_cooldown  = d->get_r_cooldown();
    mana_regen  = d->get_mana_regen();
    speed       = d->get_speed();
    damage      = d->get_damage();
    defence     = d->get_defence();
}
