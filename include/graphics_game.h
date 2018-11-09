#ifndef CSCI437_GRAPHICS_GAME_H
#define CSCI437_GRAPHICS_GAME_H

#include <SFML/Graphics.hpp>
#include "game_logic.h"
#include "graphics.h"

class GameView;
class GameGraphics : public Graphics
{

public:
  explicit GameGraphics(GameView *view);
	GameView *view;

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void drawUI(sf::RenderTarget &target, sf::RenderStates states, float x, float y) const;
	void drawLevel(sf::RenderTarget &target, sf::RenderStates states) const;
	void storeLevel();

	std::vector<sf::RectangleShape> levelShapes;
	sf::Font font;

};


#endif //CSCI437_GRAPHICS_GAME_H
