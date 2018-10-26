#include <vector>
#include <iostream>
#include "map.h"

Map::Map(std::vector<std::vector<char>> &grid)
{
  for (const auto &row : grid)
  {
    std::vector<Cell> temp;
    for (const auto &ch : row)
    {
      temp.push_back(Cell(ch));
    }
    cells.push_back(temp);
  }
}

void Map::insert_entities(std::vector<Entity> &entities)
{

}

void Map::check_collisions()
{

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
