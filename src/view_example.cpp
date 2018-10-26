#include "view_example.h"
#include "macros.h"

void ExampleView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // This must always be the first line of every draw method
  states.transform *= getTransform();

  int i, j;
  for (i = 0; i < state->get_level()->get_map()->get_height(); ++i)
  {
    for (j = 0; j < state->get_level()->get_map()->get_width(); ++j)
    {
      sf::RectangleShape rect(sf::Vector2f(100, 100));
      rect.setPosition(j * 100, i * 100);

      if (state->get_level()->get_map()->get_cells()[i][j].get_data() == '-')
      {
        rect.setFillColor(sf::Color(128, 128, 128));
      }
      else if (state->get_level()->get_map()->get_cells()[i][j].get_data() == '0')
      {
        rect.setFillColor(sf::Color(255, 255, 255));
      }
      target.draw(rect, states);
    }
  }

  // Note that the View class has the Game State as an attribute, so it can query the game objects

  sf::CircleShape circle(20);
  circle.setFillColor(sf::Color(255, 0, 0));
  circle.setOrigin(sf::Vector2f(20, 20));
  circle.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  target.draw(circle, states);
}
