#include <graphics/graphics_next_level.h>
#include <engine.h>
#include "views/player_next_level.h"


NextLevelView::NextLevelView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App)
{
    graphics = std::make_shared<NextLevelGraphics>(this);
    App->setView(App->getDefaultView());
}

void NextLevelView::process_input(float delta)
{

}

void NextLevelView::handle_event(sf::Event event)
{

    if (event.type == sf::Event::Closed) Engine::Instance().shutdown();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) Engine::Instance().switch_mode(MODE_MENU);
    if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
    {
        Engine::Instance().switch_mode(MODE_LEVEL_SELECT);
    }
}

void NextLevelView::update(float delta)
{
    //Process input
    sf::Event event;
    while (app->pollEvent(event))
    {
        handle_event(event);
    }
    process_input(delta);
}

void NextLevelView::draw(float delta)
{
    app->clear(sf::Color::Black);
    app->draw(*graphics);
    app->display();
}