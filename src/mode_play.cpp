#include "mode_play.h"

PlayMode::PlayMode()
{
  // TODO initialize other level building data
  level_factory = new LevelFactory();
  level_factory->set_algorithm(LEVEL_FILE);
  level = level_factory->generate_level();
}

PlayMode::~PlayMode()
{
  delete level_factory;
}

void PlayMode::update()
{
  level->update();
}
