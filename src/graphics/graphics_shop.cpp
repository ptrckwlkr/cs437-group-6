#include "graphics/graphics_shop.h"


ShopGraphics::ShopGraphics(ShopView *view) : Graphics(), view(view)
{
    // get all necessary resources from resource manager
    font = resources.GetFont("old_school");
    std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
    buffer = resources.GetXMLBuffer("text");
    root_node = (*doc).first_node("Root")->first_node("Shop");
}

void ShopGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    // This must always be the first line of every draw method
    states.transform *= getTransform();
    camera_reset(target);
    sf::Text manaText = prepareText("ManaText", font);
    sf::Text healthText = prepareText("HealthText", font);
    //sf::Text aText = prepareText("AbilitiesText", font);
    sf::Text exitText = prepareText("ExitText", font);
    sf::Text goldText = prepareText("GoldText", font);
    sf::Text shopkeeper = prepareText("ShopKeeperText", font);
    sf::Texture shop = resources.GetTexture("shop");
    sf::Sprite sprite;
    sf::RectangleShape rectangle, rectangle2;


    rectangle.setSize(sf::Vector2f(400, 200));
    rectangle2.setSize(sf::Vector2f(250, 200));
    rectangle.setFillColor(sf::Color::Black);
    rectangle2.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle2.setOutlineColor(sf::Color::Red);
    rectangle2.setOutlineThickness(9);
    rectangle.setOutlineThickness(9);
    rectangle.setPosition(WINDOW_WIDTH/ 13, 370);
    rectangle2.setPosition(rectangle.getPosition().x + 400, 370);

    sprite.setTexture(shop);
    sprite.setOrigin(shop.getSize().x, shop.getSize().y);
    sprite.setPosition(WINDOW_WIDTH,WINDOW_HEIGHT - 250);
    sprite.setColor(sf::Color(255, 255, 255, 160));

    shopkeeper.setPosition(rectangle.getPosition().x +160,rectangle.getPosition().y +20);
    manaText.setPosition(rectangle2.getPosition().x + 120,rectangle2.getPosition().y + 20);
    healthText.setPosition(manaText.getPosition().x +10, manaText.getPosition().y + 40);
    //aText.setPosition(healthText.getPosition().x, healthText.getPosition().y + 40);
    exitText.setPosition(healthText.getPosition().x, healthText.getPosition().y + 40);
    goldText.setPosition(exitText.getPosition().x, exitText.getPosition().y + 40);

    //target.draw(aText, states);
    target.draw(manaText, states);
    target.draw(exitText, states);
    target.draw(healthText, states);
    target.draw(goldText, states);
    target.draw(rectangle, states);
    target.draw(rectangle2, states);
    target.draw(shopkeeper,states);
    target.draw(sprite, states);

}
