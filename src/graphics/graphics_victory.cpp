#include "graphics/graphics_victory.h"
#include "views/player_view_menu.h"
#include "macros.h"

VictoryGraphics::VictoryGraphics(VictoryView *view) : Graphics(), view(view)
{
    // get all necessary resources from resource manager
    font = resources.GetFont("old_school");
    std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
    buffer = resources.GetXMLBuffer("text");
    root_node = (*doc).first_node("Root")->first_node("Victory");
}

void VictoryGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // This must always be the first line of every draw method
    states.transform *= getTransform();

    camera_reset(target);

    //title text
    sf::Text title = prepareText("winText", font);
    sf::Text playAgain = prepareText("playAgainButton", font);
    //centers text
    title.setOrigin(title.getLocalBounds().width / 2.0, title.getLocalBounds().height / 2.0);
    title.setPosition(WINDOW_WIDTH / 2.0, 200);
    playAgain.setOrigin(title.getLocalBounds().width / 8.0, title.getLocalBounds().height / 8.0);
    playAgain.setPosition(WINDOW_WIDTH / 2.3, 300);

    target.draw(title, states);
    target.draw( playAgain, states);

}


