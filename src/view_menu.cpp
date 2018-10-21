#include "view_example.h"
#include "macros.h"

void ExampleView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // This must always be the first line of every draw method
  states.transform *= getTransform();

  // Note that the View class has the Game State as an attribute, so it can query the game objects

  sf::CircleShape circle(20);
  circle.setFillColor(sf::Color(0, 255, 0));
  circle.setOrigin(sf::Vector2f(20, 20));
  circle.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  target.draw(circle, states);
}
