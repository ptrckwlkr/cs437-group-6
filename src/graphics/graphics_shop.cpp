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
    sf::Text manaText = prepareText("ManaText", font);
    sf::Text aText = prepareText("AbilitiesText", font);
    //need health text
    sf::Text exitText = prepareText("ExitText", font);

    sf::Texture shop = resources.GetTexture("shop");
    sf::Sprite sprite;
    sf::RectangleShape rectangle;
    sf::RectangleShape rectangle2;


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
    //centers text
    manaText.setPosition(rectangle2.getPosition().x + 80,rectangle2.getPosition().y + 50);
    aText.setPosition(manaText.getPosition().x + 20, manaText.getPosition().y + 50);
    exitText.setPosition(aText.getPosition().x -40 , aText.getPosition().y + 50);

    target.draw(aText, states);
    target.draw(manaText, states);
    target.draw(exitText, states);
    target.draw(rectangle, states);
    target.draw(rectangle2, states);
    target.draw(sprite, states);

}
