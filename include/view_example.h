#ifndef CSCI437_VIEW_EXAMPLE_H
#define CSCI437_VIEW_EXAMPLE_H

#include "view.h"

class ExampleView : public PlayerView
{

public:
    explicit ExampleView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App) {};
    void update(float delta) override;

protected:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    void draw() override;

private:


};


#endif //CSCI437_VIEW_EXAMPLE_H
