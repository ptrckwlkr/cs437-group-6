#ifndef CSCI437_LEVEL_H
#define CSCI437_LEVEL_H

#include <utility>
#include <vector>
#include <memory>
#include "map.h"
#include "entities/Player.h"
#include "macros.h"

class Level
{

public:
    Level(std::shared_ptr<Map> &map);
    void update();
    void set_player(Player *p);
    Map &get_map() {return *map;}
    Player &get_player() {return *player;}

protected:
    std::shared_ptr<Map> map;
    Player *player;

    int player_prev_x;
    int player_prev_y;

};


#endif //CSCI437_LEVEL_H
