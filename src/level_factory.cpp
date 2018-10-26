#include "level_factory.h"


std::shared_ptr<Level> LevelFactory::generate_level()
{
  std::shared_ptr<Level> level;
  std::shared_ptr<Map> map;

  switch (algorithm)
  {
    case LEVEL_FILE:
      map = load("../data/test.txt");
  }

  level = std::make_shared<Level>(map);
  return level;
}

std::shared_ptr<Map> LevelFactory::load(std::string filename)
{
  std::ifstream fin;
  fin.open(filename, std::ios::in);
  std::string linestr;

  std::vector<std::vector<char>> grid;
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
  return std::make_shared<Map>(grid);
}
