#include <EventManager.h>
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

  //listen for events
  //EventManager::Instance()->RegristerObject("PLAYER_SHOOT" ,this);


}

void PlayMode::update()
{
  level->update();

  //EventManager::Instance()->ProcessEvents();

}

// void PlayMode::HandleEvent( Event* event){
//   // if (event != nullptr){
//   //   if ( event->EventID() == PLAYER_SHOOT)}
//     //player shoots something 
//     //create the proper reactions
//   }
// }
