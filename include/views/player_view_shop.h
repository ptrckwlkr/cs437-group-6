#ifndef CSCI437_PLAYER_VIEW_SHOP_H
#define CSCI437_PLAYER_VIEW_SHOP_H


#include <memory>
#include "GameShop.h"
#include "macros.h"
#include "player_view.h"
#include "Equipment.h"
#include "GearSet.h"


class ShopView : public PlayerView
{

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    struct SelectBox
    {
        int x;
        int y;
        int width;
        int height;
    };
    struct ItemBox
    {
        SelectBox box;
        GameShop::Entry *entry;
    };
    int clickedBox(int x, int y);
    std::vector<GameShop::Entry> *items;

    void controlsScreen1(int clicked);
    void controlsScreen2(int clicked);
    void controlsScreen3(int clicked);
    void updateItems();

    std::shared_ptr<std::vector<char>> buffer;
    rapidxml::xml_node<> *root_node;

public:
    ShopView(GameLogic *state, sf::RenderWindow *App);
    void update(float delta) override;
    void draw(float delta) override;

    SelectBox selectionBoxes[30];
    ItemBox itemBoxes[8];
    int screenIndex;
    int slideIndex;
    GameShop::Entry *viewing;

};



#endif //CSCI437_PLAYER_VIEW_SHOP_H
