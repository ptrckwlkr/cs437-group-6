#include "tile_map.h"
#include <cstdlib>


void TileMap::PopulateVertexArray(Map map, int level_num)
{
    int width = map.get_width();
    int height = map.get_height();

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    sf::Vector2u tile_size = sf::Vector2u(16, 16);

    CellType cell_type;
    CellType above_cell_type;
    CellType below_cell_type;
    CellType left_cell_type;
    CellType right_cell_type;


    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < height; ++i)
        for (unsigned int j = 0; j < width; ++j)
        {
            Cell cell = map.get_cell(i, j);
            cell_type = cell.get_cell_type();

            //determine adjacent cell types
            if (j == 0) left_cell_type = WALL, right_cell_type = map.get_cell(i, j+1).get_cell_type();
            else if (j == width - 1) right_cell_type = WALL, left_cell_type = map.get_cell(i, j-1).get_cell_type();
            else left_cell_type = map.get_cell(i, j-1).get_cell_type(), right_cell_type = map.get_cell(i, j+1).get_cell_type();

            if (i == 0) above_cell_type = WALL, below_cell_type = map.get_cell(i+1, j).get_cell_type();
            else if (i == width - 1) below_cell_type = WALL, above_cell_type = map.get_cell(i-1, j).get_cell_type();
            else above_cell_type = map.get_cell(i-1, j).get_cell_type(), below_cell_type = map.get_cell(i+1, j).get_cell_type();

            //determine location of appropriate tile in tileset based on cell type and adjacent cell types
            if (cell_type == FLOOR)
            {
                //randomly sets tile for variation in texture
            }




        }


}


void TileMap::SetTexture()
{
    m_tileset = resources.GetTexture("tileset");
}

