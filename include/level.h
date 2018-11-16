#ifndef CSCI437_LEVEL_H
#define CSCI437_LEVEL_H

#include <utility>
#include <vector>
#include <memory>
#include "map.h"
#include "collision_engine.h"
#include "Player.h"
#include "Projectile.h"
#include "EntityManager.h"

class Level
{

public:
    Level(std::shared_ptr<Map> &map);
    void update();
    void set_player(std::shared_ptr<Player> p) {player = p;}

    //void set_player(Player &p){player =p;}


    Map &get_map() {return *map;}
    std::shared_ptr<Player>  &get_player() {return player;}

protected:
    std::shared_ptr<Map> map;
    std::shared_ptr<Player> player;


};


#endif //CSCI437_LEVEL_H
