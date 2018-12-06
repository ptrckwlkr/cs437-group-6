#include "GearSet.h"

GearSet::GearSet() {
  equipItem(std::make_shared<Equipment>(Renegade, Head, 1, 0, 0, 0, 2));
  equipItem(std::make_shared<Equipment>(Renegade, Chest, 0, 2, 0, 2, 0));
  equipItem(std::make_shared<Equipment>(Renegade, Shoulders, 0, 3, 0, 0, 2));
  equipItem(std::make_shared<Equipment>(Renegade, Legs, 2, 0, 0, 4, 0));
  equipItem(std::make_shared<Equipment>(Renegade, Feet, 0, 0, 3, 0, 1));
  equipItem(std::make_shared<Equipment>(Renegade, Hands, 1, 0, 0, 2, 0));
}

void GearSet::equipItem(std::shared_ptr<Equipment> item) {
	if (!item->isEquipped()) {
		item->setEquipped(true);
		EquipSlot type = item->getSlot();
		if (equipped[type]) {
			std::shared_ptr<Equipment> oldItem = equipped[type];
			oldItem->setEquipped(false);

			equipped[type] 				=  item;
			total_stats[Attack] 	+= item->getStat(Attack) - oldItem->getStat(Attack);
			total_stats[Magic] 		+= item->getStat(Magic) - oldItem->getStat(Magic);
			total_stats[Defence] 	+= item->getStat(Defence) - oldItem->getStat(Defence);
			total_stats[Health] 	+= item->getStat(Health) - oldItem->getStat(Health);
			total_stats[Mana] 		+= item->getStat(Mana) - oldItem->getStat(Mana);
		}
		else
		{
			equipped[type] 				=  item;
			total_stats[Attack] 	+= item->getStat(Attack);
			total_stats[Magic] 		+= item->getStat(Magic);
			total_stats[Defence] 	+= item->getStat(Defence);
			total_stats[Health] 	+= item->getStat(Health);
			total_stats[Mana] 		+= item->getStat(Mana);
		}
	}
}

std::shared_ptr<Equipment> &GearSet::getItem(EquipSlot slot) {
	return equipped[slot];
}

int GearSet::getSetStat(Stat stat) {
	return total_stats[stat];
}
