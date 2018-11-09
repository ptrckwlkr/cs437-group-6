#ifndef CSCI437_PLAYER_DATA_H
#define CSCI437_PLAYER_DATA_H

#include <memory>
#include "weapon.h"
#include "ability.h"
#include "inventory.h"

/**
 * Class to store persistent player data, such as currency, weapons, etc.
 */
class PlayerData
{

public:
    PlayerData();
    void add_gold(int amount) {gold += amount;}
    int get_gold() {return gold;}
    std::shared_ptr<Weapon> &get_curr_weapon() {return curr_weapon;}
    std::shared_ptr<Ability> &get_curr_ability() {return curr_ability;}
    Inventory &get_inventory() {return inventory;}

private:
    int gold;
    std::shared_ptr<Weapon> curr_weapon;
    std::shared_ptr<Ability> curr_ability;
    Inventory inventory;

};


#endif //CSCI437_PLAYER_DATA_H
