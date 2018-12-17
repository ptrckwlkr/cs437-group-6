#ifndef CSCI437_GRAPHICS_H
#define CSCI437_GRAPHICS_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include "../../rapidxml/rapidxml.hpp"
#include "ResourceManager.h"
#include "macros.h"
#include <memory>
#include <string>

/**
 * Base class for all the graphical views.
 */
class Graphics : public sf::Drawable, public sf::Transformable
{

public:
  Graphics() = default;
	virtual void update(float delta) {}

	/* finds element in under root node in xml file and creates sf::Text object with given parameters
	    Note that the text will have an origin at its center. Since params are in xml file they can be changed without recompiling.
		XML format:
		<elementname>
		  <text>String for sf::Text</text>
		  <size>character size for text (as int)</size>
		  <r or g or b>int for red/green/blue color value</r or g or b>*/
	sf::Text prepareText(std::string elementName, const sf::Font &font, bool centered = true) const
	{
		sf::Text text;
		rapidxml::xml_node<> *node = root_node->first_node(elementName.c_str());
		text.setString(node->first_node("text")->value());
		text.setCharacterSize(std::stoi(node->first_node("size")->value()));
		int r = std::stoi(node->first_node("r")->value());
		int g = std::stoi(node->first_node("g")->value());
		int b = std::stoi(node->first_node("b")->value());
		text.setFillColor(sf::Color(r, g, b));
		text.setFont(font);
		if (centered) text.setOrigin(text.getLocalBounds().width / 2.0, text.getLocalBounds().height / 2.0);
		return text;
	};



protected:

	//ensures the xml file text does not go out of scope
	rapidxml::xml_node<> *root_node;
	std::shared_ptr <std::vector<char>> buffer;
	const void camera_reset(sf::RenderTarget &target) const
	{
		sf::View camera;
		sf::FloatRect viewport = target.getView().getViewport();
		camera.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
		camera.setViewport(viewport);
		target.setView(camera);
	}

};

//global access to resource manager
extern ResourceManager resources;

#endif //CSCI437_GRAPHICS_H
