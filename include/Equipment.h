#ifndef CSCI431_EQUIPMENT_H
#define CSCI431_EQUIPMENT_H

#include <unordered_map>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>

enum EquipSlot { Head, Chest, Shoulders, Legs, Feet, Hands, Ring };

class Equipment
{
	private:
		bool equipped;
		std::unordered_map<std::string, int> statData;
		sf::Sprite icon;

	protected:

	public:
		Equipment();
		Equipment(int, int, int, int, int, std::string);
		~Equipment();
		EquipSlot type;
		int getStat(std::string);
		bool isEquipped(){return this->equipped;};
		void setEquipped(bool);
};

#endif //CSCI431_EQUIPMENT_H
