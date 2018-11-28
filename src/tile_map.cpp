#include "tile_map.h"
#include <cstdlib>
#include <time.h>
#include "macros.h"

void TileMap::PopulateVertexArray(Map &map, int level_num)
{
    width = map.get_width();
    height = map.get_height();
    level = level_num;

    //seeds random generator
    srand((unsigned int) time(NULL));

    // resize the vertex array to fit the level size
    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    sf::Vector2u tile_size = sf::Vector2u(16, 16);

    CellType cell_type;
    CellType above_cell_type;
    CellType below_cell_type;
    CellType left_cell_type;
    CellType right_cell_type;

    //so that ornaments are consistent within a room
    int ornament_index = -1;

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < height; ++i)
        for (unsigned int j = 0; j < width; ++j)
        {
            Cell cell = map.get_cell(i, j);
            cell_type = cell.get_cell_type();

            //determine upper and lower cell types
            if (i == 0) above_cell_type = WALL, below_cell_type = map.get_cell(i+1, j).get_cell_type();
            else if (i == height - 1) below_cell_type = WALL, above_cell_type = map.get_cell(i-1, j).get_cell_type();
            else above_cell_type = map.get_cell(i-1, j).get_cell_type(), below_cell_type = map.get_cell(i+1, j).get_cell_type();

            int tile_sheet_index;

            //determine location of appropriate tile in tileset based on cell type and adjacent cell types
            if (cell_type == FLOOR)
            {
                //randomly sets tile for variation in texture, 8 possible floor textures starting at index 14 in tile set
               tile_sheet_index = (rand() % 8) + 14;
            }
            else if (cell_type == ORNAMENT)
            {
                //necessary to have both the wall and floor ornament textures and consistent ornaments  within a room
                int temp;
                if (ornament_index == -1)
                {
                    ornament_index = (rand() % 4)*2 + 23;
                    temp = ornament_index;
                }
                else
                    temp = -1;

                //ensures that a room wasn't created directly above the ornament, uses regular wall instead
                if (above_cell_type != WALL || (i > 1 && map.get_cell(i-2,j).get_cell_type() != WALL))
                    tile_sheet_index = (rand() % 8) + 14;
                else
                {
                    //updates adjacent wall's texture
                    UpdateQuads(i-1, j, ornament_index, false);
                    tile_sheet_index = ornament_index + 1;
                }

                ornament_index = temp;
            }
            else if (cell_type == EXIT)
            {
                tile_sheet_index = 22;
            }

            if (cell_type == WALL)
            {
                tile_sheet_index = WallLogic(i, j, map, above_cell_type, below_cell_type);
            }
            else
                UpdateQuads(i, j, tile_sheet_index, false);




        }


}


void TileMap::SetTexture()
{
    m_tileset = resources.GetTexture("tileset");
    tileSize = sf::Vector2u(16,16);
}


