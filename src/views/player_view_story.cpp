#include "views/player_view_story.h"
#include "graphics/graphics_story.h"
#include "engine.h"

StoryView::StoryView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App) {
    selectionIndex = 0;
    graphics = std::make_shared<StoryGraphics>(this);
    App->setView(App->getDefaultView());
}

void StoryView::process_input(float delta) {


}

void StoryView::handle_event(sf::Event event) {
    if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Q)
        Engine::Instance().switch_mode(MODE_MENU);
    else if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::K)
        Engine::Instance().switch_mode(MODE_PLAY);
    else if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::E)
        Engine::Instance().switch_mode(MODE_LEVEL_SELECT);
    sf::Vector2f mouse_pos = (*app).mapPixelToCoords(sf::Mouse::getPosition(*app));
    if ((WINDOW_WIDTH / 6.f) < mouse_pos.x && mouse_pos.x < (5 * WINDOW_WIDTH / 6.f) &&
        (500 < mouse_pos.y && mouse_pos.y < 600)) {
        if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased) {
            Engine::Instance().switch_mode(MODE_LEVEL_SELECT);
        }
    }
}

void StoryView::update(float delta) {
    //Process input
    sf::Event event;
    while (app->pollEvent(event)) {
        handle_event(event);
        common_handle_event_tasks(event);
    }
    process_input(delta);
}

void StoryView::draw(float delta) {
    app->clear(sf::Color::Black);
    app->draw(*graphics);
    app->display();
}
