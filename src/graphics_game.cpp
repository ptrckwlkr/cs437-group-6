#include "graphics_game.h"
#include "player_view_game.h"
#include "macros.h"

#define IDX_BOUND_X   ((WINDOW_WIDTH / (2 * CELL_SIZE)) + 1)
#define IDX_BOUND_Y   ((WINDOW_HEIGHT / (2 * CELL_SIZE)) + 1)

GameGraphics::GameGraphics(GameView *view) : Graphics(), view(view)
{
	storeLevel();

	// get all necessary resources from resource manager
	font = resources.GetFont("old_school");
	std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
	buffer = resources.GetXMLBuffer("text");
	root_node = (*doc).first_node("Root")->first_node("UI");
}

void GameGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// This must always be the first line of every draw method
	states.transform *= getTransform();

	drawLevel(target, states);

	// TODO Draw an enemy
	// float x = (view->get_state().get_level().get_entities()[1]->get_position().x);
	// float y = (view->get_state().get_level().get_entities()[1]->get_position().y);
	// float s = (view->get_state().get_level().get_entities()[1]->get_size());

	//EntityManager could eventually take a number of entities you can to create
	//then this would iterate through the list and place each in right place
	float x = EntityManager::Instance()->getEntity(TYPE_SKELETON)->get_position().x;
	float y = EntityManager::Instance()->getEntity(TYPE_SKELETON)->get_position().y;
	float s = EntityManager::Instance()->getEntity(TYPE_SKELETON)->get_size();

	// Draw enemy entity to the screen
	sf::CircleShape circle(s);
	circle.setFillColor(sf::Color(255, 0, 0));
	circle.setOrigin(sf::Vector2f(s, s));
	circle.setPosition(x, y);
	target.draw(circle, states);


	// x = (view->get_state().get_level().get_entities()[2]->get_position().x);
	// y = (view->get_state().get_level().get_entities()[2]->get_position().y);
	// s = (view->get_state().get_level().get_entities()[2]->get_size());

	float x2 = EntityManager::Instance()->getEntity(TYPE_PLAYER)->get_position().x;
	float y2 = EntityManager::Instance()->getEntity(TYPE_PLAYER)->get_position().y;
	float s2 = EntityManager::Instance()->getEntity(TYPE_PLAYER)->get_size();

	// draw player entity to screen
	circle.setFillColor(sf::Color(255, 255, 0));
	circle.setOrigin(sf::Vector2f(s2, s2));
	circle.setPosition(x2, y2);
	target.draw(circle, states);


	// TODO In reality, it should probably end up accessing entities through an EntityManager, rather than directly like this
	// x = (view->get_state().get_level().get_entities()[0]->get_position().x);
	// y = (view->get_state().get_level().get_entities()[0]->get_position().y);
	// s = (view->get_state().get_level().get_entities()[0]->get_size());

	float x1 = EntityManager::Instance()->getEntity(TYPE_GOLD)->get_position().x;
	float y1 = EntityManager::Instance()->getEntity(TYPE_GOLD)->get_position().y;
	float s1 =EntityManager::Instance()->getEntity(TYPE_GOLD)->get_size();

	// draw player entity to screen
	circle.setFillColor(sf::Color(0, 255, 0));
	circle.setOrigin(sf::Vector2f(s1, s1));
	circle.setPosition(x1, y1);
	target.draw(circle, states);

	float x3 = EntityManager::Instance()->getEntity(TYPE_PROJECTILE)->get_position().x;
	float y3 = EntityManager::Instance()->getEntity(TYPE_PROJECTILE)->get_position().x;
	float s3 = EntityManager::Instance()->getEntity(TYPE_PROJECTILE)->get_position().x;

	// draw projectile  to screen
	circle.setFillColor(sf::Color(230, 255, 0));
	circle.setOrigin(sf::Vector2f(s3, s3));
	circle.setPosition(x3, y3);
	target.draw(circle, states);

	drawUI(target, states, x, y);
	
}


