#include <mode_play.h>
#include "view_example.h"
#include "macros.h"

#define IDX_BOUND_X   ((WINDOW_WIDTH / (2 * CELL_SIZE * GRAPHICS_SCALER)) + 1)
#define IDX_BOUND_Y   ((WINDOW_HEIGHT / (2 * CELL_SIZE * GRAPHICS_SCALER)) + 1)

/**
 * This is a simple example of how the game state can be drawn to the screen
 */
void ExampleView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // This must always be the first line of every draw method
  states.transform *= getTransform();

  sf::RectangleShape rect(sf::Vector2f(CELL_SIZE * GRAPHICS_SCALER, CELL_SIZE * GRAPHICS_SCALER));
  CellType cell_type;

  auto mode = std::dynamic_pointer_cast<PlayMode>(state->get_mode());

  // Calculate the index bounds, to only draw the cells within view of the player
  int bound_top   = std::max((int)(mode->get_level()->get_entities()[0]->get_position().y / CELL_SIZE - IDX_BOUND_Y), 0);
  int bound_bot   = std::min((int)(mode->get_level()->get_entities()[0]->get_position().y / CELL_SIZE + IDX_BOUND_Y), mode->get_level()->get_map()->get_height() - 1);
  int bound_left  = std::max((int)(mode->get_level()->get_entities()[0]->get_position().x / CELL_SIZE - IDX_BOUND_X), 0);
  int bound_right = std::min((int)(mode->get_level()->get_entities()[0]->get_position().x / CELL_SIZE + IDX_BOUND_X), mode->get_level()->get_map()->get_width() - 1);

  // Draw the map
  int i, j;
  for (i = bound_top; i < bound_bot; ++i)
  {
    for (j = bound_left; j < bound_right; ++j)
    {
      Cell cell = mode->get_level()->get_map()->get_cell(i, j);
      cell_type = cell.get_cell_type();
      rect.setPosition(j * CELL_SIZE * GRAPHICS_SCALER, i * CELL_SIZE * GRAPHICS_SCALER);

      if (cell_type == WALL)
      {
        rect.setFillColor(sf::Color(64, 64, 64));
      }
      else if (cell_type == FLOOR)
      {
        // TODO Occupied cells are colored differently to demonstrate the functionality of the Map data structure
        if (cell.is_occupied())
        {
          rect.setFillColor(sf::Color(128, 128, 255));
        }
        else
        {
          rect.setFillColor(sf::Color(128, 128, 128));
        }
      }
      rect.setPosition(j * CELL_SIZE * GRAPHICS_SCALER, i * CELL_SIZE * GRAPHICS_SCALER);
      target.draw(rect, states);
    }
  }

  // TODO In reality, it should probably end up accessing entities through an EntityManager, rather than directly like this
  int x = (int)(GRAPHICS_SCALER * mode->get_level()->get_entities()[0]->get_position().x);
  int y = (int)(GRAPHICS_SCALER * mode->get_level()->get_entities()[0]->get_position().y);
  int s = (int)(GRAPHICS_SCALER * mode->get_level()->get_entities()[0]->get_size());

  // Draw the player entitiy to the screen
  sf::CircleShape circle(s);
  circle.setFillColor(sf::Color(0, 255, 0));
  circle.setOrigin(sf::Vector2f(s, s));
  circle.setPosition(x, y);
  target.draw(circle, states);

  // TODO Draw an enemy
  x = (int)(GRAPHICS_SCALER * mode->get_level()->get_entities()[1]->get_position().x);
  y = (int)(GRAPHICS_SCALER * mode->get_level()->get_entities()[1]->get_position().y);
  s = (int)(GRAPHICS_SCALER * mode->get_level()->get_entities()[1]->get_size());

  // Draw the player entity to the screen
  circle.setFillColor(sf::Color(255, 0, 0));
  circle.setOrigin(sf::Vector2f(s, s));
  circle.setPosition(x, y);
  target.draw(circle, states);


}
