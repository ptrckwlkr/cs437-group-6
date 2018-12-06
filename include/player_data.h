#ifndef CSCI437_PLAYER_DATA_H
#define CSCI437_PLAYER_DATA_H

#include <memory>
#include <events/event_entity_destroyed.h>
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
    //void add_gold() {gold += 20;}
    void add_mana() { mana += 20;}
    void add_health() {health += 20;}
    void subtract_gold(){ gold -= 300;}
    void add_gold(int g) {gold += g;}
    void add_enemy_count() {level_total_enemies +=1;}
    void set_l_cooldown(float cooldown) { l_cooldown = cooldown;}
    void set_l_mana_cost(float cost) { l_mana_cost = cost;}
    GearSet &get_gear() {return gear;}

    int get_gold() {return gold + level_gold;}
    int get_gold_lost(){return gold_lost;}
    int get_total_enemies(){return total_enemies_lost;};
    void handleGoldCollection(const EventGoldCollection &event);
    void handlePlayerDeath(const EventPlayerDied &event);
    void handleLevelComplete(const EventPlayerDied &event);
    void handleEnemiesCount(const EventEntityDestroyed &event);

private:
    int gold;
    int level_gold;
    int total_enemies_lost;
    int level_total_enemies;
    int gold_lost;
    GearSet gear;

    float health;
    float mana;
    float base_damage;
    float base_defence;
    float base_speed;
    float base_max_health;
    float base_max_mana;
    float base_mana_regen;
    float l_cooldown;
    float r_cooldown;
    float l_mana_cost;

};


#endif //CSCI437_PLAYER_DATA_H
