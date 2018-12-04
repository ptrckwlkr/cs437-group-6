#include "Equipment.h"

Equipment::Equipment() {
    this->type = EquipSlot::Head;
    this->statData.insert(std::pair<std::string, int>("Attack", 0));
    this->statData.insert(std::pair<std::string, int>("Magic", 0));
    this->statData.insert(std::pair<std::string, int>("Defense", 0));
    this->statData.insert(std::pair<std::string, int>("Health", 0));
    this->statData.insert(std::pair<std::string, int>("Mana", 0));
}

Equipment::Equipment(EquipSlot slot, int atk, int mag, int def, int health, int mana, std::string sprite) {
    this->type = slot;
    this->statData.insert(std::pair<std::string, int>("Attack", atk));
    this->statData.insert(std::pair<std::string, int>("Magic", mag));
    this->statData.insert(std::pair<std::string, int>("Defense", def));
    this->statData.insert(std::pair<std::string, int>("Health", health));
    this->statData.insert(std::pair<std::string, int>("Mana", mana));
    this->icon = sprite;
}

Equipment::~Equipment() {

}

int Equipment::getStat(std::string stat) {
    return statData.at(stat);
}

void Equipment::setEquipped(bool equip) {
    this->equipped = equip;
}

std::string Equipment::getSprite() {
	return icon;
}
