#ifndef CSCI437_GRAPHICS_LEVELSELECT_H
#define CSCI437_GRAPHICS_LEVELSELECT_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "graphics.h"
#include "player_view.h"

class LevelSelectView;
class LevelSelectGraphics : public Graphics
{

public:
    explicit LevelSelectGraphics(LevelSelectView *view);

private:
		LevelSelectView *view;

	  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	  std::vector<sf::Drawable> menuObjects;
	  sf::Font font;
};


#endif //CSCI437_GRAPHICS_LEVELSELECT_H
