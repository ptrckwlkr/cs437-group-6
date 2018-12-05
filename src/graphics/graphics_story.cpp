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

    camera_reset(target);
    sf::Text title = prepareText("StoryText", font);
    sf::Text playAgain = prepareText("ReplayText", font);

    sf::Texture mountains = resources.GetTexture("mountains");
    sf::Sprite sprite;
    sf::RectangleShape rectangle;

    sprite.setTexture(mountains);
    sprite.setOrigin(sprite.getLocalBounds().width/2.f, sprite.getLocalBounds().height/2.f);
    sprite.setColor(sf::Color(255, 255, 255, 200));
    sprite.setPosition(WINDOW_WIDTH/2.f, (WINDOW_HEIGHT - 300) - mountains.getSize().y/2.f );
    //centers text
    title.setPosition(WINDOW_WIDTH / 2.f, 400);
    playAgain.setPosition(WINDOW_WIDTH / 2.f, 550);

    rectangle.setSize(sf::Vector2f(sprite.getLocalBounds().width,sprite.getLocalBounds().height - 28));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Blue);
    rectangle.setOutlineThickness(9);
    rectangle.setOrigin(rectangle.getLocalBounds().width / 2.f, rectangle.getLocalBounds().height / 2.f );
    rectangle.setPosition(WINDOW_WIDTH/2.f+8.5, (WINDOW_HEIGHT - 300) - mountains.getSize().y/2.f + 22);

    target.draw(title, states);
    target.draw(sprite, states);
    target.draw(playAgain, states);
    target.draw(rectangle, states);

}
