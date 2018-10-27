#include "level_factory.h"

/**
 * Returns a pointer to a newly created level, which is built according to the parameters specified through the setter
 * methods
 */
std::shared_ptr<Level> LevelFactory::generate_level()
{
  std::shared_ptr<Level> level;
  std::shared_ptr<Map> map;
  std::vector<std::shared_ptr<Entity>> entities;

  // TODO Generate all the level's entities
  entities.push_back(std::make_shared<Entity>(150, 100, 10));
  entities.push_back(std::make_shared<Entity>(450, 250, 10));

  // TODO Can specify the map generation algorithm (load from file, randomly generated, etc)
  switch (algorithm)
  {
    case LEVEL_FILE:
      map = load("../data/test.txt");
  }

  // Create the actual level
  level = std::make_shared<Level>(map, entities);

  return level;
}

std::shared_ptr<Map> LevelFactory::load(std::string filename)
{
  std::ifstream fin;
  std::string linestr;
  std::vector<std::vector<char>> grid;
  std::vector<char> temp;
  fin.open(filename, std::ios::in);

  while (std::getline(fin, linestr))
  {
    for (auto c : linestr)
    {
      temp.push_back(c);
    }
    grid.push_back(temp);
    temp.clear();
  }

  fin.close();
  return std::make_shared<Map>(grid);
}
