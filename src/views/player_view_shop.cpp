#include "engine.h"
#include "graphics/graphics_shop.h"
#include"views/player_view_shop.h"
#include <random>

ShopView::ShopView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App)
{
    selectionIndex = 0;
    graphics = std::make_shared<ShopGraphics>(this);
    App->setView(App->getDefaultView());
    //generateShopItems();
}

void ShopView::process_input(float delta)
{

}

void ShopView::handle_event(sf::Event event)
{
    sf::Vector2f mouse_pos = (*app).mapPixelToCoords(sf::Mouse::getPosition(*app));

    if (event.type == sf::Event::Closed) Engine::Instance().shutdown();
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

    if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Q)
    {
        Engine::Instance().switch_mode(MODE_LEVEL_SELECT);
    }
}

void ShopView::update(float delta)
{
    //Process input
    sf::Event event;
    while (app->pollEvent(event))
    {
        handle_event(event);
        //common_handle_event_tasks(event);
    }
    process_input(delta);
}

void ShopView::draw(float delta)
{
    app->clear(sf::Color::Black);
    app->draw(*graphics);
    app->display();
}

void ShopView::generateShopItems() {
	std::random_device r;
	std::mt19937 generator(r());
	std::uniform_int_distribution<int> inFive(1,5);
	std::uniform_int_distribution<int> inSix(1,6);
	std::uniform_int_distribution<int> inTen(1,10);

	std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("equipment");
	std::shared_ptr<std::vector<char>> buffer = resources.GetXMLBuffer("equipment");
	rapidxml::xml_node<> *root_node = (*doc).first_node("Root");

	EquipSlot slots[6] = {EquipSlot::Head, EquipSlot::Chest, EquipSlot::Shoulders, EquipSlot::Legs, EquipSlot::Feet, EquipSlot::Hands};
	char* sets[10] = {"renegade","crimson_rogue","forest_priest","guard","iron_hunter","cultist","gatekeeper","illusionist","marauder","sharpshooter"};
	char* statnames[5] = {"attack","magic","defense","health","mana"};

	for (int i = 0; i < 5; i++) {
		int slot = inFive(generator);
		float statIncrease = inTen(generator) / 100;
		int statTotal = (int) get_state().get_player_data().get_gear().getItem(slots[slot])->getStatTotal() * statIncrease;
		int eachStat = (int) floor(statTotal/5);
		int leftover = statTotal % 5;
		int stats[5] = {eachStat, eachStat, eachStat, eachStat, eachStat};
		bool increase[5] = {false, false, false, false, false};
		int statToIncrease;
		while (leftover > 0) {
			statToIncrease = inFive(generator);
			if (!increase[statToIncrease]) {
				stats[statToIncrease] += 1;
				leftover -= 1;
			}
		}
		int set = inTen(generator);
		rapidxml::xml_node<> *set_node = root_node->first_node(sets[set]);
		float modifier;
		for (int j = 0; j < 5; j++) {
			modifier = std::stof(set_node->first_node(statnames[j])->value());
			stats[j] = (int) stats[j] * modifier;
		}
		shopItems[i] = (std::shared_ptr<Equipment>) new Equipment(EquipSet(set), EquipSlot(slot), stats[0], stats[1], stats[2], stats[3], stats[4]);
	}

}
