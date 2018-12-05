#ifndef CSCI431_GEARSET_H
#define CSCI431_GEARSET_H

#include "Equipment.h"
#include <unordered_map>
#include <utility>
#include <string>
#include <memory>

class GearSet
{
	private:
		std::unordered_map<std::string, std::shared_ptr<Equipment>> equippedItems;
	 	std::unordered_map<std::string, int> setStats;

	protected:

	public:
		GearSet();
		void equipItem(std::shared_ptr<Equipment>&);
		std::shared_ptr<Equipment> &getItem(EquipSlot, int=1);
		std::string EquipSlotToString(EquipSlot);
		int getSetStat(std::string);
};

#endif //CSCI431_GEARSET_H
