#ifndef CSCI431_EQUIPMENT_H
#define CSCI431_EQUIPMENT_H

#include <unordered_map>
#include <string>
#include <utility>

enum EquipSlot {None, Head, Chest, Shoulders, Legs, Feet, Hands, Ring };
enum EquipSet
{
	Crimson_Rogue,
	Forest_Priest,
	Guard,
	Iron_Hunter,
	Renegade,
	Cultist,
	Gatekeeper,
	Illusionist,
	Marauder,
	Sharpshooter
};

class Equipment
{
	private:
		bool equipped;
		std::unordered_map<std::string, int> statData;
		int statTotal;

		EquipSlot slot;
		EquipSet set;

	protected:

	public:
		Equipment(EquipSet, EquipSlot, int, int, int, int, int);
		~Equipment();
		int getStat(std::string);
		int getStatTotal();
		bool isEquipped(){return this->equipped;};
		void setEquipped(bool);

		EquipSlot getSlot() {return  slot;}
		EquipSet getSet() {return set;}
};

#endif //CSCI431_EQUIPMENT_H
