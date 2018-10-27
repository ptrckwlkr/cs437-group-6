#include <vector>
#include <iostream>
#include "map.h"
#include "macros.h"

Map::Map(std::vector<std::vector<char>> &grid)
{
  height = (int)grid.size();
  width = (int)grid[0].size();

  for (const auto &row : grid)
  {
    std::vector<Cell> temp;
    for (const auto &ch : row)
    {
      if (ch == '-') temp.emplace_back(WALL);
      else if (ch == '0') temp.emplace_back(FLOOR);
    }
    cells.push_back(temp);
  }
}

/**
 * Sort a list of pointers to game entities into the map's cells, according to the entities' positions
 */
void Map::update_entities(std::vector<std::shared_ptr<Entity>> &entities)
{
  // TODO will probably ultimately accept the EntityManager& as a parameter, instead of a raw vector of pointers
  Position pos{};
  float radius;
  float top;
  float bot;
  float left;
  float right;

  // Sort every entity into one or more of the game grid's cells
  clear_cells();
  for (auto &ent : entities)
  {
    pos     = ent->get_position();
    radius  = ent->get_size() / 2;
    top     = pos.y - radius - COLLISION_BUFFER;
    bot     = pos.y + radius + COLLISION_BUFFER;
    left    = pos.x - radius - COLLISION_BUFFER;
    right   = pos.x + radius + COLLISION_BUFFER;

    // Consider the 4 "corners" of the entity, and insert into every cell that contains a corner
    cells[top / CELL_SIZE][left / CELL_SIZE].insert_entity(ent);
    cells[(int)(top / CELL_SIZE)][(int)(right / CELL_SIZE)].insert_entity(ent);
    cells[bot / CELL_SIZE][left / CELL_SIZE].insert_entity(ent);
    cells[bot / CELL_SIZE][right / CELL_SIZE].insert_entity(ent);
  }
}

/**
 * Clear every cell of its registered entities
 */
void Map::clear_cells()
{
  for (auto &row : cells)
  {
    for (auto &cell : row)
    {
      cell.clear_entities();
    }
  }
}

/**
 * Print the map to the console, useful for debugging
 */
void Map::print_map()
{
  for (auto &row : cells)
  {
    for (auto &cell : row)
    {
      if (cell.get_cell_type() == WALL) std::cout << "-";
      else if (cell.get_cell_type() == FLOOR) std::cout << "0";
      std::cout << " ";
    }
    std::cout << std::endl;
  }
}

Cell& Map::get_cell(int m, int n)
{
  return cells[m][n];
}
