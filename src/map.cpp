#include <vector>
#include <iostream>
#include "map.h"
#include "macros.h"

#define IDX_BOUND_X   ((WINDOW_WIDTH / (2 * CELL_SIZE * ZOOM_SCALAR)))
#define IDX_BOUND_Y   ((WINDOW_HEIGHT / (2 * CELL_SIZE * ZOOM_SCALAR)))

Map::Map(std::vector<std::vector<char>> &grid)
{
  height = (int)grid.size();
  width = (int)grid[0].size();

  for (const auto &row : grid)
  {
    std::vector<Cell> temp;
    std::vector<int> cost_temp;
    for (const auto &ch : row)
    {
      if (ch == '-') temp.emplace_back(WALL), cost_temp.emplace_back(-1);
      else if (ch == '0' || ch == '1') temp.emplace_back(FLOOR), cost_temp.emplace_back(height*width);
	  else if (ch == 'E') temp.emplace_back(EXIT), cost_temp.emplace_back(-1);
	  else if (ch == 'o') temp.emplace_back(ORNAMENT), cost_temp.emplace_back(height*width);

    }
    cells.push_back(temp);
    init_cell_cost.emplace_back(cost_temp);
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
  updateCellCosts(pos);

  Vector2D int_vect = Vector2D(((int) pos.x / CELL_SIZE) * CELL_SIZE + CELL_SIZE/2, ((int) pos.y / CELL_SIZE) * CELL_SIZE + CELL_SIZE/2);
  if (std::find(path_nodes.begin(), path_nodes.end(), int_vect) != path_nodes.end())
  {
    player_recent_path_nodes.push(int_vect);
    if (player_recent_path_nodes.size() > recent_nodes_max) player_recent_path_nodes.pop();
  }
}

Cell& Map::get_cell_at(float x, float y)
{
  return cells[(int)y / CELL_SIZE][(int)x / CELL_SIZE];
}


void Map::updateCellCosts(const Vector2D &pos)
{
  int player_x = (int)pos.x / CELL_SIZE;
  int player_y = (int)pos.y / CELL_SIZE;

  std::vector<std::vector<bool>> closedList(height, std::vector<bool>(width, false));
  cell_cost = init_cell_cost;

  cell_cost[player_y][player_x] = 0;
  costRecursion(closedList, player_x, player_y, 0);
}


void Map::costRecursion(std::vector<std::vector<bool>> &closedList, int x, int y, int parent_cost)
{
  if (x < 1 || y < 1 || x >= width || y >= height || cell_cost[y][x] == -1)
      return;

  if (cell_cost[y][x+1] != -1)
      cell_cost[y][x+1] = (parent_cost + 1) < cell_cost[y][x+1] ? parent_cost + 1 :  cell_cost[y][x+1];

  if (cell_cost[y][x-1] != -1)
      cell_cost[y][x-1] = (parent_cost + 1) < cell_cost[y][x-1] ? parent_cost + 1 :  cell_cost[y][x-1];

  if (cell_cost[y+1][x] != -1)
      cell_cost[y+1][x] = (parent_cost + 1) < cell_cost[y+1][x] ? parent_cost + 1 :  cell_cost[y+1][x];

  if (cell_cost[y-1][x] != -1)
      cell_cost[y-1][x] = (parent_cost + 1) < cell_cost[y-1][x] ? parent_cost + 1 :  cell_cost[y-1][x];


  if (closedList[y][x])
      return;

  closedList[y][x] = true;

  //repeat for the 4 adjacent cells
  costRecursion(closedList, x + 1, y, cell_cost[y][x+1]);
  costRecursion(closedList, x - 1, y, cell_cost[y][x-1]);
  costRecursion(closedList, x, y + 1, cell_cost[y+1][x]);
  costRecursion(closedList, x, y - 1, cell_cost[y-1][x]);
}

void Map::updateVisited(Vector2D pos)
{
  // Calculate the index bounds, to update draw the cells within view of the player
  int bound_top   = std::max((int)(pos.y / CELL_SIZE - IDX_BOUND_Y), 0);
  int bound_bot   = std::min((int)(pos.y / CELL_SIZE + IDX_BOUND_Y), height - 1);
  int bound_left  = std::max((int)(pos.x / CELL_SIZE - IDX_BOUND_X), 0);
  int bound_right = std::min((int)(pos.x / CELL_SIZE + IDX_BOUND_X), width - 1);
  int i, j;
  for (i = bound_top; i < bound_bot; ++i)
  {
    for (j = bound_left; j < bound_right; ++j)
    {
      cells[i][j].visited = true;
    }
  }
}

