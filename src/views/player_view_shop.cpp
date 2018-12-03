#include "engine.h"
#include "graphics/graphics_shop.h"
#include "views/player_view_shop.h"

ShopView::ShopView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App)
{
    selectionIndex = 0;
    graphics = std::make_shared<ShopGraphics>(this);
    App->setView(App->getDefaultView());
}

void ShopView::process_input(float delta)
{
    //sf::Vector2f mouse_pos = (*app).mapPixelToCoords(sf::Mouse::getPosition(*app));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        state->reset();
        Engine::getInstance().set_mode(MODE_MENU);
    }

}

void ShopView::handle_event(sf::Event event)
{
    sf::Vector2f mouse_pos = (*app).mapPixelToCoords(sf::Mouse::getPosition(*app));

    if (event.type == sf::Event::Closed) Engine::getInstance().shutdown();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) Engine::getInstance().set_mode(MODE_MENU);

    else if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::F) Engine::getInstance().set_mode(MODE_PLAY);
//    if (event.type == sf::Event::EventType::MouseButtonPressed)
//    {
//        if (340 < mouse_pos.x  && mouse_pos.x <= 451)
//        {
//            Engine::getInstance().set_mode(MODE_MENU);
//            printf( "play again pressed");
//        }

}

void ShopView::update(float delta)
{
    //Process input
    sf::Event event;
    while (app->pollEvent(event))
    {
        handle_event(event);
    }
    process_input(delta);
}

void ShopView::draw(float delta)
{
    app->clear(sf::Color::Black);
    app->draw(*graphics);
    app->display();
}