void TileMap::UpdateQuads(int i, int j, int tile_index, bool empty) {

    // find its position in the tileset texture
    int tu = tile_index % (m_tileset.getSize().x / tileSize.x);
    int tv = tile_index / (m_tileset.getSize().x / tileSize.x); //+ tileSize.y * level;

    // get a pointer to the current tile's quad
    sf::Vertex* quad = &m_vertices[(j + i * width) * 4];

    // define its 4 corners
    quad[0].position = sf::Vector2f(j * CELL_SIZE, i * CELL_SIZE);
    quad[1].position = sf::Vector2f((j + 1) * CELL_SIZE, i * CELL_SIZE);
    quad[2].position = sf::Vector2f((j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
    quad[3].position = sf::Vector2f(j * CELL_SIZE, (i + 1) * CELL_SIZE);

    if (!empty)
    {
        // define its 4 texture coordinates
        quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }
    else
    {
        //fill with all black
        quad[0].color = sf::Color::Black;
        quad[1].color = sf::Color::Black;
        quad[2].color = sf::Color::Black;
        quad[3].color = sf::Color::Black;
    }

}

int TileMap::RandomWallIndex() {
    //returns an int from 0 to 4 where 0 is most likely and 4 is least likely
    int selection = rand() % 15;

    if (selection < 5)
        return 0;
    else if (selection < 9)
        return 1;
    else if (selection < 12)
        return 2;
    else if (selection < 14)
        return 3;
    else
        return 4;
}


int TileMap::WallLogic(int i, int j, Map &map, CellType above_cell_type, CellType below_cell_type)
{
    //determine left and right cell types
    CellType left_cell_type, right_cell_type;
    if (j == 0) left_cell_type = WALL, right_cell_type = map.get_cell(i, j+1).get_cell_type();
    else if (j == width - 1) right_cell_type = WALL, left_cell_type = map.get_cell(i, j-1).get_cell_type();
    else left_cell_type = map.get_cell(i, j-1).get_cell_type(), right_cell_type = map.get_cell(i, j+1).get_cell_type();

    //determine diagonal cell types
    CellType up_left, up_right, down_left, down_right;
    if (i == 0)
    {
        up_left = WALL;
        up_right = WALL;
        down_left = (j == 0) ? WALL : map.get_cell(i+1, j-1).get_cell_type();
        down_right = (j == width - 1 ) ? WALL : map.get_cell(i+1, j+1).get_cell_type();
    }
    else if (j == 0)
    {
        up_left = WALL;
        down_left = WALL;
        up_right = map.get_cell(i-1, j+1).get_cell_type();
        down_right = (i == height - 1) ? WALL : map.get_cell(i+1, j+1).get_cell_type();
    }
    else
    {
        up_left = map.get_cell(i-1, j-1).get_cell_type();

        if (i == height - 1)
        {
            down_left = WALL, down_right = WALL;
            up_right = (j == width - 1) ? WALL : map.get_cell(i-1, j+1).get_cell_type();
        }
        else if (j == width - 1) up_right = WALL, down_right = WALL, down_left = map.get_cell(i+1, j-1).get_cell_type();
        else
        {
            down_left = map.get_cell(i+1,j-1).get_cell_type();
            up_right = map.get_cell(i-1,j+1).get_cell_type();
            down_right = map.get_cell(i+1, j+1).get_cell_type();
        }
    }
    //determine wall orientation and return index in tile sheet of appropriate wall
    int tile_sheet_index;
    bool empty = false;

    //HORIZONTAL WALL
    if (left_cell_type == WALL && right_cell_type == WALL)
    {
        if ((above_cell_type != WALL && below_cell_type != WALL) || (above_cell_type == WALL && below_cell_type != WALL))
            tile_sheet_index = RandomWallIndex();

        else if (above_cell_type == WALL && below_cell_type == WALL){
            if (down_right == WALL && down_left == WALL && up_right == WALL && up_left == WALL)
                empty = true, tile_sheet_index = 0;

            else if (down_right == WALL && down_left == WALL && up_left != WALL && up_right == WALL)
                tile_sheet_index = 32;
            else if (down_right == WALL && down_left == WALL && up_left == WALL && up_right != WALL)
                tile_sheet_index = 33;
            else if (down_right == WALL && down_left == WALL && up_left != WALL && up_right != WALL)
                tile_sheet_index = 34;
            else if (down_right == WALL && down_left != WALL && up_right == WALL)
                tile_sheet_index = 11;
            else if (down_right == WALL && down_left != WALL && up_right != WALL)
                tile_sheet_index = 8;
            else if (down_right != WALL && down_left == WALL && up_left == WALL)
                tile_sheet_index = 12;
            else if (down_right != WALL && down_left == WALL && up_left != WALL)
                tile_sheet_index = 9;
            else// if (down_right != WALL && down_left != WALL && up_left == WALL && up_right == WALL)
                tile_sheet_index = 10;

        }

        else //above cell is not wall and lower cell is wall
        {
            if (down_left != WALL && down_right == WALL)
                tile_sheet_index = 8;
            else if (down_left == WALL && down_right != WALL)
                tile_sheet_index = 9;
            else if (down_left != WALL && down_right != WALL)
                tile_sheet_index = 10;
            else
                tile_sheet_index = RandomWallIndex();
        }
    }
        //WALL ON LEFT SIDE
    else if (left_cell_type != WALL && right_cell_type == WALL)
    {
        if (above_cell_type == WALL && below_cell_type == WALL && down_right == WALL && up_right == WALL)
            tile_sheet_index = 11;
        else if (above_cell_type == WALL && below_cell_type == WALL && up_right != WALL && down_right == WALL)
            tile_sheet_index = 36;
        else if (above_cell_type == WALL && below_cell_type == WALL && up_right == WALL && down_right != WALL)
            tile_sheet_index = 13;
        else if (above_cell_type == WALL && below_cell_type != WALL && up_right == WALL)
            tile_sheet_index = 5;
        else if (above_cell_type == WALL && below_cell_type != WALL && up_right != WALL)
            tile_sheet_index = 7;
        else if (above_cell_type != WALL && below_cell_type == WALL && down_right == WALL)
            tile_sheet_index = 8;
        else if (above_cell_type != WALL && below_cell_type == WALL && down_right != WALL && down_left != WALL)
            tile_sheet_index = 10;
        else //if (above_cell_type != WALL && below_cell_type != WALL)
        {
            tile_sheet_index = RandomWallIndex();
        }

    }
        // WALL ON RIGHT EDGE
    else if (left_cell_type == WALL && right_cell_type != WALL)
    {
        if (above_cell_type == WALL && below_cell_type == WALL && down_left == WALL && up_left == WALL)
            tile_sheet_index = 12;
        else if (above_cell_type == WALL && below_cell_type == WALL && up_left != WALL && down_left == WALL)
            tile_sheet_index = 35;
        else if (above_cell_type == WALL && below_cell_type == WALL && up_left == WALL && down_left != WALL)
            tile_sheet_index = 13;
        else if (above_cell_type == WALL && below_cell_type != WALL && up_left == WALL)
            tile_sheet_index = 6;
        else if (above_cell_type == WALL && below_cell_type != WALL && up_left != WALL)
            tile_sheet_index = 7;
        else if (above_cell_type != WALL && below_cell_type == WALL && down_left == WALL)
            tile_sheet_index = 9;
        else if (above_cell_type != WALL && below_cell_type == WALL && down_left != WALL && down_right != WALL)
            tile_sheet_index = 10;
        else //if (above_cell_type != WALL && below_cell_type != WALL)
        {
            tile_sheet_index = RandomWallIndex();
        }
    }
        //VERTICAL WALLS
    else //if (left_cell_type != WALL && right_cell_type != WALL)
    {
        if (above_cell_type == WALL && below_cell_type == WALL)
            tile_sheet_index = 13;
        else if (above_cell_type == WALL && below_cell_type != WALL)
            tile_sheet_index = 7;
        else if (above_cell_type != WALL && below_cell_type == WALL)
            tile_sheet_index = 10;
        else //if (above_cell_type != WALL && below_cell_type != WALL)
            tile_sheet_index = 31;
    }

    UpdateQuads(i, j, tile_sheet_index, empty);
    return tile_sheet_index;
}