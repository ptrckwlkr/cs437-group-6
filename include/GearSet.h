#ifndef CSCI431_GEARSET_H
#define CSCI431_GEARSET_H

#include "Equipment.h"
#include <unordered_map>
#include <utility>
#include <string>

class GearSet
{
	private:
		std::unordered_map<std::string, Equipment*> equippedItems =
		{	{"Head",0},
			{"Chest",0},
			{"Shoulders",0},
			{"Legs",0},
			{"Feet",0},
			{"Hands",0},
			{"Ring1",0},
			{"Ring2",0} };

	protected:

	public:
		GearSet();
		void equipItem(Equipment*);
		Equipment* getItem(EquipSlot, int=1);
		std::string EquipSlotToString(EquipSlot);
};

extern GearSet gear;

#endif //CSCI431_GEARSET_H
