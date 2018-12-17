#include <engine.h>
#include <views/player_view_shop.h>
#include <graphics/sprites_equipment.h>
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

    // Draw shop image
    sf::Sprite sprite;
    sf::Texture shop = resources.GetTexture("shop");
    sprite.setTexture(shop);
    sprite.setOrigin(shop.getSize().x, shop.getSize().y);
    sprite.setPosition(WINDOW_WIDTH,WINDOW_HEIGHT - 250);
    sprite.setColor(sf::Color(255, 255, 255, 128));
    target.draw(sprite, states);

    // Draw UI border
    sf::RectangleShape border;
    border.setSize(sf::Vector2f(750, 200));
    border.setFillColor(sf::Color::Black);
    border.setOutlineColor(sf::Color::Red);
    border.setOutlineThickness(9);
    border.setPosition(25, 375);
    target.draw(border, states);

    // Draw gold
    sf::Sprite gold;
    sf::Texture goldTexture = resources.GetTexture("goldTexture");
    gold.setTexture(goldTexture);
    gold.setTextureRect(sf::IntRect(goldTexture.getSize().x / 5, goldTexture.getSize().y / 4 * 2, goldTexture.getSize().x / 5, goldTexture.getSize().y / 4));
    gold.setScale(2.0, 2.0);
    gold.setPosition(0, 0);
    target.draw(gold, states);

    sf::Text coffers;
    coffers.setFont(font);
    coffers.setCharacterSize(20);
    coffers.setString(std::to_string(view->get_state().get_player_data().get_gold()));
    coffers.setOrigin(0, coffers.getLocalBounds().height / 2.f);
    coffers.setPosition(100, 50);
    target.draw(coffers, states);

    if (view->screenIndex == 0)
    {
        // Divider
        sf::RectangleShape divider;
        divider.setSize(sf::Vector2f(9, 200));
        divider.setFillColor(sf::Color::Red);
        divider.setPosition(400, 375);
        target.draw(divider, states);

        // Draw text
        sf::Text buyEquipText = prepareText("BuyEquipmentText", font, false);
        buyEquipText.setPosition(view->selectionBoxes[0].x, view->selectionBoxes[0].y);
        target.draw(buyEquipText, states);

        sf::Text buyHealthText = prepareText("BuyHealthText", font, false);
        buyHealthText.setPosition(view->selectionBoxes[1].x, view->selectionBoxes[1].y);
        target.draw(buyHealthText, states);

        sf::Text buyManaText = prepareText("BuyManaText", font, false);
        buyManaText.setPosition(view->selectionBoxes[2].x, view->selectionBoxes[2].y);
        target.draw(buyManaText, states);

        sf::Text exitText = prepareText("ExitText", font, false);
        exitText.setPosition(view->selectionBoxes[3].x, view->selectionBoxes[3].y);
        target.draw(exitText, states);

        sf::Text shopkeeper = prepareText("ShopKeeperText", font);
        shopkeeper.setPosition(175, 400);
        target.draw(shopkeeper, states);
    }
    else if (view->screenIndex == 1)
    {
        for (auto itemBox : view->itemBoxes)
        {
            auto item = itemBox.entry->item;

            // Draw box
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(itemBox.box.width, itemBox.box.height));
            cell.setOutlineColor(sf::Color::Red);
            if (itemBox.entry->item->isEquipped())
                cell.setFillColor(sf::Color(0, 64, 0));
            else
                cell.setFillColor(sf::Color::Black);
            cell.setOutlineThickness(1);
            cell.setPosition(itemBox.box.x, itemBox.box.y);
            target.draw(cell, states);

            // Draw item
            sf::Sprite equipSprite;
            sf::Texture texture = resources.GetTexture(EquipSprite::getEquipSprite(item->getSet(), item->getSlot()));
            equipSprite.setTexture(texture);
            equipSprite.setPosition(itemBox.box.x + 10, itemBox.box.y + 10);
            float scaleFactor = (itemBox.box.height - 20) / equipSprite.getLocalBounds().height;
            equipSprite.setScale(scaleFactor, scaleFactor);
            target.draw(equipSprite, states);

            if (!itemBox.entry->purchased)
            {
                // Draw gold
                sf::Sprite goldImage;
                sf::Texture goldTexture = resources.GetTexture("goldTexture");
                goldImage.setTexture(goldTexture);
                goldImage.setTextureRect(sf::IntRect(goldTexture.getSize().x / 5, goldTexture.getSize().y / 4 * 2, goldTexture.getSize().x / 5, goldTexture.getSize().y / 4));
                goldImage.setPosition(itemBox.box.x + 90, itemBox.box.y - 10);
                target.draw(goldImage, states);

                // Draw price
                sf::Text price = prepareText("Gold", font);
                price.setString(std::to_string(itemBox.entry->price));
                price.setPosition(itemBox.box.x + 102, itemBox.box.y + 35);
                target.draw(price, states);
            }

            sf::CircleShape triangle(20, 3);
            triangle.setOutlineColor(sf::Color::Red);
            triangle.setFillColor(sf::Color::Black);
            triangle.setOutlineThickness(1);
            triangle.setOrigin(20, 20);
            if (view->slideIndex > 0)
            {
                triangle.setPosition(view->selectionBoxes[12].x + view->selectionBoxes[12].width / 2,
                                     view->selectionBoxes[12].y + view->selectionBoxes[12].height / 2);
                triangle.setRotation(-90);
                target.draw(triangle, states);
            }
            if (view->slideIndex < 23)
            {
                triangle.setPosition(view->selectionBoxes[13].x + view->selectionBoxes[13].width / 2,
                                     view->selectionBoxes[13].y + view->selectionBoxes[13].height / 2);
                triangle.setRotation(90);
                target.draw(triangle, states);
            }
        }
    }
    else if (view->screenIndex == 2)
    {
        auto entry = view->viewing;
        auto item = entry->item;
        sf::Sprite equipSprite;
        sf::Texture texture = resources.GetTexture(EquipSprite::getEquipSprite(item->getSet(), item->getSlot()));
        equipSprite.setTexture(texture);
        equipSprite.setPosition(50, 400);
        float scaleFactor = 100 / equipSprite.getLocalBounds().height;
        equipSprite.setScale(scaleFactor, scaleFactor);
        target.draw(equipSprite, states);

        auto buyButton = view->selectionBoxes[14];

        sf::RectangleShape buyBorder;
        buyBorder.setSize(sf::Vector2f(buyButton.width, buyButton.height));
        buyBorder.setOutlineColor(sf::Color::Red);
        buyBorder.setFillColor(sf::Color::Black);
        buyBorder.setOutlineThickness(1);
        buyBorder.setPosition(buyButton.x, buyButton.y);
        target.draw(buyBorder, states);


        sf::Text buttonText;
        if (entry->purchased)
            buttonText = prepareText("EquipText", font);
        else
            buttonText = prepareText("PurchaseText", font);
        buttonText.setPosition(buyButton.x + buyButton.width / 2, buyButton.y + buyButton.height / 2);
        target.draw(buttonText, states);

        sf::Text attackText = prepareText("AttackText", font);
        attackText.setPosition(300, 400);
        target.draw(attackText, states);

        sf::Text attackStat;
        attackStat.setFont(font);
        attackStat.setCharacterSize(20);
        attackStat.setString(std::to_string(item->getStat(Attack)));
        attackStat.setOrigin(attackStat.getLocalBounds().width / 2.f, attackStat.getLocalBounds().height / 2.f);
        attackStat.setPosition(300, 450);
        target.draw(attackStat, states);

        sf::Text defenceText = prepareText("DefenceText", font);
        defenceText.setPosition(400, 400);
        target.draw(defenceText, states);

        sf::Text defenceStat;
        defenceStat.setFont(font);
        defenceStat.setCharacterSize(20);
        defenceStat.setString(std::to_string(item->getStat(Defence)));
        defenceStat.setOrigin(defenceStat.getLocalBounds().width / 2.f, defenceStat.getLocalBounds().height / 2.f);
        defenceStat.setPosition(400, 450);
        target.draw(defenceStat, states);

        sf::Text healthText = prepareText("HealthText", font);
        healthText.setPosition(500, 400);
        target.draw(healthText, states);

        sf::Text healthStat;
        healthStat.setFont(font);
        healthStat.setCharacterSize(20);
        healthStat.setString(std::to_string(item->getStat(Health)));
        healthStat.setOrigin(healthStat.getLocalBounds().width / 2.f, healthStat.getLocalBounds().height / 2.f);
        healthStat.setPosition(500, 450);
        target.draw(healthStat, states);

        sf::Text manaText = prepareText("ManaText", font);
        manaText.setPosition(600, 400);
        target.draw(manaText, states);

        sf::Text manaStat;
        manaStat.setFont(font);
        manaStat.setCharacterSize(20);
        manaStat.setString(std::to_string(item->getStat(Mana)));
        manaStat.setOrigin(manaStat.getLocalBounds().width / 2.f, manaStat.getLocalBounds().height / 2.f);
        manaStat.setPosition(600, 450);
        target.draw(manaStat, states);

        sf::Text regenText = prepareText("RegenText", font);
        regenText.setPosition(700, 400);
        target.draw(regenText, states);

        sf::Text magicStat;
        magicStat.setFont(font);
        magicStat.setCharacterSize(20);
        magicStat.setString(std::to_string(item->getStat(Magic)));
        magicStat.setOrigin(magicStat.getLocalBounds().width / 2.f, magicStat.getLocalBounds().height / 2.f);
        magicStat.setPosition(700, 450);
        target.draw(magicStat, states);

        if (!entry->purchased)
        {
            // Draw gold
            sf::Sprite goldImage;
            sf::Texture goldTexture = resources.GetTexture("goldTexture");
            goldImage.setTexture(goldTexture);
            goldImage.setTextureRect(
                    sf::IntRect(goldTexture.getSize().x / 5, goldTexture.getSize().y / 4 * 2, goldTexture.getSize().x / 5,
                                goldTexture.getSize().y / 4));
            goldImage.setScale(2.0, 2.0);
            goldImage.setPosition(650, 500);
            target.draw(goldImage, states);

            sf::Text price;
            price.setFont(font);
            price.setCharacterSize(20);
            price.setString(std::to_string(entry->price));
            price.setOrigin(price.getLocalBounds().width, price.getLocalBounds().height / 2.f);
            price.setPosition(640, 545);
            target.draw(price, states);
        }
    }
}
