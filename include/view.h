#ifndef CSCI437_VIEW_H
#define CSCI437_VIEW_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include "game_logic.h"

/**
 * Base class for all the graphical views.
 */
class View : public sf::Drawable, public sf::Transformable
{

public:
    explicit View(GameLogic *state) : state(state) {};

protected:
    GameLogic *state;
};

#endif //CSCI437_VIEW_H