void GameGraphics::drawUI(sf::RenderTarget &target, sf::RenderStates states, float x, float y) const
{
	//TODO set size of bar to match player'sactual health/mana
	// updates hpBar
	sf::RectangleShape hpBar, manaBar;
	hpBar.setFillColor(sf::Color(255, 0, 0, 190));
	hpBar.setSize(sf::Vector2f(2.5f * 100, 30));
	hpBar.setPosition(sf::Vector2f(x - WINDOW_WIDTH / 2.f + 10, y - WINDOW_HEIGHT / 2.f + 10));
	target.draw(hpBar, states);
	//updates mana bar
	manaBar.setFillColor(sf::Color(0,255,0,190));
	manaBar.setSize(sf::Vector2f(2.5f * 100, 30));
	manaBar.setPosition(sf::Vector2f(x - WINDOW_WIDTH / 2.f + 10, y - WINDOW_HEIGHT / 2.f + 50));
	target.draw(manaBar, states);

	// update and draw text for health and mana, must be drawn after the corresponding bars
	sf::Text hpText, manaText;
	hpText = prepareText("health", font);
	//note that y position of text is relative to bar size but x position is fixed so that bar can change width without moving text
	hpText.setPosition(x - WINDOW_WIDTH / 2.f + 135,  hpBar.getPosition().y + hpBar.getLocalBounds().height / 2.f);
	manaText = prepareText("mana", font);
	manaText.setPosition(x - WINDOW_WIDTH / 2.f + 135, manaBar.getPosition().y + manaBar.getLocalBounds().height / 2.f);
	target.draw(hpText, states);
	target.draw(manaText, states);
}

/*
	Helper function to draw the background to the screen, called before entities are drawn
*//*
void GameGraphics::drawLevel(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (unsigned i = 0; i < levelShapes.size(); i++)
	{
		target.draw(levelShapes.at(i), states);
	}
}*/

void GameGraphics::drawLevel(sf::RenderTarget &target, sf::RenderStates states) const
{
  // This must always be the first line of every draw method
  states.transform *= getTransform();

  sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  CellType cell_type;

  // Calculate the index bounds, to only draw the cells within view of the player
  int bound_top   = std::max((int)(view->get_state().get_level().get_player()->get_position().y / CELL_SIZE - IDX_BOUND_Y), 0);
  int bound_bot   = std::min((int)(view->get_state().get_level().get_player()->get_position().y / CELL_SIZE + IDX_BOUND_Y), view->get_state().get_level().get_map().get_height() - 1);
  int bound_left  = std::max((int)(view->get_state().get_level().get_player()->get_position().x / CELL_SIZE - IDX_BOUND_X), 0);
  int bound_right = std::min((int)(view->get_state().get_level().get_player()->get_position().x / CELL_SIZE + IDX_BOUND_X), view->get_state().get_level().get_map().get_width() - 1);

  // Draw the map
  int i, j;
  for (i = bound_top; i < bound_bot; ++i)
  {
    for (j = bound_left; j < bound_right; ++j)
    {
      Cell cell = view->get_state().get_level().get_map().get_cell(i, j);
      cell_type = cell.get_cell_type();
      rect.setPosition(j * CELL_SIZE, i * CELL_SIZE);

      if (cell_type == WALL)
      {
        rect.setFillColor(sf::Color(64, 64, 64));
      }
      else if (cell_type == FLOOR)
      {
        rect.setFillColor(sf::Color(128, 128, 128));
        // if (cell.is_occupied()) rect.setFillColor(sf::Color(128, 128, 255)); // TODO just for fun
      }
      rect.setPosition(j * CELL_SIZE, i * CELL_SIZE);
      target.draw(rect, states);
    }
  }
}


/*
	Stores all rectangle shapes for the level in a vector so that they can be quickly drawn later
*/
void GameGraphics::storeLevel()
{
	// Draw every cell onto the screen
	int i, j;
	for (i = 0; i < view->get_state().get_level().get_map().get_height(); ++i)
	{
		for (j = 0; j < view->get_state().get_level().get_map().get_width(); ++j)
		{
			sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			rect.setPosition(j * CELL_SIZE, i * CELL_SIZE);

			// Color the cells according to their type
			if (view->get_state().get_level().get_map().get_cell(i, j).get_cell_type() == WALL)
			{
				rect.setFillColor(sf::Color(64, 64, 64));
			}
			else if (view->get_state().get_level().get_map().get_cell(i, j).get_cell_type() == FLOOR)
			{
				rect.setFillColor(sf::Color(128, 128, 128));
			}
			levelShapes.push_back(rect);
		}
	}
}

