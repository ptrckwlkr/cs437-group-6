#include "EventManager.h"
#include "level_factory.h"
#include "Player.h"
#include "gold.h"

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

  std::shared_ptr<Player> player = std::make_shared<Player>(150, 100, 10);
  std::shared_ptr<Player> enemy = std::make_shared<Player>(450, 250, 10);
  std::shared_ptr<Gold> gold = std::make_shared<Gold>(350, 250);

  EventManager::Instance()->RegisterObject(COLLISION_EVENT, player.get());


  entities.push_back(player);
  entities.push_back(enemy);
  entities.push_back(gold);

  // TODO Can specify the map generation algorithm (load from file, randomly generated, etc)
  switch (algorithm)
  {
    case LEVEL_FILE:
      map = load("../data/test2.txt");
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
