#ifndef CSCI437_CELL_H
#define CSCI437_CELL_H

#include <vector>
#include "entity.h"

class Cell
{

public:
    Cell() = default;;
    void insert_entity(Entity &entity);
    void check_collisions();

private:
    std::vector<Entity> entities;

};

#endif //CSCI437_CELL_H
