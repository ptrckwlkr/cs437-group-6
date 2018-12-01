#include <SFML/Graphics.hpp>
#include "engine.h"
#include "macros.h"

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Tower", sf::Style::Titlebar | sf::Style::Close);
  App.setVerticalSyncEnabled(true);

  // Initialize the game engine
//  Engine engine(&App);
  Engine::getInstance().init(&App);

  // start main loop
  while (App.isOpen())
  {
    float delta = Engine::getInstance().clock();
//    if (delta > 0.5)
//      delta = 0.0336380005;

    Engine::getInstance().update_views(delta);
    Engine::getInstance().update_state(delta);
    Engine::getInstance().update_graphics(delta);
  }

  // Done.
  return 0;
}
