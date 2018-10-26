#ifndef CSCI437_VIEW_PLAYER_H
#define CSCI437_VIEW_PLAYER_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "game_logic.h"
#include "view.h"

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
};

#endif //CSCI437_VIEW_PLAYER_H
