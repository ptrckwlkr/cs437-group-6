#ifndef CSCI437_VIEW_INVENTORY_H
#define CSCI437_VIEW_INVENTORY_H

#include "macros.h"
#include "player_view.h"

class InventoryView : public PlayerView
{

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;

public:
    InventoryView(GameLogic *state, sf::RenderWindow *App);
    void update(float delta) override;
    void draw(float delta) override;

};


#endif //CSCI437_VIEW_INVENTORY_H
