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

}

void LevelSelectView::handle_event(sf::Event event)
{
	if (event.type == sf::Event::EventType::MouseButtonPressed) {
		int x = event.mouseButton.x;
		int y = event.mouseButton.y;
		printf("Click Event Processed\n");
		if (x >= 10 and x <= 275 and y >= 10 and y <= 275) {
			if (x >= 10 and x <= 50 and y >= 10 and y <= 50) {
				printf("Level One Selected\n");
			}
			if (x >= 55 and x <= 95 and y >= 55 and y <= 95) {
				printf("Level Two Selected\n");
			}
			if (x >= 100 and x <= 140 and y >= 100 and y <= 140) {
				printf("Level Three Selected\n");
			}
			if (x >= 145 and x <= 185 and y >= 145 and y <=185) {
				printf("Level Four Selected\n");
			}
			if (x >= 190 and x <= 230 and y >= 190 and y <= 230) {
				printf("Level Five Selected\n");
			}
			if (x >= 235 and x <=275 and y >= 235 and y <= 275) {
				printf("Level Six Selected\n");
			}
		}
		fflush(stdout);
	}
}

void LevelSelectView::update(float delta)
{

}

void LevelSelectView::draw()
{

}
