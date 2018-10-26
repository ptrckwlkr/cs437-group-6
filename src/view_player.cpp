#include "view_player.h"
#include "macros.h"

void PlayerView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// This must always be the first line of every draw method
	states.transform *= getTransform();

	drawLevel(target, states);

	// TODO In reality, it should probably end up accessing entities through an EntityManager, rather than directly like this
	float x = (GRAPHICS_SCALER * state->get_level()->get_entities()[0]->get_position().x);
	float y = (GRAPHICS_SCALER * state->get_level()->get_entities()[0]->get_position().y);
	float s = (GRAPHICS_SCALER * state->get_level()->get_entities()[0]->get_size());

	// draw player entity to screen
	sf::CircleShape circle(s);
	circle.setFillColor(sf::Color(0, 255, 0));
	circle.setOrigin(sf::Vector2f(s, s));
	circle.setPosition(x, y);
	target.draw(circle, states);

	// TODO Draw an enemy
	x = (int)(GRAPHICS_SCALER * state->get_level()->get_entities()[1]->get_position().x);
	y = (int)(GRAPHICS_SCALER * state->get_level()->get_entities()[1]->get_position().y);
	s = (int)(GRAPHICS_SCALER * state->get_level()->get_entities()[1]->get_size());

	// Draw the player entitiy to the screen
	circle.setFillColor(sf::Color(255, 0, 0));
	circle.setOrigin(sf::Vector2f(s, s));
	circle.setPosition(x, y);
	target.draw(circle, states);
}


/*
	Helper function to draw the background to the screen, called before entities are drawn
*/
void PlayerView::drawLevel(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (unsigned i = 0; i < levelShapes.size(); i++)
	{
		target.draw(levelShapes.at(i), states);
	}
}


/*
	Stores all rectangle shapes for the level in a vector so that they can be quickly drawn later
*/
void PlayerView::storeLevel()
{
	// Draw every cell onto the screen
	int i, j;
	for (i = 0; i < state->get_level()->get_map()->get_height(); ++i)
	{
		for (j = 0; j < state->get_level()->get_map()->get_width(); ++j)
		{
			sf::RectangleShape rect(sf::Vector2f(CELL_SIZE * GRAPHICS_SCALER, CELL_SIZE * GRAPHICS_SCALER));
			rect.setPosition(j * CELL_SIZE * GRAPHICS_SCALER, i * CELL_SIZE * GRAPHICS_SCALER);

			// Color the cells according to their type
			if (state->get_level()->get_map()->get_cells()[i][j].get_cell_type() == WALL)
			{
				rect.setFillColor(sf::Color(64, 64, 64));
			}
			else if (state->get_level()->get_map()->get_cells()[i][j].get_cell_type() == FLOOR)
			{
				// TODO Occupied cells are colored differently to demonstrate the functionality of the Map data structure
				if (state->get_level()->get_map()->get_cells()[i][j].is_occupied())
				{
					rect.setFillColor(sf::Color(128, 128, 255));
				}
				else
				{
					rect.setFillColor(sf::Color(128, 128, 128));
				}
			}
			levelShapes.push_back(rect);
		}
	}
}

/*
	Actions to be performed when PlayerView is created: stores level, initializes sf::View
*/
void PlayerView::init()
{
	storeLevel();
}