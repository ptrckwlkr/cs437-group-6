#ifndef CSCI437_CELL_H
#define CSCI437_CELL_H

#include <vector>
#include <memory>
#include <set>
#include "entity.h"

enum CellType
{
    WALL,
    FLOOR,
};

/**
 * Represents a single cell of the game grid. Can specify type (Wall, Floor, etc) and also encapsulate a data structure
 * for game entities within the cell, which may be used for collision detection
 */
class Cell
{

public:
    Cell(CellType cell_type) : cell_type(cell_type) {}
    void insert_entity(std::shared_ptr<Entity> &entity);
    void clear_entities();
    std::vector<std::shared_ptr<Entity>> get_entities();
    bool is_occupied() {return !entities.empty();}
    CellType get_cell_type() {return cell_type;}

private:
    std::set<std::shared_ptr<Entity>> entities;
    CellType cell_type;

};

#endif //CSCI437_CELL_H
