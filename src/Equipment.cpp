#include "Equipment.h"

#include <iostream>

Equipment::Equipment(EquipSet set, EquipSlot slot, int atk, int mag, int def, int health, int mana)
{
    this->slot = slot;
    this->set = set;
    this->statData.insert(std::pair<std::string, int>("Attack", atk));
    this->statData.insert(std::pair<std::string, int>("Magic", mag));
    this->statData.insert(std::pair<std::string, int>("Defense", def));
    this->statData.insert(std::pair<std::string, int>("Health", health));
    this->statData.insert(std::pair<std::string, int>("Mana", mana));
    this->statTotal = atk + mag + def + health + mana;
}

Equipment::~Equipment() {

}

int Equipment::getStat(std::string stat) {
    return statData.at(stat);
}

int Equipment::getStatTotal() {
    return statTotal;
}

void Equipment::setEquipped(bool equip) {
    this->equipped = equip;
}
