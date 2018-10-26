#ifndef CSCI437_LEVEL_H
#define CSCI437_LEVEL_H

#include <utility>
#include <vector>
#include <memory>
#include "map.h"

class Level
{

public:
    Level(std::shared_ptr<Map> map) : map(std::move(map)) {};
    std::shared_ptr<Map> get_map() {return map;}
    std::vector<std::shared_ptr<Entity>> get_entities() {entities;}

protected:
    std::shared_ptr<Map> map;
    std::vector<std::shared_ptr<Entity>> entities;

};


#endif //CSCI437_LEVEL_H
