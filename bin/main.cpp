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
  Engine::Instance().init(&App);

  // start main loop
  while (App.isOpen())
  {
    float delta = Engine::Instance().clock();
//    if (delta > 0.5)
//      delta = 0.0336380005;

    Engine::Instance().update_views(delta);
    Engine::Instance().update_state(delta);
    Engine::Instance().update_graphics(delta);
  }

  // Done.
  return 0;
}
