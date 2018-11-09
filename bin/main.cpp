#include <SFML/Graphics.hpp>
#include "engine.h"
#include "macros.h"

double g_time_elapsed;

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Tower", sf::Style::Titlebar | sf::Style::Close);
  App.setVerticalSyncEnabled(true);

  // Initialize the game engine
//  Engine engine(&App);
  Engine::GameEngine()->init(&App);

  // start main loop
  while (App.isOpen())
  {
    float delta = Engine::GameEngine()->clock();
    Engine::GameEngine()->update_views(delta);
    Engine::GameEngine()->update_state(delta);
    Engine::GameEngine()->update_graphics();
  }

  // Done.
  return 0;
}
