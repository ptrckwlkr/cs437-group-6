#ifndef CSCI437_GRAPHICS_SHOP_H
#define CSCI437_GRAPHICS_SHOP_H


#include "graphics.h"
#include "macros.h"
#include <string>

class ShopView;
class ShopGraphics : public Graphics{

    public:
        explicit ShopGraphics(ShopView *view);

    private:
        ShopView *view;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        sf::Font font;
        sf::Text title;
        std::vector<sf::Text> controls;
        sf::Text aboutText;

    };


#endif //CSCI437_GRAPHICS_SHOP_H
