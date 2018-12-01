#include "level_factory.h"
#include "views/view_skeleton.h"
#include "alg_agent_based.h"
#include "views/view_manager.h"
#include "entities/gold.h"
#include "EntityManager.h"
#include "level.h"

/**
 * Returns a pointer to a newly created level, which is built according to the parameters specified through the setter
 * methods
 */
std::shared_ptr<Level> LevelFactory::generate_level()
{
  std::shared_ptr<Level> level;
  std::shared_ptr<Map> map;


  // TODO Can specify the map generation algorithm (load from file, randomly generated, etc)
  switch (algorithm)
  {
    case LEVEL_FILE:

      EntityManager::Instance()->getPlayer()->set_position(150, 150);
      //player->set_position(150, 150);

      map = load("../data/test2.txt");
	    break;
	case AGENT_BASED:

		AgentBasedGenerator gen = AgentBasedGenerator(64, 64, 1, 10, 0);
		map = std::make_shared<Map>(gen.createLevelGrid(15, 40, 64.0));
		map->givePathNodes(gen.getPathNodes());
		//gen.printLevelGrid();

    std::shared_ptr<Player> player = EntityManager::Instance()->createEntity<Player>(gen.player_x, gen.player_y);
    EntityManager::Instance()->set_player(player);
		//TEMP method to place enemies
		for (int i = 0; i < gen.enemy_coords.size(); i++)
		{
      auto ent = EntityManager::Instance()->createEntity<Skeleton>((float) gen.enemy_coords[i][0], (float) gen.enemy_coords[i][1]);
		}
    for (int i = 0; i < gen.treasure_coords.size(); i++)
    {
      auto ent = EntityManager::Instance()->createEntity<Gold>((float) gen.treasure_coords[i][0], (float) gen.treasure_coords[i][1]);
    }

		break;
  }

  // Create the actual level
  level = std::make_shared<Level>(map);
  level->set_player(EntityManager::Instance()->getPlayer().get());

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
