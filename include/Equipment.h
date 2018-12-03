#ifndef CSCI431_EQUIPMENT_H
#define CSCI431_EQUIPMENT_H

#include <unordered_map>
#include <string>
#include <utility>

enum class EquipSlot { Head, Chest, Shoulders, Legs, Feet, Hands, Ring };

class Equipment
{
	private:
		bool equipped;
		std::unordered_map<std::string, int> statData;
		std::string icon;

	protected:

	public:
		Equipment();
		Equipment(EquipSlot, int, int, int, int, int, std::string);
		~Equipment();
		EquipSlot type;
		int getStat(std::string);
		bool isEquipped(){return this->equipped;};
		void setEquipped(bool);
		std::string getSprite();
};

#endif //CSCI431_EQUIPMENT_H
