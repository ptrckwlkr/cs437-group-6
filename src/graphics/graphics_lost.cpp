#include <string>
#include <engine.h>
#include "graphics/graphics_lost.h"

#include "macros.h"

LostGraphics::LostGraphics(LostView *view) : Graphics(), view(view)
{
    // get all necessary resources from resource manager
    font = resources.GetFont("old_school");
    std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
    buffer = resources.GetXMLBuffer("text");
    root_node = (*doc).first_node("Root")->first_node("Lost");
    this->view = view;

}

void LostGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    // This must always be the first line of every draw method
    states.transform *= getTransform();
    camera_reset(target);
    sf::Text title = prepareText("LostText", font);
    sf::Text stats = prepareText("StatsText", font);
    sf::Text number = prepareText("NumberText", font);
    sf::Text goldstats = prepareText("GoldStatsText", font);
    sf::Text goldNum = prepareText("GoldNumText", font);
    number.setString(std::to_string( Engine::Instance().get_state().get_player_data().get_total_enemies()) );
    goldNum.setString(std::to_string(Engine::Instance().get_state().get_player_data().get_gold_lost() ));
    sf::Text playAgain = prepareText("ReplayText", font);

    //center
    title.setOrigin(title.getLocalBounds().width / 2.0, title.getLocalBounds().height / 2.0);
    title.setPosition(WINDOW_WIDTH / 2, 150);
    stats.setOrigin(title.getLocalBounds().width / 2.0, title.getLocalBounds().height / 2.0);
    stats.setPosition(WINDOW_WIDTH /  3, title.getPosition().y + 100);
    number.setPosition(stats.getPosition().x + 100, stats.getPosition().y +15);
    goldstats.setPosition(WINDOW_WIDTH /  3, stats.getPosition().y + 120);
    goldstats.setOrigin(title.getLocalBounds().width / 2.0, title.getLocalBounds().height / 2.0);
    goldNum.setPosition(stats.getPosition().x + 100, goldstats.getPosition().y + 15);
    playAgain.setOrigin(title.getLocalBounds().width / 8.0, title.getLocalBounds().height / 8.0);
    playAgain.setPosition(WINDOW_WIDTH / 2.5, title.getPosition().y + 350);

    target.draw(title, states);
    target.draw(playAgain, states);
    target.draw(number, states);
    target.draw(stats, states);
    target.draw(goldNum, states);
    target.draw(goldstats, states);

}