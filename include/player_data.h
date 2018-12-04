#ifndef CSCI437_PLAYER_DATA_H
#define CSCI437_PLAYER_DATA_H

#include <memory>
#include "Weapon.h"
#include "inventory.h"
#include "entities/Player.h"
#include "events/event_gold_collection.h"

/**
 * Class to store persistent player data, such as currency, weapons, etc.
 */
class PlayerData
{

public:
    PlayerData();
    void set_player(Player *p);
    void reset();
    void update();

    Weapon &get_curr_weapon() {return *curr_weapon;}
    Inventory &get_inventory() {return inventory;}

    int get_gold() {return gold;}
    void update_gold();
    void handleCollision(const EventGoldCollection &event);

private:
    Player *player;
    int gold;
    std::shared_ptr<Weapon> curr_weapon;
    Inventory inventory;

    float health;
    float mana;

    float base_health;
    float base_mana;
    float base_damage;
    float base_defence;
    float base_speed;
    float base_max_health;
    float base_max_mana;
    float base_mana_regen;

    void set_health();
    void set_mana();
    void set_speed();
    void set_damage();
    void set_defence();
    void set_max_health();
    void set_max_mana();
    void set_mana_regen();

};


#endif //CSCI437_PLAYER_DATA_H
