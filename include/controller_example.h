#ifndef CSCI437_CONTROLLER_EXAMPLE_H
#define CSCI437_CONTROLLER_EXAMPLE_H

#include "controller.h"

class ExampleController : public Controller
{

public:
    ExampleController(GameLogic *state) : Controller(state) {};
    ~ExampleController() = default;
    void process_input(float delta, sf::Vector2f mouse_pos);
    void handle_event(sf::Event event);

private:


};


#endif //CSCI437_CONTROLLER_EXAMPLE_H
