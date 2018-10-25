#include "view_player.h"
#include "macros.h"

void PlayerView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// This must always be the first line of every draw method
	states.transform *= getTransform();

	target.draw(shape, states);
}


void PlayerView::init()
{
	//player is temporarily respresented as a green circle
	shape.setRadius(20);
	shape.setFillColor(sf::Color(0, 255, 0));
	shape.setOrigin(sf::Vector2f(20, 20));
	shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}