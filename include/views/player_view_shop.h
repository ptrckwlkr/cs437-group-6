#ifndef CSCI437_PLAYER_VIEW_SHOP_H
#define CSCI437_PLAYER_VIEW_SHOP_H


#include "macros.h"
#include "player_view.h"
#include "Equipment.h"
#include "GearSet.h"
#include <memory>


class ShopView : public PlayerView
{

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    int selectionIndex;	//represents current highlighted option on screen
    void generateShopItems();
    std::shared_ptr<Equipment> shopItems[5];

    std::shared_ptr<std::vector<char>> buffer;
    rapidxml::xml_node<> *root_node;

public:
    ShopView(GameLogic *state, sf::RenderWindow *App);
    void update(float delta) override;
    void draw(float delta) override;

};



#endif //CSCI437_PLAYER_VIEW_SHOP_H
