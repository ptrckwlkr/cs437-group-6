#include "game_logic.h"
#include "engine.h"
#include "views/view_manager.h"
#include "sprite_manager.h"
#include "EntityManager.h"

GameLogic::GameLogic() : Listener()
{
  level_factory = LevelFactory();
  player_data = PlayerData();
  collision_engine = CollisionEngine();
  f_paused = false;

  EventManager::Instance().registerListener(EventExitReached::eventType, this, &GameLogic::handleExitReached);
}

GameLogic::~GameLogic()
{
  EventManager::Instance().unregisterAll(this);
}

/**
 * Update the game state
 */
void GameLogic::update_state(float delta)
{
  EventManager::Instance().processEvents(); // Pre-collision event processing
  if (f_new_game)
  {
    f_new_game = false;
    reset();

    create_new_level(AGENT_BASED, current_level);
    Engine::Instance().switch_mode(MODE_PLAY);
  }
  else
  {
    collision_engine.hash_entities(level->get_map(), EntityManager::Instance().getEntites());
    level->update();
    collision_engine.check_collisions(level->get_map());
  }
  EventManager::Instance().processEvents(); // Post-collision event processing
}

/**
 * Start a new level.
 */
void GameLogic::create_new_level(Generator g, int level_num)
{
  level_factory.set_algorithm(g, level_num);
  level = level_factory.generate_level();
  current_level = level_num;
}

void GameLogic::reset()
{
  collision_engine.reset();
  SpriteManager::Instance().reset();
  ViewManager::Instance().reset();
  EntityManager::Instance().reset();
  EventManager::Instance().reset();
}

void GameLogic::handleExitReached(const EventExitReached &event)
{
  f_new_game = true;
}
