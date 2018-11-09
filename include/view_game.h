#ifndef CSCI437_PLAYER_CONTROLLER_H
#define CSCI437_PLAYER_CONTROLLER_H

#include "graphics_game.h"
#include "view.h"

/**
* Controller class for Stu Dent
*/
class GameView : public PlayerView
{

public:
    explicit GameView(GameLogic *state, sf::RenderWindow *App);
    ~GameView() = default;
    void update(float delta) override;
    void draw() override;

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    GameGraphics *graphics;

};

#endif //CSCI437_PLAYER_CONTROLLER_H
