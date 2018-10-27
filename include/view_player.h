#ifndef CSCI437_VIEW_PLAYER_H
#define CSCI437_VIEW_PLAYER_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "game_logic.h"
#include "view.h"
#include "../rapidxml/rapidxml.hpp"
#include "fstream"

class PlayerView : public View
{

public:
	PlayerView(GameLogic *state) : View(state) { init(); };

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void drawLevel(sf::RenderTarget &target, sf::RenderStates states) const;
	void init();
	void storeLevel();

	std::vector<sf::RectangleShape> levelShapes;
	sf::Font font;

	//ensures the xml file text does not go out of scope
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * root_node;
	std::vector<char> buffer;
};

#endif //CSCI437_VIEW_PLAYER_H
