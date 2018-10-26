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
      temp.emplace_back(ch);
    }
    cells.push_back(temp);
  }
}

void Map::update_entities(std::vector<std::shared_ptr<Entity>> &entities)
{
  clear_cells();
  for (auto &ent : entities)
  {
    float x = ent->get_position().x;
    float y = ent->get_position().y;
    cells[y / CELL_SIZE][x / CELL_SIZE].insert_entity(ent);
  }
}

void Map::check_collisions()
{

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

void Map::print_map()
{
  for (auto &row : cells)
  {
    for (auto &cell : row)
    {
      std::cout << cell.get_data() << " ";
    }
    std::cout << std::endl;
  }
}