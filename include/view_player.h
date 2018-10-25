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

	sf::Vector2f get_coords() {return shape.getPosition();}
	void set_coords(float x, float y) {shape.setPosition(x, y);}

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void init();

	sf::CircleShape shape;
};

#endif //CSCI437_VIEW_EXAMPLE_H
