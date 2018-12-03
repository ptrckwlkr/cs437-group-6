#include "graphics/graphics_lost.h"

#include "macros.h"

LostGraphics::LostGraphics(LostView *view) : Graphics(), view(view)
{
    // get all necessary resources from resource manager
    font = resources.GetFont("old_school");
    std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
    buffer = resources.GetXMLBuffer("text");
    root_node = (*doc).first_node("Root")->first_node("Lost");

}

void LostGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    // This must always be the first line of every draw method
    states.transform *= getTransform();
    camera_reset(target);
    sf::Text title = prepareText("LostText", font);
    sf::Text playAgain = prepareText("ReplayText", font);
    //centers text
    title.setOrigin(title.getLocalBounds().width / 2.0, title.getLocalBounds().height / 2.0);
    title.setPosition(WINDOW_WIDTH / 2.0, 200);
    playAgain.setOrigin(title.getLocalBounds().width / 8.0, title.getLocalBounds().height / 8.0);
    playAgain.setPosition(WINDOW_WIDTH / 2.3, 300);

    target.draw(title, states);
    target.draw(playAgain, states);

}