#include "views/view_sreep.h"


SreepView::SreepView(GameLogic *state, Sreep &s) : View(state)
{
    sreep = &s;
    aggro = false;
    firing = false;
    timer = 0;
    fire_option = 0;
    shots_fired = 0;
    stream_fired = 0;
}

void SreepView::update(float delta)
{
    Vector2D dir = state->get_level().get_player().get_position() - sreep->get_position();
    if (!aggro && dir.length < 500)
        aggro = true;
    if (aggro)
    {
        timer += delta;
        printf("%f\n", timer);
        if (!firing && timer > 7)
        {
            firing = true;
            fire_option = 1 + rand() % 2;
            timer = 0;
        }
        if (firing)
        {
            if (fire_option == 1 && timer > 0.5)
            {
                sreep->fire_all_dirs();
                shots_fired++;
                timer = 0;
            }
            if (fire_option == 2 && timer > 0.1)
            {
                sreep->fire_at_player();
                stream_fired++;
                timer = 0;
            }
            if (shots_fired > 7 || stream_fired > 50)
            {
                firing = false;
                timer = 0;
                shots_fired = 0;
                stream_fired = 0;
            }
        }
        else
        {
            sreep->move(dir, delta);
        }
    }
}
