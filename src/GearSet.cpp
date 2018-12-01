#include "GearSet.h"

GearSet::GearSet() {

}

void GearSet::equipItem(Equipment* item) {
	if (!item->isEquipped()) {
		item->setEquipped(true);
	}
}

Equipment* GearSet::getItem(EquipSlot slot, int ringNum) {
	
}
