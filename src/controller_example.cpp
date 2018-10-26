#include "controller_example.h"
#include <iostream>

void ExampleController::process_input()
{
  float x = state->get_level()->get_entities()[0]->get_position().x;
  float y = state->get_level()->get_entities()[0]->get_position().y;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))     y -= 3;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))   y += 3;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))   x -= 3;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  x += 3;

  state->get_level()->get_entities()[0]->set_position(x, y);
}

void ExampleController::handle_event(sf::Event event)
{

}
