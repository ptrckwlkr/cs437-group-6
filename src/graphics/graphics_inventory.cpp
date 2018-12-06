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
	for (int i = 0; i < 6; i++) {
		auto item = view->get_state().get_player_data().get_gear().getItem(slots[i]);
    //sprite = EquipSprite::getEquipSprite(item->get, Headitem->);
		//EquipSprite::getEquipSprite(Renegade, Head, sprite);
    sf::Texture texture = resources.GetTexture(EquipSprite::getEquipSprite(Renegade, Head, sprite));
    sprite.setTexture(texture);
		sprite.setPosition(WINDOW_WIDTH/4.f,64+(64*(i+1))+(4*i));
		target.draw(sprite, states);
  };
  /*

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
   */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace EquipSprite;

std::string EquipSprite::getEquipSprite(EquipSet set, EquipSlot slot)
{
	static const std::map<std::pair<EquipSet, EquipSlot>, std::string> equipMap {
					{std::pair<EquipSet, EquipSlot>(Renegade, Head), 		  std::string("renegade_head")},
					{std::pair<EquipSet, EquipSlot>(Renegade, Chest), 		std::string("renegade_armor")},
					{std::pair<EquipSet, EquipSlot>(Renegade, Shoulders),	std::string("renegade_shoulders")},
					{std::pair<EquipSet, EquipSlot>(Renegade, Legs), 		  std::string("renegade_pants")},
					{std::pair<EquipSet, EquipSlot>(Renegade, Feet), 		  std::string("renegade_boots")},
					{std::pair<EquipSet, EquipSlot>(Renegade, Hands), 		std::string("renegade_gloves")},
	};

	auto i = equipMap.find(std::pair<EquipSet, EquipSlot>(set, slot));
	if (i != equipMap.end()) {
    return i->second;
	}
  return std::string("renegade_head");
}
