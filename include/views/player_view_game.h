#ifndef CSCI437_VIEW_GAME_H
#define CSCI437_VIEW_GAME_H

#include <memory>
#include "player_view.h"

/**
* Controller class for Stu Dent
*/
class GameView : public PlayerView
{

public:
    GameView(GameLogic *state, sf::RenderWindow *App);
    ~GameView();
    void update(float delta) override;
    void draw(float delta) override;
    bool getMapMode() {return map_mode;}

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    bool map_mode = false;

};

#endif //CSCI437_VIEW_GAME_H
