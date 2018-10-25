#include <iostream>
#include <fstream>
#include <vector>
#include "floor.h"

Floor::Floor(unsigned int seed)
{
  srand(seed);

  for (int i = 0; i < GRID_HEIGHT; ++i)
  {
    for (int j = 0; j < GRID_WIDTH; ++j)
    {
      grid[i][j] = '-';
    }
  }

  generate_rooms();
}

void Floor::print_room()
{
  std::ofstream fout;
  fout.open("room.txt", std::ios::out);
  for (int i = 0; i < GRID_HEIGHT; ++i)
  {
    for (int j = 0; j < GRID_WIDTH; ++j)
    {
      fout << grid[i][j];
    }
    fout << std::endl;
  };
  fout.close();
}
