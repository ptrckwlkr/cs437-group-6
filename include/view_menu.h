#ifndef CSCI437_VIEW_MENU_H
#define CSCI437_VIEW_MENU_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "game_logic.h"
#include "view.h"



class MenuView : public View
{

public:
	MenuView(GameLogic *state);

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void init();

	std::vector<sf::Drawable> menuObjects;
	sf::Font font;

	//ensures the xml file text does not go out of scope
	rapidxml::xml_node<> * root_node;
	std::shared_ptr <std::vector<char>> buffer;
};


#endif //CSCI437_VIEW_MENU_H