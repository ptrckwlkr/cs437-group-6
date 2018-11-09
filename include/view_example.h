#ifndef CSCI437_CONTROLLER_EXAMPLE_H
#define CSCI437_CONTROLLER_EXAMPLE_H

#include "view.h"

class ExampleView : public PlayerView
{

public:
    explicit ExampleView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App) {};
    ~ExampleView() = default;
    void update(float delta);

protected:
    void process_input(float delta, sf::Vector2f mouse_pos);
    void handle_event(sf::Event event);
    void draw();

private:


};


#endif //CSCI437_CONTROLLER_EXAMPLE_H
