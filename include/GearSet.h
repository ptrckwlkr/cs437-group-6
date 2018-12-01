#ifndef CSCI431_GEARSET_H
#define CSCI431_GEARSET_H

#include "Equipment.h"
#include <unordered_map>
#include <utility>
#include <string>

class GearSet
{
	private:
		std::unordered_map<std::string, Equipment*> equippedItems;

	protected:

	public:
		GearSet();
		void equipItem(Equipment*);
		Equipment* getItem(EquipSlot, int = 0);
};

#endif //CSCI431_GEARSET_H
