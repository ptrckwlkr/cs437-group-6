#ifndef CSCI437_VIEW_PLAYER_H
#define CSCI437_VIEW_PLAYER_H

#include <SFML/Graphics.hpp>
#include "game_logic.h"
#include "view.h"


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

};


#endif //CSCI437_VIEW_PLAYER_H
