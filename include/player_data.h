#ifndef CSCI437_PLAYER_DATA_H
#define CSCI437_PLAYER_DATA_H

#include <memory>
#include "Weapon.h"
#include "inventory.h"
#include "events/event_gold_collection.h"
#include "events/event_player_died.h"
#include "GearSet.h"

/**
 * Class to store persistent player data, such as currency, weapons, etc.
 */
class PlayerData : public Listener
{

public:
    PlayerData();
    ~PlayerData();
    void reset();

    float get_health();
    float get_mana();
    float get_speed();
    float get_damage();
    float get_defence();
    float get_max_health();
    float get_max_mana();
    float get_mana_regen();
    float get_l_cooldown();
    float get_r_cooldown();
    float get_l_mana_cost();

    void set_health(float h) {health = h;}
    void set_mana(float m) {mana = m;}
    void add_gold(int g) {gold += g;}
    GearSet &get_gear() {return gear;}

    int get_gold() {return gold + level_gold;}
    void handleGoldCollection(const EventGoldCollection &event);
    void handlePlayerDeath(const EventPlayerDied &event);
    void handleLevelComplete(const EventPlayerDied &event);

private:
    int gold;
    int level_gold;

    GearSet gear;

    float health;
    float mana;
    float base_damage;
    float base_defence;
    float base_speed;
    float base_max_health;
    float base_max_mana;
    float base_mana_regen;

};


#endif //CSCI437_PLAYER_DATA_H
