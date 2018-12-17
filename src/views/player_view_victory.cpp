#include "views/player_view_victory.h"
#include "graphics/graphics_victory.h"
#include "engine.h"

VictoryView::VictoryView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App)
{
    graphics = std::make_shared<VictoryGraphics>(this);
    App->setView(App->getDefaultView());
}

void VictoryView::process_input(float delta)
{

}

void VictoryView::handle_event(sf::Event event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) Engine::Instance().switch_mode(MODE_MENU);
    else if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Q) Engine::Instance().switch_mode(MODE_MENU);
    sf::Vector2f mouse_pos = (*app).mapPixelToCoords(sf::Mouse::getPosition(*app));

    if (event.type == sf::Event::EventType::MouseButtonPressed && sf::Event::EventType::MouseButtonReleased)
    {
      Engine::Instance().switch_mode(MODE_MENU);
    }
}

void VictoryView::update(float delta)
{
    //Process input
    sf::Event event;
    while (app->pollEvent(event))
    {
        handle_event(event);
        common_handle_event_tasks(event);
    }
    process_input(delta);
}

void VictoryView::draw(float delta)
{
    app->clear(sf::Color::Black);
    app->draw(*graphics);
    app->display();
}
