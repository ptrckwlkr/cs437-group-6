#ifndef CSCI437_PLAYER_VIEW_SHOP_H
#define CSCI437_PLAYER_VIEW_SHOP_H


#include "macros.h"
#include "player_view.h"

class ShopView : public PlayerView
{

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    int selectionIndex;	//represents current highlighted option on screen

public:
    ShopView(GameLogic *state, sf::RenderWindow *App);
    void update(float delta) override;
    void draw(float delta) override;

};



#endif //CSCI437_PLAYER_VIEW_SHOP_H
