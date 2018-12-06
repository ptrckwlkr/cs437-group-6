#ifndef CSCI431_EQUIPMENT_H
#define CSCI431_EQUIPMENT_H

#include <array>
#include <string>
#include <utility>

enum Stat
{
	Attack  = 0,
	Magic   = 1,
	Defence = 2,
	Health  = 3,
	Mana		= 4,
};

enum EquipSlot
{
	Head 			= 0,
	Chest 		= 1,
	Shoulders = 2,
	Legs 			= 3,
	Feet 			= 4,
	Hands 		= 5
};

enum EquipSet
{
	Renegade			= 0,
	Crimson_Rogue = 1,
	Forest_Priest = 2,
	Guard					= 3,
	Iron_Hunter   = 4,
	Cultist				= 5,
	Gatekeeper		= 6,
	Illusionist   = 7,
	Marauder      = 8,
	Sharpshooter  = 9
};

class Equipment
{
	private:
		bool equipped = false;
		std::array<int, 5> stats;
		int statTotal;
		EquipSlot slot;
		EquipSet set;

	protected:

	public:
		Equipment(EquipSet, EquipSlot, int, int, int, int, int);
		~Equipment() = default;
		int getStat(Stat stat);
		int getStatTotal();
		bool isEquipped(){return this->equipped;};
		void setEquipped(bool);

		EquipSlot getSlot() {return slot;}
		EquipSet getSet() {return set;}
};

#endif //CSCI431_EQUIPMENT_H
