#ifndef CSCI437_VIEW_EXAMPLE_H
#define CSCI437_VIEW_EXAMPLE_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "game_logic.h"
#include "view.h"

class ExampleView : public View
{

public:
    ExampleView(GameLogic *state) : View(state) {};

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //CSCI437_VIEW_EXAMPLE_H
