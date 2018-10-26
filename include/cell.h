#ifndef CSCI437_CELL_H
#define CSCI437_CELL_H

#include <vector>
#include "entity.h"

class Cell
{

public:
    Cell(char ch) : data(ch) {}
    void insert_entity(Entity &entity);
    void check_collisions();
    char get_data() {return data;}

private:
    std::vector<Entity> entities;
    char data;

};

#endif //CSCI437_CELL_H
