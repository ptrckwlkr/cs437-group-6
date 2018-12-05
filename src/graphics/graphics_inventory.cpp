#include "graphics/graphics_inventory.h"
#include "views/player_view_inventory.h"
#include "macros.h"
#include "Equipment.h"

InventoryGraphics::InventoryGraphics(InventoryView *view) : Graphics(), view(view)
{
    // get all necessary resource from resource manager
    font = resources.GetFont("old_school");
    std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
    buffer = resources.GetXMLBuffer("text");
    root_node = (*doc).first_node("Root")->first_node("Inventory");
}

void InventoryGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

	// This must always be the first line of every draw method
	states.transform *= getTransform();
	camera_reset(target);

	sf::Text header = prepareText("Header", font);
	header.setOrigin(header.getLocalBounds().width/2.f, header.getLocalBounds().height/2.f);
	header.setPosition(WINDOW_WIDTH/2.f, 32);
	target.draw(header, states);

	EquipSlot slots[6] = {EquipSlot::Head, EquipSlot::Chest, EquipSlot::Shoulders, EquipSlot::Legs, EquipSlot::Feet, EquipSlot::Hands};

	sf::Sprite sprite;
        sprite.setScale(.25,.25);
	for (int i = 0; i < 6; i++) {
		auto item = view->get_state().get_player_data().get_gear().getItem(slots[i])->getEquipItem();
		switch (item)
		{
			case renegade_head:
				sprite.setTexture(resources.GetTexture("renegade_head"));
				break;
			case renegade_armor:
				sprite.setTexture(resources.GetTexture("renegade_armor"));
				break;
			case renegade_shoulders:
				sprite.setTexture(resources.GetTexture("renegade_shoulders"));
				break;
			case renegade_pants:
				sprite.setTexture(resources.GetTexture("renegade_pants"));
				break;
			case renegade_boots:
				sprite.setTexture(resources.GetTexture("renegade_boots"));
				break;
			case renegade_gloves:
				sprite.setTexture(resources.GetTexture("renegade_gloves"));
				break;
			default:
				sprite.setTexture(resources.GetTexture("renegade_head"));
				break;
		}
		sprite.setPosition(WINDOW_WIDTH/4.f,64+(64*(i+1))+(4*i));
		target.draw(sprite, states);
	 };

	std::string stats[5] = {"Attack", "Magic", "Defense", "Health", "Mana"};
	sf::Text statHeader;

	for (int i = 0; i < 5; i++) {
	sf::Text statHeader = prepareText(stats[i], font);
	statHeader.setOrigin(statHeader.getLocalBounds().width/2.f, statHeader.getLocalBounds().height/2.f);
	statHeader.setPosition(WINDOW_WIDTH/2.f + (64 * (i+1)), 88);
	target.draw(statHeader, states);
	}	

	sf::Text statText;
	statText.setFont(font);
	statText.setCharacterSize(20);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			statText.setString(std::to_string(view->get_state().get_player_data().get_gear().getItem(slots[i])->getStat(stats[j])));
			statText.setOrigin(statText.getLocalBounds().width/2.f, statText.getLocalBounds().height/2.f);
			statText.setPosition(WINDOW_WIDTH/2.f + 64 * (j+1), 96+(64*(i+1))+(4*i));
			target.draw(statText, states);
		}
	}	
}
