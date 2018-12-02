#ifndef CSCI437_ALG_AGENT_BASED_H
#define CSCI437_ALG_AGENT_BASED_H

#include <vector>
#include "macros.h"
#include <cstdlib>
#include <math.h>
#include <random>
#include "vector2d.h"
#include "ResourceManager.h"



/*
	Uses Agent Based algorithm to generate rooms within a 2D character vector 
	and paths between the rooms
*/
class AgentBasedGenerator
{
public:
	AgentBasedGenerator();
	~AgentBasedGenerator() = default;

	std::vector<std::vector<char>> &createLevelGrid(int level);
	bool placeRoom(int i, int j);
	void placeEntities(int num_enemies);
	void placeTreasure(int num_treasures);
	void printLevelGrid();
	std::vector<Vector2D> &getPathNodes() { return path_nodes;}

	//current floor number
	int floor;

	//level parameters, read from level-parameters.xml
	int width;
	int height;
	float prob_room;
	float prob_turn;
	int min_rooms;
	float fraction_total_size;
	int num_gold;
	int num_skeleton_white;
	int num_skeleton_red;
	int num_skeleton_gold;
	int num_ghost_white;
	int num_ghost_red;
	int num_ghost_gold;
	int num_orc_green;
	int num_orc_red;
	int num_orc_gold;


	//extreme points to cut down size of map
	int min_x, max_x, min_y, max_y;

	//player's initial coordinates
	int player_x;
	int player_y;

	//exit's coordinates
	int exit_x;
	int exit_y;

	//vector of enemy initial coordinates
	std::vector<std::vector<int>> enemy_coords;
	std::vector<std::vector<int>> treasure_coords;
	std::vector<std::vector<char>> level_grid;

private:
	void SetLevelParams(int level);
	int chooseRandomDirection(int cur_dir, bool orthogonal);
	int createStartAndExit();

	bool checkPointInBounds(int i, int j)
	{ return ((i < width - 2) && (j < height - 2) && (i > 1) && (j > 1)); }
	
	float euclideanDistance(int x1, int y1, int x2, int y2) { return sqrtf((float)(x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)); }
	void updateExtremeCoords(int cur_x, int cur_y);

	//stores information about each room in the level
	std::vector<std::vector<int>> rooms;

	//vector for enemy movement
	std::vector<Vector2D> path_nodes;

	//indices in the above vector that correspond to the player's starting room and exit rooms
	int player_room_index;
	int exit_room_index;

	int max_room_size;
	int min_room_size;


	int direction_x;
	int direction_y;

	int num_rooms;
	int num_enemies;
	int avg_i;
	int avg_j;

	//xml stuff for loading levels
	//ensures the xml file text does not go out of scope
	rapidxml::xml_node<> *root_node;
	std::shared_ptr <std::vector<char>> buffer;


};

//global access to resource manager
extern ResourceManager resources;


#endif //CSCI437_ALG_AGENT_BASED_H