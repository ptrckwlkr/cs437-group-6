#include "graphics_level_select.h"
#include "player_view_level_select.h"

LevelSelectGraphics::LevelSelectGraphics(LevelSelectView *view) : Graphics(), view(view)
{

}

void LevelSelectGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

	// This must always be the first line of every draw method
	states.transform *= getTransform();

	sf::RectangleShape* levels[6];
	for (int i=0;i<6;i++) {
		levels[i] = new sf::RectangleShape;
		levels[i]->setFillColor(sf::Color::Red);
		levels[i]->setSize(sf::Vector2f(40,40));
		levels[i]->setPosition(sf::Vector2f((5*(i+2))+(40*i),(5*(i+2))+(40*i)));
		target.draw(*levels[i], states);
	}

}


