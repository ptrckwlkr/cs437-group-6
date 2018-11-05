#ifndef CSCI437_VIEW_LEVELSELECT_H
#define CSCI437_VIEW_LEVELSELECT_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "game_logic.h"
#include "view.h"
#include "../rapidxml/rapidxml.hpp"
#include "fstream"


class LevelSelectView : public View
{

public:
	LevelSelectView(GameLogic *state) : View(state) {};

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void init();

	std::vector<sf::Drawable> menuObjects;
	sf::Font font;

	//ensures the xml file text does not go out of scope
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * root_node;
	std::vector<char> buffer;
};


#endif //CSCI437_VIEW_MENU_H
