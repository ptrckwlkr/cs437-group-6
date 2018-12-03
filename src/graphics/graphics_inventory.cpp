#include "graphics/graphics_inventory.h"
#include "views/player_view_inventory.h"

InventoryGraphics::InventoryGraphics(InventoryView *view) : Graphics(), view(view)
{

}

void InventoryGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

	// This must always be the first line of every draw method
	states.transform *= getTransform();
	camera_reset(target);

	sf::Sprite sprite;
        sprite.setScale(.25,.25);
	sprite.setTexture(resources.GetTexture(gear.getItem(EquipSlot::Head)->getSprite()));
	target.draw(sprite, states);
	sprite.setTexture(resources.GetTexture(gear.getItem(EquipSlot::Chest)->getSprite()));
	sprite.setPosition(64,0);
	target.draw(sprite, states);
	sprite.setTexture(resources.GetTexture(gear.getItem(EquipSlot::Shoulders)->getSprite()));
	sprite.setPosition(128,0);
	target.draw(sprite, states);
	sprite.setTexture(resources.GetTexture(gear.getItem(EquipSlot::Legs)->getSprite()));
	sprite.setPosition(192,0);
	target.draw(sprite, states);
	sprite.setTexture(resources.GetTexture(gear.getItem(EquipSlot::Feet)->getSprite()));
	sprite.setPosition(256,0);
	target.draw(sprite, states);
	sprite.setTexture(resources.GetTexture(gear.getItem(EquipSlot::Hands)->getSprite()));
	sprite.setPosition(320,0);
	target.draw(sprite, states);
}
