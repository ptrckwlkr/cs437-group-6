#include "level_file.h"
#include <iostream>
#include <fstream>

LevelFile::LevelFile() : Level()
{
  load("test.txt");
  for (int i = 0; i < height; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      char ch = grid[i][j];
      std::cout << ch;
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
  width = (int)grid[0].size();
  height = (int)grid.size();
  fin.close();
}
