#include "graphics/graphics_level_select.h"
#include "views/player_view_level_select.h"

LevelSelectGraphics::LevelSelectGraphics(LevelSelectView *view) : Graphics(), view(view)
{

}

void LevelSelectGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

	// This must always be the first line of every draw method
	states.transform *= getTransform();
    camera_reset(target);

  sf::Sprite sprite;
  sprite.setTexture(resources.GetTexture("map"));
  target.draw(sprite, states);

	for (int i = 0; i < NUMBER_OF_LEVELS; ++i) {
		//sf::CircleShape shape;
		sf::Sprite marker;
		marker.setTexture(resources.GetTexture("marker"));
    //shape.setFillColor(sf::Color::Red);
        //marker.setRadius(view->get_node(i).size);
        marker.setOrigin(view->get_node(i).size, view->get_node(i).size);
        marker.setPosition(view->get_node(i).x, view->get_node(i).y);
		target.draw(marker, states);
	}
}


