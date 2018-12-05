#ifndef CSCI431_EQUIPMENT_H
#define CSCI431_EQUIPMENT_H

#include <unordered_map>
#include <string>
#include <utility>

enum class EquipSlot { Head, Chest, Shoulders, Legs, Feet, Hands, Ring };
enum Equip
{
		empty,
		renegade_head,
		renegade_armor,
		renegade_shoulders,
		renegade_pants,
		renegade_boots,
		renegade_gloves,
};

class Equipment
{
	private:
		bool equipped;
		std::unordered_map<std::string, int> statData;
		Equip item;

	protected:

	public:
		Equipment(EquipSlot, int, int, int, int, int, Equip);
		~Equipment();
		EquipSlot type;
		int getStat(std::string);
		bool isEquipped(){return this->equipped;};
		void setEquipped(bool);
		Equip &getEquipItem();
};

#endif //CSCI431_EQUIPMENT_H
