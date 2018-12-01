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
	  else if (ch == 'E') temp.emplace_back(EXIT);
	  else if (ch == 'o') temp.emplace_back(ORNAMENT);

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
	  else if (cell.get_cell_type() == EXIT) std::cout << "E";
      std::cout << " ";
    }
    std::cout << std::endl;
  }
}

Cell& Map::get_cell(int m, int n)
{
  return cells[m][n];
}


void Map::updatePlayerRecentCells(const Vector2D &pos)
{
  player_recent_cells.push(pos);
  if (player_recent_cells.size() > recent_cells_max) player_recent_cells.pop();

  Vector2D non_const = pos;
  if (std::find(path_nodes.begin(), path_nodes.end(), non_const) != path_nodes.end())
  {
    player_recent_path_nodes.push(pos);
    if (player_recent_path_nodes.size() > recent_nodes_max) player_recent_path_nodes.pop();
  }
}
