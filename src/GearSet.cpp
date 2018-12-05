#include "GearSet.h"
#include <memory>

GearSet::GearSet() {
	auto head = std::make_shared<Equipment>(EquipSlot::Head, 2, 2, 2, 10, 0, "renegade_head");
	auto armor = std::make_shared<Equipment>(EquipSlot::Chest, 0, 0, 10, 0, 0, "renegade_armor");
	auto shoulders = std::make_shared<Equipment>(EquipSlot::Shoulders, 2, 2, 4, 0, 0, "renegade_shoulders");
	auto pants = std::make_shared<Equipment>(EquipSlot::Legs, 2, 2, 2, 20, 0, "renegade_pants");
	auto boots = std::make_shared<Equipment>(EquipSlot::Feet, 3, 3, 2, 0, 10, "renegade_boots");
	auto gloves = std::make_shared<Equipment>(EquipSlot::Hands, 6, 6, 2, 0, 0, "renegade_gloves");
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
		std::string typestr = EquipSlotToString(item->type);
		if (equippedItems.at(typestr) != 0) {
			std::shared_ptr<Equipment> oldItem = equippedItems.at(typestr);
			oldItem->setEquipped(false);
			equippedItems.at(typestr) = item;
			for (int i = 0; i < 5; i++) {
				setStats.at(stats[i]) += item->getStat(stats[i]) - oldItem->getStat(stats[i]);
			}
		} else {
			equippedItems.at(typestr) = item;
			for (int i = 0; i < 5; i++) {
				setStats.at(stats[i]) += item->getStat(stats[i]);
			}
		}
	}
}

std::shared_ptr<Equipment> &GearSet::getItem(EquipSlot equipslot, int ringNum) {
	switch (equipslot) {
		case EquipSlot::Head:
			return equippedItems.at("Head");
		case EquipSlot::Chest:
			return equippedItems.at("Chest");
		case EquipSlot::Shoulders:
			return equippedItems.at("Shoulders");
		case EquipSlot::Legs:
			return equippedItems.at("Legs");
		case EquipSlot::Feet:
			return equippedItems.at("Feet");
		case EquipSlot::Hands:
			return equippedItems.at("Hands");
		case EquipSlot::Ring:
			return equippedItems.at("Ring1");
	}
}

std::string GearSet::EquipSlotToString(EquipSlot equipslot) {
	switch (equipslot) {
		case EquipSlot::Head:
			return "Head";
		case EquipSlot::Chest:
			return "Chest";
		case EquipSlot::Shoulders:
			return "Shoulders";
		case EquipSlot::Legs:
			return "Legs";
		case EquipSlot::Feet:
			return "Feet";
		case EquipSlot::Hands:
			return "Hands";
		case EquipSlot::Ring:
			return "Ring";
		default:
			return "";
	}
}

int GearSet::getSetStat(std::string stat) {
	return setStats.at(stat);
}
