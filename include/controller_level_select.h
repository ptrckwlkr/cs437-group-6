#ifndef CSCI437_CONTROLLER_LEVELSELECT_H
#define CSCI437_CONTROLLER_LEVELSELECT_H

#include "controller.h"

class LevelSelectController : public Controller
{

public:
    LevelSelectController(GameLogic *state) : Controller(state) {};
    ~LevelSelectController() = default;
    void process_input(float delta, sf::Vector2f mouse_pos);
    void handle_event(sf::Event event);

private:


};


#endif //CSCI437_CONTROLLER_LEVELSELECT_H
