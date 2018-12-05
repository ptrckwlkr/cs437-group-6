#ifndef CSCI431_EQUIPMENT_H
#define CSCI431_EQUIPMENT_H

#include <unordered_map>
#include <string>
#include <utility>

enum class EquipSlot { Head, Chest, Shoulders, Legs, Feet, Hands, Ring };
enum EquipmentSet
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
		Equip item;

	protected:

	public:
		Equipment(EquipSlot, int, int, int, int, int, Equip);
		~Equipment();
		EquipSlot type;
		int getStat(std::string);
		int getStatTotal();
		bool isEquipped(){return this->equipped;};
		void setEquipped(bool);
		Equip &getEquipItem();
};

#endif //CSCI431_EQUIPMENT_H
