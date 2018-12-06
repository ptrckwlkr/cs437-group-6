#ifndef CSCI431_GEARSET_H
#define CSCI431_GEARSET_H

#include "Equipment.h"
#include <unordered_map>
#include <utility>
#include <string>
#include <memory>
#include "Equipment.h"

class GearSet
{
	private:
		std::array<std::shared_ptr<Equipment>, 6> equipped;
	 	std::array<int, 5> total_stats;

	protected:

	public:
		GearSet();
		void equipItem(std::shared_ptr<Equipment>);
		std::shared_ptr<Equipment> &getItem(EquipSlot);
		int getSetStat(Stat stat);
};

#endif //CSCI431_GEARSET_H
