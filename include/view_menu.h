#ifndef CSCI437_VIEW_MENU_H
#define CSCI437_VIEW_MENU_H

#include <SFML/Graphics.hpp>
#include "game_logic.h"
#include "view.h"



class MenuView : public View
{

public:
	MenuView(GameLogic *state);

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void storeStaticText();
	void drawDynamicText(sf::RenderTarget &target, sf::RenderStates states) const;

	void drawTitleScreenDynamicText(sf::RenderTarget &target, sf::RenderStates states, int index) const;

	sf::Font font;
	sf::Text title;

};


#endif //CSCI437_VIEW_MENU_H