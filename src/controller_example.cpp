#include "controller_example.h"
#include <iostream>

void ExampleController::process_input(float delta)
{
  // TODO
  // NOTE: Presumably, the actual implementation will not directly manipulate individual entities' states, but rather
  // send messages to do so through the EventManager. But this works for demo purposes
  float x = state->get_level()->get_entities()[0]->get_position().x;
  float y = state->get_level()->get_entities()[0]->get_position().y;

  // Update position
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))     y -= 5;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))   y += 5;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))   x -= 5;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  x += 5;
  state->get_level()->get_entities()[0]->set_position(x, y);
}

void ExampleController::handle_event(sf::Event event)
{

}
