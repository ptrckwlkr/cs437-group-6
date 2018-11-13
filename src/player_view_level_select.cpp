#include <engine.h>
#include "graphics_level_select.h"
#include "player_view_level_select.h"

LevelSelectView::LevelSelectView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App)
{
  selectionIndex = 0;
  graphics = std::make_shared<LevelSelectGraphics>(this);
  App->setView(App->getDefaultView());
}

void LevelSelectView::process_input(float delta)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) Engine::getInstance().set_mode(MODE_MENU);
}

void LevelSelectView::handle_event(sf::Event event)
{
	if (event.type == sf::Event::EventType::MouseButtonPressed) {
		int x = event.mouseButton.x;
		int y = event.mouseButton.y;
		printf("Click Event Processed\n");
		if (x >= 10 && x <= 275 && y >= 10 && y <= 275) {
			if (x >= 10 && x <= 50 && y >= 10 && y <= 50) {
				printf("Level One Selected\n");
        Engine::getInstance().set_mode(MODE_PLAY);
			}
			if (x >= 55 && x <= 95 && y >= 55 && y <= 95) {
				printf("Level Two Selected\n");
			}
			if (x >= 100 && x <= 140 && y >= 100 && y <= 140) {
				printf("Level Three Selected\n");
			}
			if (x >= 145 && x <= 185 && y >= 145 && y <=185) {
				printf("Level Four Selected\n");
			}
			if (x >= 190 && x <= 230 && y >= 190 && y <= 230) {
				printf("Level Five Selected\n");
			}
			if (x >= 235 && x <=275 && y >= 235 && y <= 275) {
				printf("Level Six Selected\n");
			}
		}
		fflush(stdout);
	}
}

void LevelSelectView::update(float delta)
{
  // Process input
  sf::Event event;
  while (app->pollEvent(event))
  {
    handle_event(event);
  }
  process_input(delta);
}

void LevelSelectView::draw()
{
  app->clear(sf::Color::Black);
  app->draw(*graphics);
  app->display();
}
