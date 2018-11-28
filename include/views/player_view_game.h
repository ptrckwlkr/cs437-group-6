#ifndef CSCI437_VIEW_GAME_H
#define CSCI437_VIEW_GAME_H

#include "view.h"
#include "player_view.h"

/**
* Controller class for Stu Dent
*/
class GameView : public PlayerView
{

public:
    GameView(GameLogic *state, sf::RenderWindow *App);
    void update(float delta) override;
    void draw() override;

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;

};

#endif //CSCI437_VIEW_GAME_H
