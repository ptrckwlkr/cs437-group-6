#ifndef CSCI437_VIEW_MENU_H
#define CSCI437_VIEW_MENU_H

#include <SFML/Graphics.hpp>
#include "game_logic.h"
#include "view.h"
#include <vector>
#include <string>


class MenuView : public View
{

public:
	MenuView(GameLogic *state);

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void storeStaticText();
	void storeControlText();

	void drawTitleScreenDynamicText(sf::RenderTarget &target, sf::RenderStates states, int index) const;

	sf::Font font;
	sf::Text title;
	std::vector<sf::Text> menuInstructions;
	std::vector<sf::Text> controls;
	sf::Text aboutText;

};


#endif //CSCI437_VIEW_MENU_H