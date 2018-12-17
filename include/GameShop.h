#ifndef CSCI437_GAMESHOP_H
#define CSCI437_GAMESHOP_H

#include <vector>
#include <memory>
#include "Equipment.h"

class GameShop
{

public:
    struct Entry {
        int price;
        bool purchased;
        std::shared_ptr<Equipment> item;
    };
    GameShop();
    std::vector<Entry> &get_items() {return items;}

private:
    std::vector<Entry> items;

};


#endif //CSCI437_GAMESHOP_H
