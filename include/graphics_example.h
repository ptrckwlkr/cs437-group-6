#ifndef CSCI437_VIEW_EXAMPLE_H
#define CSCI437_VIEW_EXAMPLE_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "game_logic.h"
#include "graphics.h"
#include "view.h"
#include "view_game.h"

class ExampleGraphics : public Graphics
{

public:
    explicit ExampleGraphics(GameView *view) : Graphics(), view(view) {}

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    GameView *view;

};

#endif //CSCI437_VIEW_EXAMPLE_H
