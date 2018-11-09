#ifndef CSCI437_VIEW_EXAMPLE_H
#define CSCI437_VIEW_EXAMPLE_H

#include "view.h"

class ExampleView : public PlayerView
{

public:
    explicit ExampleView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App) {};
    ~ExampleView() = default;
    void update(float delta);

protected:
    void process_input(float delta);
    void handle_event(sf::Event event);
    void draw();

private:


};


#endif //CSCI437_VIEW_EXAMPLE_H
