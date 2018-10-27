#include "view_player.h"
#include "macros.h"
#include "iostream"


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

	// updates hpBar and manaBar
	sf::RectangleShape hpBar, manaBar;
	hpBar.setFillColor(sf::Color::Red);
	hpBar.setSize(sf::Vector2f(2.5f * 100, 30));
	manaBar.setFillColor(sf::Color::Green);
	manaBar.setSize(sf::Vector2f(2.5f * 100, 30));
	hpBar.setPosition(sf::Vector2f(x - WINDOW_WIDTH / 2.f + 10, y - WINDOW_HEIGHT / 2.f + 10));
	manaBar.setPosition(sf::Vector2f(x - WINDOW_WIDTH / 2.f + 10, y - WINDOW_HEIGHT / 2.f + 50));
	target.draw(hpBar, states);
	target.draw(manaBar, states);

	// update and draw text for health and mana, must be drawn after the corresponding bars
	sf::Text hpText, manaText;
	hpText.setFont(font);
	manaText.setFont(font);
	hpText.setFillColor(sf::Color::White);
	manaText.setFillColor(sf::Color::White);
	hpText.setString(root_node->first_node("health")->value());
	manaText.setString(root_node->first_node("mana")->value());
	hpText.setCharacterSize(20);
	manaText.setCharacterSize(20);
	hpText.setPosition(sf::Vector2f(x - WINDOW_WIDTH / 2.f + 135 - (hpText.getLocalBounds().width / 2.f), y - WINDOW_HEIGHT / 2.f + 15));
	manaText.setPosition(sf::Vector2f(x - WINDOW_WIDTH / 2.f + 135 - (manaText.getLocalBounds().width / 2.f), y - WINDOW_HEIGHT / 2.f + 55));
	target.draw(hpText, states);
	target.draw(manaText, states);



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
			if (state->get_level()->get_map()->get_cell(i, j).get_cell_type() == WALL)
			{
				rect.setFillColor(sf::Color(64, 64, 64));
			}
			else if (state->get_level()->get_map()->get_cell(i, j).get_cell_type() == FLOOR)
			{
				rect.setFillColor(sf::Color(128, 128, 128));
			}
			levelShapes.push_back(rect);
		}
	}
}

/*
	Actions to be performed when PlayerView is created: stores level, initializes xml text and UI
*/
void PlayerView::init()
{
	storeLevel();

	//load font 
	if (!font.loadFromFile("../data/Old-School-Adventures.ttf"))
		throw;

	// Read the xml file into a vector
	std::ifstream theFile("../data/game-text.xml");
	buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("UI");

}
