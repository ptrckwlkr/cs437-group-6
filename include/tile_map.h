#ifndef CSCI437_TILE_MAP_H
#define CSCI437_TILE_MAP_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "map.h"
#include "ResourceManager.h"

class TileMap
{
public:
    TileMap() = default;
    ~TileMap() = default;

    void PopulateVertexArray(Map map, int level_num);
    sf::VertexArray GetVertices() { return m_vertices; };
    void SetTexture();



private:

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

};

//global access to resource manager
extern ResourceManager resources;

#endif //CSCI437_TILE_MAP_H
