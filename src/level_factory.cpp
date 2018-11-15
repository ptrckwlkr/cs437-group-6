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

  EntityManager::Instance()->createEntity(TYPE_PLAYER,3150, 1000, 10 );
  EntityManager::Instance()->createEntity(TYPE_SKELETON,450, 250, 0);
  EntityManager::Instance()->createEntity(TYPE_GOLD,350, 250, 0);
  EntityManager::Instance()->createEntity(TYPE_PROJECTILE, 3155, 1010, 5);

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
     
		  map = std::make_shared<Map>(gen.createLevelGrid(15, 32.0));
		 // gen.printLevelGrid();
		  //player_>set_position(gen.player_x, gen.player_y);

      EntityManager::Instance()->getPlayer()->set_position(gen.player_x, gen.player_y);
      //maybe list is not the best way to store them, hard time to access them
      EntityManager::Instance()->getSkeletions().front()->set_position(gen.player_x + 10, gen.player_y+ 10);
      //enemy->set_position(gen.player_x + 10, gen.player_y+ 10 );
		  //enemy->set_position(3150, 800);
      EntityManager::Instance()->getGolds().front()->set_position(3050, 800 );
		  //gold->set_position(3050, 800);

    ///testing projectile shooting
      EntityManager::Instance()->getProjectiles().front()->set_position(gen.player_x+5, gen.player_y+5);
      EntityManager::Instance()->getProjectiles().front()->set_maxDamage(10);
      //projectile->set_position(gen.player_x+5, gen.player_y+5);
      //projectile->set_maxDamage(4);
      EntityManager::Instance()->getPlayer()->set_projectile(EntityManager::Instance()->getProjectiles().front());
      //player->set_projectile(projectile);
		  break;
  }

  // Create the actual level
  level = std::make_shared<Level>(map);

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
