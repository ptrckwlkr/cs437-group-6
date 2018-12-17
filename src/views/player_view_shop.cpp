#include "engine.h"
#include "graphics/graphics_shop.h"
#include"views/player_view_shop.h"
#include <random>

ShopView::ShopView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App)
{
    screenIndex = 0;
    slideIndex = 0;
    graphics = std::make_shared<ShopGraphics>(this);
    items = &Engine::Instance().get_shop().get_items();

    // Main menu options
    selectionBoxes[0] = {420, 380, 340, 30};
    selectionBoxes[1] = {420, 415, 340, 30};
    selectionBoxes[2] = {420, 450, 340, 30};
    selectionBoxes[3] = {420, 485, 340, 30};

    // Item screen options
    selectionBoxes[4] = {85, 385, 150, 85};
    selectionBoxes[5] = {85, 480, 150, 85};
    selectionBoxes[6] = {245, 385, 150, 85};
    selectionBoxes[7] = {245, 480, 150, 85};
    selectionBoxes[8] = {405, 385, 150, 85};
    selectionBoxes[9] = {405, 480, 150, 85};
    selectionBoxes[10] = {565, 385, 150, 85};
    selectionBoxes[11] = {565, 480, 150, 85};

    // Arrows
    selectionBoxes[12] = {35, 450, 40, 50};
    selectionBoxes[13] = {725, 450, 40, 50};

    // Purchase button
    selectionBoxes[14] = {50, 515, 200, 50};

    itemBoxes[0] = {selectionBoxes[4], &(*items)[0]};
    itemBoxes[1] = {selectionBoxes[5], &(*items)[1]};
    itemBoxes[2] = {selectionBoxes[6], &(*items)[2]};
    itemBoxes[3] = {selectionBoxes[7], &(*items)[3]};
    itemBoxes[4] = {selectionBoxes[8], &(*items)[4]};
    itemBoxes[5] = {selectionBoxes[9], &(*items)[5]};
    itemBoxes[6] = {selectionBoxes[10], &(*items)[6]};
    itemBoxes[7] = {selectionBoxes[11], &(*items)[7]};

    App->setView(App->getDefaultView());
}

void ShopView::process_input(float delta)
{

}

void ShopView::handle_event(sf::Event event)
{
    if (event.type == sf::Event::Closed) Engine::Instance().shutdown();
    else if (event.type == sf::Event::EventType::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::S)
        {
            if (screenIndex == 0) Engine::Instance().switch_mode(MODE_LEVEL_SELECT);
            else if (screenIndex == 1) screenIndex = 0;
            else if (screenIndex == 2) screenIndex = 1;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mouse_pos = (*app).mapPixelToCoords(sf::Mouse::getPosition(*app));
        int clicked = clickedBox((int) mouse_pos.x, (int) mouse_pos.y);
        if (screenIndex == 0) controlsScreen1(clicked);
        else if (screenIndex == 1) controlsScreen2(clicked);
        else if (screenIndex == 2) controlsScreen3(clicked);
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

int ShopView::clickedBox(int x, int y)
{
    int i;
    if (screenIndex == 0)
    {
        for (i = 0; i < 4; ++i)
        {
            auto box = selectionBoxes[i];
            if (x > box.x && x < box.x + box.width && y > box.y && y < box.y + box.height) return i + 1;
        }
    }
    else if (screenIndex == 1)
    {
        for (i = 4; i < 14; ++i)
        {
            auto box = selectionBoxes[i];
            if (x > box.x && x < box.x + box.width && y > box.y && y < box.y + box.height) return i + 1;
        }
    }
    else if (screenIndex == 2)
    {
        for (i = 14; i < 15; ++i)
        {
            auto box = selectionBoxes[i];
            if (x > box.x && x < box.x + box.width && y > box.y && y < box.y + box.height) return i + 1;
        }
    }
    return 0;
}

void ShopView::controlsScreen1(int clicked)
{
    if (clicked == 1)
    {
      screenIndex = 1;
    }
    else if (clicked == 2)
    {
      if (get_state().get_player_data().get_gold() >= 300)
      {
        get_state().get_player_data().add_health();
        get_state().get_player_data().subtract_gold(300);
      }
    }
    else if (clicked == 3)
    {
      if (get_state().get_player_data().get_gold() >= 300)
      {
        get_state().get_player_data().add_mana();
        get_state().get_player_data().subtract_gold(300);
      }
    }
    else if (clicked == 4)
    {
      Engine::Instance().switch_mode(MODE_LEVEL_SELECT);
    }
}

void ShopView::controlsScreen2(int clicked)
{
    if (clicked >= 5 && clicked <= 12)
    {
        viewing = itemBoxes[clicked - 5].entry;
        screenIndex = 2;
    }
    if (clicked == 13)
    {
        if (slideIndex > 0) slideIndex--;
        updateItems();
    }
    else if (clicked == 14)
    {
        if (slideIndex < (items->size() - 8) / 2) slideIndex++;
        updateItems();
    }
}

void ShopView::controlsScreen3(int clicked)
{
    if (clicked == 15)
    {
        if (viewing->purchased)
        {
            state->get_player_data().get_gear().equipItem(viewing->item);
            screenIndex = 1;
        }
        else if (state->get_player_data().get_gold() >= viewing->price)
        {
            state->get_player_data().get_gear().equipItem(viewing->item);
            state->get_player_data().subtract_gold(viewing->price);
            viewing->purchased = true;
            screenIndex = 1;
        }
    }
}

void ShopView::updateItems()
{
    int base = slideIndex * 2;
    itemBoxes[0] = {selectionBoxes[4], &(*items)[base]};
    itemBoxes[1] = {selectionBoxes[5], &(*items)[base + 1]};
    itemBoxes[2] = {selectionBoxes[6], &(*items)[base + 2]};
    itemBoxes[3] = {selectionBoxes[7], &(*items)[base + 3]};
    itemBoxes[4] = {selectionBoxes[8], &(*items)[base + 4]};
    itemBoxes[5] = {selectionBoxes[9], &(*items)[base + 5]};
    itemBoxes[6] = {selectionBoxes[10], &(*items)[base + 6]};
    itemBoxes[7] = {selectionBoxes[11], &(*items)[base + 7]};
}
