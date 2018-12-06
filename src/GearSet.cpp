#include "GearSet.h"
#include <memory>

GearSet::GearSet() {

  setStats = {
    {"Attack",  0},
    {"Magic",   0},
    {"Defense", 0},
    {"Health",  0},
    {"Mana",    0}
  };

	auto head 			= std::make_shared<Equipment>(EquipSet::Renegade, EquipSlot::Head, 0, 0, 0, 0, 0);
	auto armor 			= std::make_shared<Equipment>(EquipSet::Renegade, EquipSlot::Chest, 0, 0, 0, 0, 0);
	auto shoulders 	= std::make_shared<Equipment>(EquipSet::Renegade, EquipSlot::Shoulders, 0, 0, 0, 0, 0);
	auto pants 			= std::make_shared<Equipment>(EquipSet::Renegade, EquipSlot::Legs, 0, 0, 0, 0, 0);
	auto boots 			= std::make_shared<Equipment>(EquipSet::Renegade, EquipSlot::Feet, 0, 0, 0, 0, 0);
	auto gloves 		= std::make_shared<Equipment>(EquipSet::Renegade, EquipSlot::Hands, 0, 0, 0, 0, 0);
	equipItem(head);
	equipItem(armor);
	equipItem(shoulders);
	equipItem(pants);
	equipItem(boots);
	equipItem(gloves);
}

void GearSet::equipItem(std::shared_ptr<Equipment> &item) {
	if (!item->isEquipped()) {
		std::string stats[5] = {"Attack","Magic","Defense","Health","Mana"};
		item->setEquipped(true);
		EquipSlot type = item->getSlot();
		if (equippedItems[type]) {
			std::shared_ptr<Equipment> oldItem = equippedItems.at(type);
			oldItem->setEquipped(false);
			equippedItems[type] = item;
			for (int i = 0; i < 5; i++) {
				setStats.at(stats[i]) += item->getStat(stats[i]) - oldItem->getStat(stats[i]);
			}
		} else {
			equippedItems[type] = item;
			for (int i = 0; i < 5; i++) {
				setStats.at(stats[i]) += item->getStat(stats[i]);
			}
		}
	}
}

std::shared_ptr<Equipment> &GearSet::getItem(EquipSlot equipslot, int ringNum) {
	return equippedItems[equipslot];
}

int GearSet::getSetStat(std::string stat) {
	return setStats[stat];
}
