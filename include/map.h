#ifndef CSCI437_MAP_H
#define CSCI437_MAP_H

#include <vector>
#include <memory>
#include "cell.h"
#include "entity.h"

class Map
{

public:
    explicit Map(std::vector<std::vector<char>> &grid);
    std::vector<std::vector<Cell>> get_cells() {return cells;}
    void update_entities(std::vector<std::shared_ptr<Entity>> &entities);
    void check_collisions();
    void print_map();
    int get_height() {return height;}
    int get_width() {return width;}

private:
    void clear_cells();
    std::vector<std::vector<Cell>> cells;
    int width;
    int height;

};

#endif //CSCI437_MAP_H
