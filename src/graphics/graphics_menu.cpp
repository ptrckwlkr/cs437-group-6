
#include "graphics/graphics_menu.h"
#include "views/player_view_menu.h"
#include "macros.h"

MenuGraphics::MenuGraphics(MenuView *view) : Graphics(), view(view)
{
	// get all necessary resources from resource manager
	font = resources.GetFont("old_school");
	std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
	buffer = resources.GetXMLBuffer("text");
	root_node = (*doc).first_node("Root")->first_node("Menu");
	//change first node to be the new class to be created in xml chart
	storeStaticText();
}

void MenuGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// This must always be the first line of every draw method
	states.transform *= getTransform();

	camera_reset(target);

	if (view->screenIndex == 0)		//draw elements for title screen
	{
		drawTitleScreenDynamicText(target, states, view->selectionIndex);
		target.draw(title, states);
	}
	else if (view->screenIndex == 1)  //draw elements for controls screen
	{
		for (unsigned int i = 0; i < controls.size(); i++)
			target.draw(controls[i], states);
	}
	else if (view->screenIndex == 2)	//draw elements for about screen
		target.draw(aboutText, states);

	//always draws the menu instructions so the player is not confused about how to operate the menu
	for (unsigned int i = 0; i < menuInstructions.size(); i++)
		target.draw(menuInstructions[i], states);
}


/*
	Helper method to prepare all text items that will not be changed in any way 
*/
void MenuGraphics::storeStaticText()
{
	//title text
	title = prepareText("title", font);
	//centers text
	title.setOrigin(title.getLocalBounds().width / 2.0, title.getLocalBounds().height / 2.0);
	title.setPosition(WINDOW_WIDTH / 2.0, 125);

	//prepares the menu controls text
	menuInstructions.push_back(prepareText("navigation", font));
	menuInstructions.push_back(prepareText("accept", font));
	menuInstructions.push_back(prepareText("back", font));
	menuInstructions[0].setPosition(WINDOW_WIDTH / 2.0, 515);
	menuInstructions[1].setPosition(WINDOW_WIDTH / 2.0, 540);
	menuInstructions[2].setPosition(WINDOW_WIDTH / 2.0, 565);

	//prepares the about page's text
	aboutText = prepareText("about-page", font);
	aboutText.setPosition(WINDOW_WIDTH / 2.0, (WINDOW_HEIGHT / 2.0) - 75);

	storeControlText();

	//prepares for when the dynamic buttons are created
	root_node = root_node->first_node("buttons");

}


/*
	helper function for drawDynamicText that draws text for the titleScreen
*/
void MenuGraphics::drawTitleScreenDynamicText(sf::RenderTarget &target, sf::RenderStates states, int index) const
{
	sf::Text playButton = prepareText("play", font);
	sf::Text controlsButton = prepareText("controls", font);
	sf::Text aboutButton = prepareText("about", font);

	//play button's color is updated properly
	playButton.setPosition(WINDOW_WIDTH / 2.0, 300);
	if (index == 0)
		playButton.setFillColor(sf::Color::Cyan);
	else
		playButton.setFillColor(sf::Color::White);

	//controls button's color is updated properly
	controlsButton.setPosition(WINDOW_WIDTH / 2.0, 350);
	if (index == 1)
		controlsButton.setFillColor(sf::Color::Cyan);
	else
		controlsButton.setFillColor(sf::Color::White);
	
	//exit button's color is updated properly
	aboutButton.setPosition(WINDOW_WIDTH / 2.0, 400);
	if (index == 2)
		aboutButton.setFillColor(sf::Color::Cyan);
	else
		aboutButton.setFillColor(sf::Color::White);

	target.draw(playButton, states);
	target.draw(controlsButton, states);
	target.draw(aboutButton, states);
}

/*
	Helper function for storeStaticText which prepares the control screen's text
*/
void MenuGraphics::storeControlText()
{
	//used to iterate through game-text.xml 
	std::vector<std::string> xmlStrings;
	xmlStrings.push_back("movement");
	xmlStrings.push_back("aim");
	xmlStrings.push_back("lweapon");
	xmlStrings.push_back("rweapon");
	xmlStrings.push_back("inventory");
	xmlStrings.push_back("interact");


	//coordinates for each entry
	int lhs_x = WINDOW_WIDTH / 2.0 - 50;
	int rhs_x = WINDOW_WIDTH / 2.0 + 95;
	int y_start = 125;
	int offset = 50;

	for (int i = 0; i < 6; i++)
	{
		//reads text from xml file and creates an sf::Text object with a good position position 
		controls.push_back(prepareText("control-" + xmlStrings[i] + "-lhs", font));		//this 2.0 is to keep the same height from prepareText()
		controls[2 * i].setOrigin(controls[2 * i].getLocalBounds().width, controls[2 * i].getLocalBounds().height / 2.0);
		controls[2*i].setPosition(lhs_x, y_start + i * offset);

		controls.push_back(prepareText("control-" + xmlStrings[i] + "-rhs", font));
		controls[2*i+1].setPosition(rhs_x, y_start + i * offset);
	}
}