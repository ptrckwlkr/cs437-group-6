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
  Engine engine(&App);

  // start main loop
  while (App.isOpen())
  {
    engine.clock();
    engine.process_input();
    engine.update_state();
    engine.update_views();
  }

  // Done.
  return 0;
}
