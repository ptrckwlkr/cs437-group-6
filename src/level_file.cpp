#include "level_file.h"
#include <iostream>
#include <fstream>

LevelFile::LevelFile() : Level()
{
  load("../data/test.txt");
  map = std::make_shared<Map>((int)grid[0].size(), (int)grid.size(), grid);
  for (int i = 0; i < map->get_height(); ++i)
  {
    for (int j = 0; j < map->get_width(); ++j)
    {
      std::cout << grid[i][j];
    }
    std::cout << std::endl;
  };
}

char *LevelFile::load(std::string filename)
{
  std::ifstream fin;
  fin.open(filename, std::ios::in);
  std::string linestr;

  std::vector<char> temp;

  char c;
  while (fin.get(c))
  {
    if (c == '\n')
    {
      grid.push_back(temp);
      temp.clear();
    }
    else
    {
      temp.push_back(c);
    }
  }

  fin.close();
}
