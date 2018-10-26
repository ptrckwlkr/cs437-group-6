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
      sf::RectangleShape rect(sf::Vector2f(CELL_SIZE * GRAPHICS_SCALER, CELL_SIZE * GRAPHICS_SCALER));
      rect.setPosition(j * CELL_SIZE * GRAPHICS_SCALER, i * CELL_SIZE * GRAPHICS_SCALER);

      if (state->get_level()->get_map()->get_cells()[i][j].get_cell_type() == WALL)
      {
        rect.setFillColor(sf::Color(64, 64, 64));
      }
      else if (state->get_level()->get_map()->get_cells()[i][j].get_cell_type() == FLOOR)
      {
        if (state->get_level()->get_map()->get_cells()[i][j].is_occupied())
        {
          rect.setFillColor(sf::Color(255, 0, 0));
        }
        else
        {
          rect.setFillColor(sf::Color(128, 128, 128));
        }
      }
      target.draw(rect, states);
    }
  }

  int x = GRAPHICS_SCALER * (int)state->get_level()->get_entities()[0]->get_position().x;
  int y = GRAPHICS_SCALER * (int)state->get_level()->get_entities()[0]->get_position().y;
  int s = GRAPHICS_SCALER * (int)state->get_level()->get_entities()[0]->get_size();

  sf::CircleShape circle(s);
  circle.setFillColor(sf::Color(0, 255, 0));
  circle.setOrigin(sf::Vector2f(s, s));
  circle.setPosition(x, y);
  target.draw(circle, states);
}
