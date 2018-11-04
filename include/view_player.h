#ifndef CSCI437_VIEW_PLAYER_H
#define CSCI437_VIEW_PLAYER_H

#include <SFML/Graphics.hpp>
#include "game_logic.h"
#include "view.h"
#include "../rapidxml/rapidxml.hpp"
#include "ResourceManager.h"
#include <memory>

class PlayerView : public View
{

public:
	PlayerView(GameLogic *state);

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void drawUI(sf::RenderTarget &target, sf::RenderStates states, float x, float y) const;
	void drawLevel(sf::RenderTarget &target, sf::RenderStates states) const;
	void storeLevel();

	std::vector<sf::RectangleShape> levelShapes;
	sf::Font font;

	//ensures the xml file text does not go out of scope
	std::shared_ptr<rapidxml::xml_document<>> doc;
	rapidxml::xml_node<> * root_node;
	std::shared_ptr <std::vector<char>> buffer;
};

//global access to resource manager
extern ResourceManager resources;

#endif //CSCI437_VIEW_PLAYER_H
