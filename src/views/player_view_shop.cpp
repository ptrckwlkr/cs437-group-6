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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        Engine::Instance().switch_mode(MODE_MENU);
    }

}

void ShopView::handle_event(sf::Event event)
{
    sf::Vector2f mouse_pos = (*app).mapPixelToCoords(sf::Mouse::getPosition(*app));

    if (event.type == sf::Event::Closed) Engine::Instance().shutdown();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) Engine::Instance().switch_mode(MODE_MENU);
    else if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::S) Engine::Instance().switch_mode(MODE_LEVEL_SELECT);
    if (480 < mouse_pos.x  && mouse_pos.x <= 620 )
    {
        if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
        {
            if ( 380 < mouse_pos.y && mouse_pos.y < 400) {
                printf("mana pressed");
                get_state().get_player_data().add_mana();
                std::cout << get_state().get_player_data().get_mana();
            }

            if ( 418 < mouse_pos.y && mouse_pos.y < 450) {
                printf("health pressed");
                get_state().get_player_data().add_health();
                std::cout << get_state().get_player_data().get_health();
            }

            if ( 460 < mouse_pos.y && mouse_pos.y < 500) {
                printf("exit pressed");
                Engine::Instance().switch_mode(MODE_LEVEL_SELECT);
            }
        }
    }
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
