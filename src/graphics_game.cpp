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
	tileTexture = resources.GetTexture("tileset");
}

void GameGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// This must always be the first line of every draw method
	states.transform *= getTransform();

	drawLevel(target, states);

	float x;
	float y;
	float size;
	EntityType type;
	for (auto &ent : EntityManager::Instance()->getEntites())
	{
		x = ent->get_position().x;
		y = ent->get_position().y;
		size = ent->get_size();
		type = ent->get_type();

		sf::CircleShape circle(size);

		if (type == TYPE_SKELETON) circle.setFillColor(sf::Color(255, 0, 0));
		if (type == TYPE_PLAYER) circle.setFillColor(sf::Color(0, 255, 0));
		if (type == TYPE_GOLD) circle.setFillColor(sf::Color(255, 255, 0));
		if (type == TYPE_PROJECTILE) circle.setFillColor(sf::Color(255, 255, 255));

		circle.setOrigin(sf::Vector2f(size, size));
		circle.setPosition(x, y);
		target.draw(circle, states);
	}

  x = EntityManager::Instance()->getPlayer()->get_position().x;
  y = EntityManager::Instance()->getPlayer()->get_position().y;
	drawUI(target, states, x, y);
}


void GameGraphics::drawUI(sf::RenderTarget &target, sf::RenderStates states, float x, float y) const
{

  sf::Sprite sprite;
  sprite.setTexture(resources.GetTexture("fog"));
  sprite.setPosition(sf::Vector2f(x - WINDOW_WIDTH / 2.f, y - WINDOW_HEIGHT / 2.f));
  //target.draw(sprite, states); // Uncomment me to see a nice effect

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

void GameGraphics::drawLevel(sf::RenderTarget &target, sf::RenderStates states) const
{
  // This must always be the first line of every draw method
  states.transform *= getTransform();
  states.texture = &tileTexture;

  target.draw(vertices, states);

//  sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
//  CellType cell_type;
//
//  // Calculate the index bounds, to only draw the cells within view of the player
//  int bound_top   = std::max((int)(view->get_state().get_level().get_player()->get_position().y / CELL_SIZE - IDX_BOUND_Y), 0);
//  int bound_bot   = std::min((int)(view->get_state().get_level().get_player()->get_position().y / CELL_SIZE + IDX_BOUND_Y), view->get_state().get_level().get_map().get_height() - 1);
//  int bound_left  = std::max((int)(view->get_state().get_level().get_player()->get_position().x / CELL_SIZE - IDX_BOUND_X), 0);
//  int bound_right = std::min((int)(view->get_state().get_level().get_player()->get_position().x / CELL_SIZE + IDX_BOUND_X), view->get_state().get_level().get_map().get_width() - 1);
//
//  // Draw the map
//  int i, j;
//  for (i = bound_top; i < bound_bot; ++i)
//  {
//    for (j = bound_left; j < bound_right; ++j)
//    {
//      Cell cell = view->get_state().get_level().get_map().get_cell(i, j);
//      cell_type = cell.get_cell_type();
//      rect.setPosition(j * CELL_SIZE, i * CELL_SIZE);
//
//      if (cell_type == WALL)
//      {
//        rect.setFillColor(sf::Color(64, 64, 64));
//      }
//      else if (cell_type == FLOOR)
//      {
//        rect.setFillColor(sf::Color(128, 128, 128));
//         // if (cell.is_occupied()) rect.setFillColor(sf::Color(128, 128, 255)); // TODO just for fun
//      }
//			else if (cell_type == EXIT)
//			{
//				rect.setFillColor(sf::Color(255, 230, 0));
//			}
//      rect.setPosition(j * CELL_SIZE, i * CELL_SIZE);
//      target.draw(rect, states);
//    }
//  }
}


/*
	Stores all rectangle shapes for the level in a vector so that they can be quickly drawn later
*/
void GameGraphics::storeLevel()
{
    tile_map.SetTexture();
    tile_map.PopulateVertexArray(view->get_state().get_level().get_map(), 0);
	vertices = tile_map.GetVertices();

//	// Draw every cell onto the screen
//	int i, j;
//	for (i = 0; i < view->get_state().get_level().get_map().get_height(); ++i)
//	{
//		for (j = 0; j < view->get_state().get_level().get_map().get_width(); ++j)
//		{
//			sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
//			rect.setPosition(j * CELL_SIZE, i * CELL_SIZE);
//
//			// Color the cells according to their type
//			if (view->get_state().get_level().get_map().get_cell(i, j).get_cell_type() == WALL)
//			{
//				rect.setFillColor(sf::Color(64, 64, 64));
//			}
//			else if (view->get_state().get_level().get_map().get_cell(i, j).get_cell_type() == FLOOR)
//			{
//				rect.setFillColor(sf::Color(128, 128, 128));
//			}
//			levelShapes.push_back(rect);
//		}
//	}
}

