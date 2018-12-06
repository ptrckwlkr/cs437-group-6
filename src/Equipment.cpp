#include "Equipment.h"

#include <iostream>

Equipment::Equipment(EquipSet st, EquipSlot sl, int atk, int mag, int def, int health, int mana)
{
    slot            = sl;
    set             = st;
    stats[Attack]   = atk;
    stats[Magic]    = mag;
    stats[Defence]  = def;
    stats[Health]   = health;
    stats[Mana]     = mana;
    statTotal       = atk + mag + def + health + mana;
}

int Equipment::getStat(Stat stat) {
    return stats[stat];
}

int Equipment::getStatTotal() {
    return statTotal;
}

void Equipment::setEquipped(bool equip) {
    equipped = equip;
}
