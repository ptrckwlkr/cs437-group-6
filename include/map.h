#ifndef CSCI437_MAP_H
#define CSCI437_MAP_H

#include <vector>
#include <queue>
#include <memory>
#include "cell.h"

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
    Cell& get_cell_at(float x, float y);
    void givePathNodes(std::vector<Vector2D> &path_nodes) {this->path_nodes = path_nodes;}
    void updatePlayerRecentCells(const Vector2D &pos);

    template<typename T, typename Container=std::deque<T> >
    class iterable_queue : public std::queue<T,Container>
    {
    public:
        typedef typename Container::iterator iterator;
        typedef typename Container::const_iterator const_iterator;

        iterator begin() { return this->c.begin(); }
        iterator end() { return this->c.end(); }
        const_iterator begin() const { return this->c.begin(); }
        const_iterator end() const { return this->c.end(); }
    };

    iterable_queue<Vector2D> &getRecentNodes() {return player_recent_path_nodes;}
    iterable_queue<Vector2D> &getRecentCells() {return player_recent_cells;}

private:
    CellMap cells;
    int width;
    int height;

    std::vector<Vector2D> path_nodes;

    //used to help smarter enemies chase/shoot the player
    iterable_queue<Vector2D> player_recent_path_nodes;
    iterable_queue<Vector2D> player_recent_cells;

    //maximum size of above data structures
    const int recent_cells_max = 20;
    const int recent_nodes_max = 5;

};

#endif //CSCI437_MAP_H
