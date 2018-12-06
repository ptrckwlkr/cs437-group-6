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
    sf::Texture texture = resources.GetTexture(EquipSprite::getEquipSprite(item->getSet(), item->getSlot()));
    sprite.setTexture(texture);
		sprite.setPosition(WINDOW_WIDTH / 4.f, 64 + (64 * (i + 1)) + (4 * i));
		sprite.setScale(0.25, 0.25);
		target.draw(sprite, states);
  };

	std::string stats[5] = {"Attack", "Magic", "Defense", "Health", "Mana"};
	for (int i = 0; i < 5; i++) {
    sf::Text stat = prepareText(stats[i], font);
    stat.setOrigin(stat.getLocalBounds().width / 2.f, stat.getLocalBounds().height / 2.f);
    stat.setPosition(WINDOW_WIDTH / 2.f + (64 * (i + 1)), 88);
    target.draw(stat, states);
	}

	sf::Text statText;
	statText.setFont(font);
	statText.setCharacterSize(20);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			statText.setString(std::to_string(view->get_state().get_player_data().get_gear().getItem(slots[i])->getStat((Stat)j)));
			statText.setOrigin(statText.getLocalBounds().width / 2.f, statText.getLocalBounds().height / 2.f);
			statText.setPosition(WINDOW_WIDTH / 2.f + 64 * (j + 1), 96 + (64 * (i + 1)) + (4 * i));
			target.draw(statText, states);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace EquipSprite;

std::string EquipSprite::getEquipSprite(EquipSet set, EquipSlot slot)
{
	static const std::map<std::pair<int, int>, std::string> equipMap {
					{std::make_pair<int, int>(Renegade, Head), 		    std::string("renegade_head")},
					{std::make_pair<int, int>(Renegade, Chest), 		  std::string("renegade_armor")},
					{std::make_pair<int, int>(Renegade, Shoulders),	  std::string("renegade_shoulders")},
					{std::make_pair<int, int>(Renegade, Legs), 		    std::string("renegade_pants")},
					{std::make_pair<int, int>(Renegade, Feet), 		    std::string("renegade_boots")},
					{std::make_pair<int, int>(Renegade, Hands), 		  std::string("renegade_gloves")},
	};
	auto i = equipMap.find(std::pair<int, int>(set, slot));
  return i->second;
}
