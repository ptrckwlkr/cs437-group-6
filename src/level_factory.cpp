#include "skeleton.h"
#include "level_factory.h"
#include "EventManager.h"
#include "Player.h"
#include "gold.h"
#include "alg_agent_based.h"

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

  std::shared_ptr<Player> player = std::make_shared<Player>(3150, 1000, 10);
  std::shared_ptr<Skeleton> enemy = std::make_shared<Skeleton>(450, 250);
  std::shared_ptr<Gold> gold = std::make_shared<Gold>(350, 250);

  entities.push_back(player);
  entities.push_back(enemy);
  entities.push_back(gold);

  AgentBasedGenerator gen = AgentBasedGenerator(128, 106, 1, 10, 0);

  // TODO Can specify the map generation algorithm (load from file, randomly generated, etc)
  switch (algorithm)
  {
    case LEVEL_FILE:
      player->set_position(150, 150);
      map = load("../data/test2.txt");
	    break;
	  case AGENT_BASED:
      player->set_position(3150, 900);
      enemy->set_position(3150, 800);
      gold->set_position(3050, 800);
		  map = std::make_shared<Map>(gen.createLevelGrid());
		  //gen.printLevelGrid();
		  break;
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
