#include "graphics/graphics_lost.h"
#include "views/player_view_lost.h"
#include "engine.h"

LostView::LostView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App) {
    graphics = std::make_shared<LostGraphics>(this);
    App->setView(App->getDefaultView());
}

void LostView::process_input(float delta) {


}

void LostView::handle_event(sf::Event event) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) Engine::Instance().switch_mode(MODE_MENU);

    else if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
        {
            printf( "play again pressed");
            Engine::Instance().switch_mode(MODE_LEVEL_SELECT);
        }
/*    else if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::V)
        Engine::Instance().switch_mode(MODE_PLAY); */
    else if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::E)
	Engine::Instance().switch_mode(MODE_LEVEL_SELECT);

}

void LostView::update(float delta) {
    //Process input
    sf::Event event;
    while (app->pollEvent(event)) {
        handle_event(event);
        common_handle_event_tasks(event);
    }
    process_input(delta);
}

void LostView::draw(float delta) {
    app->clear(sf::Color::Black);
    app->draw(*graphics);
    app->display();
}
