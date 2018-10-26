#ifndef CSCI437_CELL_H
#define CSCI437_CELL_H

#include <vector>
#include <memory>
#include <set>
#include "entity.h"

/**
 * Represents a single cell of the game grid. Can specify type (Wall, Floor, etc) and also encapsulate a data structure
 * for game entities within the cell, which may be used for collision detection
 */
class Cell
{

public:
    Cell(char ch) : data(ch) {}
    void insert_entity(std::shared_ptr<Entity> &entity);
    void clear_entities();
    std::vector<std::shared_ptr<Entity>> get_entities();
    char get_data() {return data;}
    bool is_occupied() {return !entities.empty();}

private:
    std::set<std::shared_ptr<Entity>> entities;
    char data;

};

#endif //CSCI437_CELL_H
