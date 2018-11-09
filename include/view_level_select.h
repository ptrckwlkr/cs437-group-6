#ifndef CSCI437_CONTROLLER_LEVELSELECT_H
#define CSCI437_CONTROLLER_LEVELSELECT_H

#include "view.h"

class LevelSelectView : public PlayerView
{

public:
    LevelSelectView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App) {};
    ~LevelSelectView() = default;
    void update(float delta);
    void draw();

private:
    void process_input(float delta, sf::Vector2f mouse_pos);
    void handle_event(sf::Event event);
    Level getSelectedLevel();
    int selectionIndex;

};


#endif //CSCI437_CONTROLLER_LEVELSELECT_H
