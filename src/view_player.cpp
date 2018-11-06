#include <mode_play.h>
#include "view_player.h"
#include "macros.h"


PlayerView::PlayerView(GameLogic *state) : View(state)
{
	storeLevel();

	// get all necessary resources from resource manager
	font = resources.GetFont("old_school");
	std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
	buffer = resources.GetXMLBuffer("text");
	root_node = (*doc).first_node("Root")->first_node("UI");
}

void PlayerView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// This must always be the first line of every draw method
	states.transform *= getTransform();

	drawLevel(target, states);

	auto mode = std::dynamic_pointer_cast<PlayMode>(state->get_mode());

	// TODO Draw an enemy
	float x = (GRAPHICS_SCALER * mode->get_level()->get_entities()[1]->get_position().x);
	float y = (GRAPHICS_SCALER * mode->get_level()->get_entities()[1]->get_position().y);
	float s = (GRAPHICS_SCALER * mode->get_level()->get_entities()[1]->get_size());

	// Draw enemy entity to the screen
	sf::CircleShape circle(s);
	circle.setFillColor(sf::Color(255, 0, 0));
	circle.setOrigin(sf::Vector2f(s, s));
	circle.setPosition(x, y);
	target.draw(circle, states);


	// TODO In reality, it should probably end up accessing entities through an EntityManager, rather than directly like this
	x = (GRAPHICS_SCALER * mode->get_level()->get_entities()[0]->get_position().x);
	y = (GRAPHICS_SCALER * mode->get_level()->get_entities()[0]->get_position().y);
	s = (GRAPHICS_SCALER * mode->get_level()->get_entities()[0]->get_size());

	// draw player entity to screen
	circle.setFillColor(sf::Color(0, 255, 0));
	circle.setOrigin(sf::Vector2f(s, s));
	circle.setPosition(x, y);
	target.draw(circle, states);

	drawUI(target, states, x, y);
	
}


void PlayerView::drawUI(sf::RenderTarget &target, sf::RenderStates states, float x, float y) const
{
	//TODO set size of bar to match player'sactual health/mana
	// updates hpBar
	sf::RectangleShape hpBar, manaBar;
	hpBar.setFillColor(sf::Color::Red);
	hpBar.setSize(sf::Vector2f(2.5f * 100, 30));
	hpBar.setPosition(sf::Vector2f(x - WINDOW_WIDTH / 2.f + 10, y - WINDOW_HEIGHT / 2.f + 10));
	target.draw(hpBar, states);
	//updates mana bar
	manaBar.setFillColor(sf::Color::Green);
	manaBar.setSize(sf::Vector2f(2.5f * 100, 30));
	manaBar.setPosition(sf::Vector2f(x - WINDOW_WIDTH / 2.f + 10, y - WINDOW_HEIGHT / 2.f + 50));
	target.draw(manaBar, states);

	// update and draw text for health and mana, must be drawn after the corresponding bars
	sf::Text hpText, manaText;
	hpText = prepareText("health");
	hpText.setFont(font);
	hpText.setPosition(sf::Vector2f(x - WINDOW_WIDTH / 2.f + 135 - (hpText.getLocalBounds().width / 2.f), y - WINDOW_HEIGHT / 2.f + 15));
	manaText = prepareText("mana");
	manaText.setFont(font);
	manaText.setPosition(sf::Vector2f(x - WINDOW_WIDTH / 2.f + 135 - (manaText.getLocalBounds().width / 2.f), y - WINDOW_HEIGHT / 2.f + 55));
	target.draw(hpText, states);
	target.draw(manaText, states);
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
	auto mode = std::dynamic_pointer_cast<PlayMode>(state->get_mode());
	for (i = 0; i < mode->get_level()->get_map()->get_height(); ++i)
	{
		for (j = 0; j < mode->get_level()->get_map()->get_width(); ++j)
		{
			sf::RectangleShape rect(sf::Vector2f(CELL_SIZE * GRAPHICS_SCALER, CELL_SIZE * GRAPHICS_SCALER));
			rect.setPosition(j * CELL_SIZE * GRAPHICS_SCALER, i * CELL_SIZE * GRAPHICS_SCALER);

			// Color the cells according to their type
			if (mode->get_level()->get_map()->get_cell(i, j).get_cell_type() == WALL)
			{
				rect.setFillColor(sf::Color(64, 64, 64));
			}
			else if (mode->get_level()->get_map()->get_cell(i, j).get_cell_type() == FLOOR)
			{
				rect.setFillColor(sf::Color(128, 128, 128));
			}
			levelShapes.push_back(rect);
		}
	}
}

