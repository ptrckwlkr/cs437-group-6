#ifndef CSCI431_EQUIPMENT_H
#define CSCI431_EQUIPMENT_H

#include <unordered_map>
#include <string>
#include <utility>

enum EquipSlot { Head, Chest, Shoulders, Legs, Feet, Hands, Ring };

class Equipment
{
	private:
		bool equipped;
		std::unordered_map<std::string, int> statData;

	protected:

	public:
		Equipment();
		Equipment(int, int, int, int, int);
		~Equipment();
		EquipSlot type;
		int getStat(std::string);
		bool isEquipped(){return this->equipped;};
		void setEquipped(bool);
};

#endif //CSCI431_EQUIPMENT_H
