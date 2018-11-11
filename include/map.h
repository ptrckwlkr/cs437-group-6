#ifndef CSCI437_MAP_H
#define CSCI437_MAP_H

#include <vector>
#include <memory>
#include "cell.h"
#include "entity.h"

typedef std::vector<std::vector<Cell>> CellMap;

/**
 * Data structure to encapsulate the grid-based layout of an individual level. The grid is stored as a 2D array of
 * cells, and includes built-in functionality to sort the game entities into the cells (useful in collision detection)
 */
class Map
{

public:
    explicit Map(std::vector<std::vector<char>> &grid);
    CellMap &get_cells() {return cells;}
    void print_map();
    int get_height() {return height;}
    int get_width() {return width;}
    Cell& get_cell(int m, int n);

private:
    CellMap cells;
    int width;
    int height;

};

#endif //CSCI437_MAP_H
