#include "Equipment.h"

#include <iostream>

Equipment::Equipment(EquipSlot slot, int atk, int mag, int def, int health, int mana, Equip equip) {
    this->type = slot;
    this->statData.insert(std::pair<std::string, int>("Attack", atk));
    this->statData.insert(std::pair<std::string, int>("Magic", mag));
    this->statData.insert(std::pair<std::string, int>("Defense", def));
    this->statData.insert(std::pair<std::string, int>("Health", health));
    this->statData.insert(std::pair<std::string, int>("Mana", mana));
    this->item = equip;
}

Equipment::~Equipment() {

}

int Equipment::getStat(std::string stat) {
    return statData.at(stat);
}

void Equipment::setEquipped(bool equip) {
    this->equipped = equip;
}

Equip &Equipment::getEquipItem() {
	  return item;
}
