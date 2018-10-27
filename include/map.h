#ifndef CSCI437_MAP_H
#define CSCI437_MAP_H

#include <vector>
#include <memory>
#include "cell.h"
#include "entity.h"

/**
 * Data structure to encapsulate the grid-based layout of an individual level. The grid is stored as a 2D array of
 * cells, and includes built-in functionality to sort the game entities into the cells (useful in collision detection)
 */
class Map
{

public:
    explicit Map(std::vector<std::vector<char>> &grid);
    std::vector<std::vector<Cell>>& get_cells() {return cells;}
    void update_entities(std::vector<std::shared_ptr<Entity>> &entities);
    void print_map();
    int get_height() {return height;}
    int get_width() {return width;}
    Cell& get_cell(int m, int n);

private:
    void clear_cells();
    std::vector<std::vector<Cell>> cells;
    int width;
    int height;

};

#endif //CSCI437_MAP_H
