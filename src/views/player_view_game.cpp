#include "views/player_view_game.h"
#include "graphics/graphics_game.h"
#include "macros.h"
#include "engine.h"

GameView::GameView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App) {
    graphics = std::make_shared<GameGraphics>(this);
    player_text = resources.GetTexture("playerTexture");
    skeleton_text = resources.GetTexture("skeletonTexture");
    if (MUSIC) {
        bg_music = resources.GetMusic("vanquisher");
        bg_music->setVolume(35.0);
        bg_music->play();
    }
    animation_player.init(player_text, sf::Vector2u(13, 21), 3 / 60.f);
    animation_skeleton.init(skeleton_text, sf::Vector2u(13, 21), 3 / 60.f);
}

GameView::~GameView() {

}

void GameView::process_input(float delta) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        state->reset();
        Engine::getInstance().set_mode(MODE_MENU);
    }

    // TODO check that game has started (not in menu)


    int x_dir = 0, y_dir = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) y_dir++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) y_dir--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x_dir--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x_dir++;

    if (x_dir != 0 || y_dir != 0) {
        auto dir = VEC_NONE;
        if (x_dir == 1 && y_dir == 1) dir = VEC_NORTHEAST;
        else if (x_dir == 1 && y_dir == 0) dir = VEC_EAST;
        else if (x_dir == 1 && y_dir == -1) dir = VEC_SOUTHEAST;
        else if (x_dir == 0 && y_dir == 1) dir = VEC_NORTH;
        else if (x_dir == 0 && y_dir == -1) dir = VEC_SOUTH;
        else if (x_dir == -1 && y_dir == 1) dir = VEC_NORTHWEST;
        else if (x_dir == -1 && y_dir == 0) dir = VEC_WEST;
        else if (x_dir == -1 && y_dir == -1) dir = VEC_SOUTHWEST;

        // TODO The call to move should probably eventually be handled through the EventManager
        //only call move when necessary
        // if (dir != VEC_NONE)
        // {
        state->get_level().get_player().move(dir, delta);
        //animation_player.Update(dir, 9, delta);
        //}
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f mpos = (*app).mapPixelToCoords(sf::Mouse::getPosition(*app));
        Vector2D mouse_pos = Vector2D(mpos.x, mpos.y);
        Vector2D direction = mouse_pos - state->get_level().get_player().get_position();
        state->get_level().get_player().attack(direction, delta);
    }

}

void GameView::handle_event(sf::Event event) {
    if (event.type == sf::Event::Closed) Engine::getInstance().shutdown();
    else if (event.key.code == sf::Keyboard::M && event.type == sf::Event::KeyReleased) map_mode = !map_mode;
}

void GameView::update(float delta) {
    sf::Event event;
    while (app->pollEvent(event)) {
        handle_event(event);
    }

    // Process input
    process_input(delta);
}

void GameView::draw(float delta) {
    // initializes the camera
    graphics->update(delta);
    app->draw(*graphics);
    app->display();
}
