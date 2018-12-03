#include "views/player_view_victory.h"
#include "graphics/graphics_victory.h"
#include "engine.h"

VictoryView::VictoryView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App)
{
    selectionIndex = 0;
    graphics = std::make_shared<VictoryGraphics>(this);
    App->setView(App->getDefaultView());
}

void VictoryView::process_input(float delta)
{


}

void VictoryView::handle_event(sf::Event event)
{
    if (event.type == sf::Event::Closed) Engine::getInstance().shutdown();

    else if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Q) Engine::getInstance().set_mode(MODE_MENU);
    else if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::V) Engine::getInstance().set_mode(MODE_PLAY);
    sf::Vector2f mouse_pos = (*app).mapPixelToCoords(sf::Mouse::getPosition(*app));
    if (340 < mouse_pos.x  && mouse_pos.x <= 451)
    {
        if (event.type == sf::Event::EventType::MouseButtonPressed && sf::Event::EventType::MouseButtonReleased)
        {
            state->reset();
            Engine::getInstance().set_mode(MODE_MENU);
            printf( "play again pressed");
        }
    }
}

void VictoryView::update(float delta)
{
    //Process input
    sf::Event event;
    while (app->pollEvent(event))
    {
        handle_event(event);
    }
    process_input(delta);
}

void VictoryView::draw(float delta)
{
    app->clear(sf::Color::Black);
    app->draw(*graphics);
    app->display();
}
