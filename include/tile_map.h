#ifndef CSCI437_TILE_MAP_H
#define CSCI437_TILE_MAP_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <random>
#include "map.h"
#include "ResourceManager.h"

class TileMap
{
public:
    TileMap();
    ~TileMap() = default;

    void PopulateVertexArray(Map &map, int level_num);
    sf::VertexArray &GetVertices() { return m_vertices; };
    void SetTexture();



private:
    void UpdateQuads(int i, int j, int tile_index, bool empty);
    int RandomFloorIndex();
    int RandomWallIndex();
    int WallLogic(int i, int j, Map &map, CellType above_cell_type, CellType below_cell_type);

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    //Mersenne-Twister engine;
    std::mt19937 generator;

    int width;
    int height;
    int level;
    sf::Vector2u tileSize;

};

//global access to resource manager
extern ResourceManager resources;

#endif //CSCI437_TILE_MAP_H
