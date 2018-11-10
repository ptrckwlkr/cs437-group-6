#include "player_view_game.h"
#include "graphics_game.h"
#include "macros.h"
#include "engine.h"
#include "Player.h"

GameView::GameView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App)
{
  graphics = std::make_shared<GameGraphics>(this);
}

void GameView::process_input(float delta)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) Engine::getInstance().set_mode(MODE_MENU);

	// TODO check that game has started (not in menu)
	Direction dir = NONE;

	int x_dir = 0, y_dir = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	y_dir++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	y_dir--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	x_dir--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	x_dir++;

	if (x_dir == 1 && y_dir == 1)			dir = NORTHEAST;
	else if (x_dir == 1 && y_dir == 0)		dir = EAST;
	else if (x_dir == 1 && y_dir == -1)		dir = SOUTHEAST;
	else if (x_dir == 0 && y_dir == 1)		dir = NORTH;
	else if (x_dir == 0 && y_dir == -1)		dir = SOUTH;
	else if (x_dir == -1 && y_dir == 1)		dir = NORTHWEST;
	else if (x_dir == -1 && y_dir == 0)		dir = WEST;
	else if (x_dir == -1 && y_dir == -1)	dir = SOUTHWEST;

	// TODO The call to move should probably eventually be handled through the EventManager
	//only call move when necessary
	if (dir != NONE)
	{
		auto player = std::static_pointer_cast<Player>(state->get_level().get_entities()[0]);
		player->move(dir, delta);
	}
		
}

void GameView::handle_event(sf::Event event)
{
  if (event.type == sf::Event::Closed) app->close();
}

void GameView::update(float delta)
{
  sf::Event event;
  while (app->pollEvent(event))
  {
    handle_event(event);
  }

  // Process input
  process_input(delta);
}

void GameView::draw()
{
  // initializes the camera
  // TODO send some of this to the constructor?
  sf::View camera;
  camera.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
  Position playerPos = state->get_level().get_entities()[0]->get_position();
  camera.setCenter(playerPos.x, playerPos.y);

  app->setView(camera);
  app->clear(sf::Color::Black);
  app->draw(*graphics);
  app->display();
}
