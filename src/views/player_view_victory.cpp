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
    sf::Vector2f mouse_pos = (*app).mapPixelToCoords(sf::Mouse::getPosition(*app));



}

void VictoryView::handle_event(sf::Event event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) Engine::getInstance().set_mode(MODE_MENU);

    sf::Vector2f mouse_pos = (*app).mapPixelToCoords(sf::Mouse::getPosition(*app));
    if (event.type == sf::Event::EventType::MouseButtonPressed)
    {
        if (340 < mouse_pos.x  && mouse_pos.x <= 451)
        {
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
