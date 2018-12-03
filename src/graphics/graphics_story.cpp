#include "graphics/graphics_story.h"
#include "macros.h"

StoryGraphics::StoryGraphics(StoryView *view) : Graphics(), view(view)
{
    // get all necessary resources from resource manager
    font = resources.GetFont("old_school");
    std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
    buffer = resources.GetXMLBuffer("text");
    root_node = (*doc).first_node("Root")->first_node("Story");

}

void StoryGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    // This must always be the first line of every draw method
    states.transform *= getTransform();
    sf::Text title = prepareText("StoryText", font);
    sf::Text playAgain = prepareText("ReplayText", font);

    sf::Texture mountains = resources.GetTexture("mountains");
    sf::Sprite sprite;
    sf::RectangleShape rectangle;

    sprite.setTexture(mountains);
    sprite.setOrigin(mountains.getSize().x, mountains.getSize().y);
    sprite.setColor(sf::Color(255, 255, 255, 200));
    sprite.setPosition(WINDOW_WIDTH-100,WINDOW_HEIGHT -300);
    //centers text
    title.setOrigin(title.getLocalBounds().width / 2.0, title.getLocalBounds().height / 2.0);
    title.setPosition(WINDOW_WIDTH -400, 400);
    playAgain.setOrigin(title.getLocalBounds().width / 8.0, title.getLocalBounds().height / 8.0);
    playAgain.setPosition(WINDOW_WIDTH / 2.3, 550);

    rectangle.setSize(sf::Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height-25));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Blue);
    rectangle.setOutlineThickness(9);
    rectangle.setPosition(sprite.getPosition().x - sprite.getGlobalBounds().width, sprite.getPosition().y -sprite.getGlobalBounds().height+27);

    target.draw(title, states);
    target.draw(sprite, states);
    target.draw(playAgain, states);
    target.draw(rectangle, states);

}
