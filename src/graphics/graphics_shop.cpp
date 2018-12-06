#include <engine.h>
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
    sf::Text totalText = prepareText("TotalText", font);
    sf::Text goldText = prepareText("GoldText", font);
    sf::Text gold = prepareText("Gold", font);
    sf::Text shopkeeper = prepareText("ShopKeeperText", font);
    sf::Text mText = prepareText("MText", font);
    sf::Text hText = prepareText("HText", font);
    sf::Text mana = prepareText("M", font);
    sf::Text health = prepareText("H", font);
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
    totalText.setPosition(exitText.getPosition().x - 60, exitText.getPosition().y + 30);
    goldText.setPosition(totalText.getPosition().x, totalText.getPosition().y + 20);
    gold.setString(std::to_string(Engine::Instance().get_state().get_player_data().get_gold()));
    gold.setPosition(goldText.getPosition().x +10, goldText.getPosition().y -5);

    mText.setPosition(goldText.getPosition().x, goldText.getPosition().y + 20);
    hText.setPosition(mText.getPosition().x, mText.getPosition().y + 20);
    mana.setString(std::to_string(Engine::Instance().get_state().get_player_data().get_mana()));
    health.setString(std::to_string(Engine::Instance().get_state().get_player_data().get_health()));
    mana.setPosition(mText.getPosition().x + 10, mText.getPosition().y - 5);
    health.setPosition(hText.getPosition().x + 10, hText.getPosition().y -5);

    target.draw(mana, states);
    target.draw(hText, states);
    target.draw(mText, states);
    target.draw(health, states);
    target.draw(manaText, states);
    target.draw(exitText, states);
    target.draw(healthText, states);
    target.draw(goldText, states);
    target.draw(gold, states);
    target.draw(totalText, states);
    target.draw(rectangle, states);
    target.draw(rectangle2, states);
    target.draw(shopkeeper,states);
    target.draw(sprite, states);

}
