#ifndef CSCI437_VIEW_H
#define CSCI437_VIEW_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include "game_logic.h"
#include "../rapidxml/rapidxml.hpp"
#include "ResourceManager.h"
#include <memory>
#include <string>

/**
 * Base class for all the graphical views.
 */
class View : public sf::Drawable, public sf::Transformable
{

public:
    explicit View(GameLogic *state) : state(state) {};

	// finds element in under root node in xml file and creates sf::Text object with parameters
	sf::Text prepareText(std::string elementName) const
	{
		sf::Text text;
		rapidxml::xml_node<> *node = root_node->first_node(elementName.c_str());
		text.setString(node->first_node("text")->value());
		text.setCharacterSize(std::stoi(node->first_node("size")->value()));
		int r = std::stoi(node->first_node("r")->value());
		int g = std::stoi(node->first_node("g")->value());
		int b = std::stoi(node->first_node("b")->value());
		text.setFillColor(sf::Color(r, g, b));

		return text;

	};

protected:
    GameLogic *state;

	//ensures the xml file text does not go out of scope
	rapidxml::xml_node<> *root_node;
	std::shared_ptr <std::vector<char>> buffer;
};

//global access to resource manager
extern ResourceManager resources;

#endif //CSCI437_VIEW_H
