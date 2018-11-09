#ifndef CSCI437_VIEW_LEVELSELECT_H
#define CSCI437_VIEW_LEVELSELECT_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "game_logic.h"
#include "graphics.h"
#include "../rapidxml/rapidxml.hpp"
#include "fstream"
#include "view.h"
#include "view_level_select.h"


class LevelSelectGraphics : public Graphics
{

public:
    explicit LevelSelectGraphics(LevelSelectView *view) : Graphics(), view(view) {};
	  LevelSelectView *view;

private:
	  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	  std::vector<sf::Drawable> menuObjects;
	  sf::Font font;
};


#endif //CSCI437_VIEW_MENU_H
