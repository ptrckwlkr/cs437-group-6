#ifndef CSCI437_GRAPHICS_GAME_H
#define CSCI437_GRAPHICS_GAME_H

#include <SFML/Graphics.hpp>
#include "graphics.h"
#include "views/player_view.h"
#include "tile_map.h"
#include "sprite_manager.h"

class GameView;

class GameGraphics : public Graphics {

public:
    explicit GameGraphics(GameView *view);

private:
    GameView *view;

    void update(float delta) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void drawUI(sf::RenderTarget &target, sf::RenderStates states, float x, float y) const;

    void drawLevel(sf::RenderTarget &target, sf::RenderStates states) const;

    void storeLevel();

    void drawMap(sf::RenderTarget &target, sf::RenderStates states) const;

    void drawProjectileMotionBlur(sf::RenderTarget &target, sf::RenderStates states, sf::CircleShape,  std::vector<Vector2D> &trail) const;

    TileMap tile_map;
    sf::VertexArray vertices;
    sf::Texture tileTexture;

    std::vector<sf::RectangleShape> levelShapes;
    sf::Font font;

    SpriteManager spriteManager;

};


#endif //CSCI437_GRAPHICS_GAME_H
