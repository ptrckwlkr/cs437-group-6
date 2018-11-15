#include "skeleton.h"
#include "level_factory.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "Player.h"
#include "gold.h"
#include "Projectile.h"
#include "alg_agent_based.h"

/**
 * Returns a pointer to a newly created level, which is built according to the parameters specified through the setter
 * methods
 */
std::shared_ptr<Level> LevelFactory::generate_level()
{
  std::shared_ptr<Level> level;
  std::shared_ptr<Map> map;


  // TODO Generate all the level's entities
  // std::shared_ptr<Player> player = std::make_shared<Player>(3150, 1000, 10);
  // std::shared_ptr<Skeleton> enemy = std::make_shared<Skeleton>(450, 250);
  // std::shared_ptr<Gold> gold = std::make_shared<Gold>(350, 250);
  // std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(3155, 1010, 5);

  EntityManager::Instance()->createEntity(TYPE_PLAYER, 3150, 1000, 10 );
  EntityManager::Instance()->createEntity(TYPE_GOLD, 350, 250, 0);
  EntityManager::Instance()->createEntity(TYPE_PROJECTILE, 3155, 1010, 5);

  //NOTE THAT NUMBER OF ENEMIES HAS TO BE LARGER THAN THE NUMBER OF ROOMS!!!
  AgentBasedGenerator gen = AgentBasedGenerator(128, 106, 1, 10, 0);

  // TODO Can specify the map generation algorithm (load from file, randomly generated, etc)
  switch (algorithm)
  {
    case LEVEL_FILE:

      EntityManager::Instance()->getPlayer()->set_position(150, 150);
      //player->set_position(150, 150);

      map = load("../data/test2.txt");
	    break;
	  case AGENT_BASED:
		  map = std::make_shared<Map>(gen.createLevelGrid(15, 40, 32.0));
		 // gen.printLevelGrid();
		  //player_>set_position(gen.player_x, gen.player_y);

      EntityManager::Instance()->getPlayer()->set_position(gen.player_x, gen.player_y);
      //maybe list is not the best way to store them, hard time to access them

		  break;
  }

  // Create the actual level
  level = std::make_shared<Level>(map);

  //TEMP method to place enemies
  for (int i = 0; i < gen.enemy_coords.size(); i++)
  {
	  EntityManager::Instance()->createEntity(TYPE_SKELETON, gen.enemy_coords[i][0], gen.enemy_coords[i][1], 0);
  }

  //level->set_player(player);
  level->set_player(EntityManager::Instance()->getPlayer());
  
  // level->get_entities().push_back(player);
  // level->get_entities().push_back(enemy);
  // level->get_entities().push_back(gold);

  // level->get_entities().push_back(projectile);

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
