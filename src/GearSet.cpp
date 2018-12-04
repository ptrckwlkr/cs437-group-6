#include "GearSet.h"

GearSet::GearSet() {
	equipItem(new Equipment(EquipSlot::Head, 2, 2, 2, 10, 0, "renegade_head"));
	equipItem(new Equipment(EquipSlot::Chest, 0, 0, 10, 0, 0, "renegade_armor"));
	equipItem(new Equipment(EquipSlot::Shoulders, 2, 2, 4, 0, 0, "renegade_shoulders"));
	equipItem(new Equipment(EquipSlot::Legs, 2, 2, 2, 20, 0, "renegade_pants"));
	equipItem(new Equipment(EquipSlot::Feet, 3, 3, 2, 0, 10, "renegade_boots"));
	equipItem(new Equipment(EquipSlot::Hands, 6, 6, 2, 0, 0, "renegade_gloves"));
}

void GearSet::equipItem(Equipment* item) {
	if (!item->isEquipped()) {
		std::string stats[5] = {"Attack","Magic","Defense","Health","Mana"};
		item->setEquipped(true);
		std::string typestr = EquipSlotToString(item->type);
		if (equippedItems.at(typestr) != 0) {
			Equipment* oldItem = equippedItems.at(typestr);
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

Equipment* GearSet::getItem(EquipSlot equipslot, int ringNum) {
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
		default:
			return 0;
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

GearSet gear = GearSet();
