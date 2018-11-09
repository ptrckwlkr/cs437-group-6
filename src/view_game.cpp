#include <macros.h>
#include <engine.h>
#include "graphics_game.h"
#include "view_game.h"
#include "Player.h"

GameView::GameView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App)
{
  graphics = new GameGraphics(this);
}

void GameView::process_input(float delta)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) Engine::GameEngine()->set_mode(MODE_MENU);

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
		auto player = std::static_pointer_cast<Player>(state->get_level()->get_entities()[0]);
		player->move(dir, delta);
	}
		
}

void GameView::handle_event(sf::Event event)
{
  if (event.type == sf::Event::Closed) App->close();
}

void GameView::update(float delta)
{
  sf::Event event;
  while (App->pollEvent(event))
  {
    handle_event(event);
  }

  // Process input
  process_input(delta);

  // Listen for shutdown signal
  if (state->shutdown()) App->close();
}

void GameView::draw()
{
  // initializes the camera
  // TODO send some of this to the constructor?
  sf::View camera;
  camera.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
  Position playerPos = state->get_level()->get_entities()[0]->get_position();
  camera.setCenter(playerPos.x, playerPos.y);

  App->setView(camera);
  App->clear(sf::Color::Black);
  App->draw(*graphics);
  App->display();
}
