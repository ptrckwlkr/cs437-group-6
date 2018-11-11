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

}

void LevelSelectView::update(float delta)
{

}

void LevelSelectView::draw()
{

}
