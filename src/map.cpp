#include <vector>
#include <iostream>
#include "map.h"

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
      else if (ch == '0' || ch == '1') temp.emplace_back(FLOOR);

    }
    cells.push_back(temp);
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
