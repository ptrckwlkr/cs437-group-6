#include "graphics/graphics_inventory.h"
#include "views/player_view_inventory.h"
#include "macros.h"

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
		sprite.setTexture(resources.GetTexture(gear.getItem(slots[i])->getSprite()));
		sprite.setPosition(WINDOW_WIDTH/4.f,64+(64*(i+1))+(4*i));
		target.draw(sprite, states);
	 };

	sf::Text statHeader = prepareText("Attack", font);
	statHeader.setOrigin(statHeader.getLocalBounds().width/2.f, statHeader.getLocalBounds().height/2.f);
	statHeader.setPosition(WINDOW_WIDTH/2.f + 64, 88);
	target.draw(statHeader, states);
	statHeader = prepareText("Magic", font);
	statHeader.setOrigin(statHeader.getLocalBounds().width/2.f, statHeader.getLocalBounds().height/2.f);
	statHeader.setPosition(WINDOW_WIDTH/2.f + 128, 88);
	target.draw(statHeader, states);
	statHeader = prepareText("Defense", font);
	statHeader.setOrigin(statHeader.getLocalBounds().width/2.f, statHeader.getLocalBounds().height/2.f);
	statHeader.setPosition(WINDOW_WIDTH/2.f + 192, 88);
	target.draw(statHeader, states);
	statHeader = prepareText("Health", font);
	statHeader.setOrigin(statHeader.getLocalBounds().width/2.f, statHeader.getLocalBounds().height/2.f);
	statHeader.setPosition(WINDOW_WIDTH/2.f + 256, 88);
	target.draw(statHeader, states);
	statHeader = prepareText("Mana", font);
	statHeader.setOrigin(statHeader.getLocalBounds().width/2.f, statHeader.getLocalBounds().height/2.f);
	statHeader.setPosition(WINDOW_WIDTH/2.f + 320, 88);
	target.draw(statHeader, states);

	std::string stats[5] = {"attack", "magic", "defense", "hp", "mp"};
	sf::Text statText;
	statText.setFont(font);
	statText.setCharacterSize(20);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			statText.setString(std::to_string(gear.getItem(slots[i])->getStat(stats[j])));
			statText.setOrigin(statText.getLocalBounds().width/2.f, statText.getLocalBounds().height/2.f);
			statText.setPosition(WINDOW_WIDTH/2.f + 64 * (j+1), 96+(64*(i+1))+(4*i));
			target.draw(statText, states);
		}
	}	
}
