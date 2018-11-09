#include "controller_example.h"
#include <iostream>
#include <mode_play.h>

void ExampleController::process_input(float delta, sf::Vector2f mouse_pos)
{
  Direction dir;

  //looks at keyboard state and updates coordinates appropriately
  bool W_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
  bool S_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
  bool A_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
  bool D_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

  // This is super complicated (sorry) and can probably be greatly simplified
  if (W_pressed && A_pressed && S_pressed && D_pressed) // Don't do anything if all the keys are pressed
  {
    dir = NONE;
  }
  else if (A_pressed && D_pressed) // A and D cancel each other out
  {
    if (W_pressed) dir = NORTH;
    else if (S_pressed) dir = SOUTH;
    else dir = NONE;
  }
  else if (W_pressed && S_pressed) // W and S cancel each other out
  {
    if (A_pressed) dir = WEST;
    else if (D_pressed) dir = EAST;
    else dir = NONE;
  }
  else // For everything else, just figure out what direction we should be going
  {
    if (W_pressed && D_pressed) dir = NORTHEAST;
    else if (D_pressed && S_pressed) dir = SOUTHEAST;
    else if (S_pressed && A_pressed) dir = SOUTHWEST;
    else if (A_pressed && W_pressed) dir = NORTHWEST;
    else if (W_pressed) dir = NORTH;
    else if (D_pressed) dir = EAST;
    else if (S_pressed) dir = SOUTH;
    else if (A_pressed) dir = WEST;
    else dir = NONE;
  }

  auto mode = std::dynamic_pointer_cast<PlayMode>(state->get_mode());
  mode->get_level()->get_entities()[0]->move(dir, delta);
}

void ExampleController::handle_event(sf::Event event)
{

}
