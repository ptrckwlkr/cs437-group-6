#ifndef CSCI437_PLAYER_VIEW_H
#define CSCI437_PLAYER_VIEW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include "view.h"
#include "Animations/Animation.h"
#include "engine.h"

#define ASPECT_RATIO 1.25f

/**
 * Abstract base class for all the player views, to include functionality for SFML input, graphics, and audio.
 */
class Graphics;
class PlayerView : public View
{

public:
    PlayerView(GameLogic *state, sf::RenderWindow *App) : View(state), app(App){}
    virtual void draw(float delta) = 0;

protected:
    virtual void process_input(float delta) = 0;
    virtual void handle_event(sf::Event event) = 0;

    sf::RenderWindow *app;
    std::shared_ptr<Graphics> graphics;


    void common_handle_event_tasks(sf::Event &event)
    {
        //makes sure game can shutdown properly
        if (event.type == sf::Event::Closed)
            Engine::Instance().shutdown();

        //pauses game if window is minimized or resized while player is in a level
        if (Engine::Instance().get_mode() == MODE_PLAY && (event.type == sf::Event::LostFocus || event.type == sf::Event::Resized) && !state->is_paused())
            state->toggle_pause();

        if (event.type == sf::Event::Resized)
            preserve_aspect_ratio(event.size.width, event.size.height);
    }

    /*Called  by handle_event in order to change the viewport's aspect ratio when the window is resized,
    this avoids having to change any of the draw methods since the 800x600 pixel mapping is preserved*/
    void preserve_aspect_ratio(int width, int height)
    {
        sf::FloatRect viewport;
        viewport.width = 1.f;
        viewport.height = 1.f;

        //adjusts viewport so that 800x600 window is always centered and scaled properly
        if (width > height * ASPECT_RATIO)
        {
            viewport.width = (height * ASPECT_RATIO) / width;
            viewport.left = (1.f - viewport.width) / 2.f;
        }
        else if (width < height * ASPECT_RATIO)
        {
            viewport.height = width / (height * ASPECT_RATIO);
            viewport.top = (1.f - viewport.height) / 2.f;
        }

        sf::View view = app->getView();
        view.setViewport(viewport);
        app->setView(view);

    }
};

#endif //CSCI437_PLAYER_VIEW_H
