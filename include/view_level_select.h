#ifndef CSCI437_VIEW_LEVELSELECT_H
#define CSCI437_VIEW_LEVELSELECT_H

#include "view.h"

class LevelSelectView : public PlayerView
{

public:
    LevelSelectView(GameLogic *state, sf::RenderWindow *App);
    void update(float delta) override;
    void draw() override;

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    int getSelectedLevel() {};
    int selectionIndex;

};


#endif //CSCI437_VIEW_LEVELSELECT_H
