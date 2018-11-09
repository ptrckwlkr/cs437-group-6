#ifndef CSCI437_VIEW_H
#define CSCI437_VIEW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "game_logic.h"

/**
 * Abstract base class for all controllers.
 */
class View
{

public:
    explicit View(GameLogic *state) : state(state) {};
    virtual ~View() = default;
    virtual void update(float delta) = 0;
    GameLogic &get_state() {return *state;}
    GameLogic *state;

};

class Graphics;
class PlayerView : public View
{

public:
    explicit PlayerView(GameLogic *state, sf::RenderWindow *App) : View(state), app(App) {}
    virtual void draw() = 0;

protected:
    virtual void process_input(float delta) = 0;
    virtual void handle_event(sf::Event event) = 0;
    sf::RenderWindow *app;
    std::shared_ptr<Graphics> graphics;

};

#endif //CSCI437_VIEW_H
