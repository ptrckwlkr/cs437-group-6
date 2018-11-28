#ifndef CSCI437_ALG_AGENT_BASED_H
#define CSCI437_ALG_AGENT_BASED_H

#include <vector>
#include "macros.h"
#include <cstdlib>
#include <math.h>
#include <random>



/*
	Uses Agent Based algorithm to generate rooms within a 2D character vector 
	and paths between the rooms
*/
class AgentBasedGenerator
{
public:
	AgentBasedGenerator(int width, int height, float prob_room, float prob_turn, int room_size_modifier);
	~AgentBasedGenerator() = default;

	std::vector<std::vector<char>> &createLevelGrid(int max_rooms, int num_enemies, float fraction_total_size);
	bool placeRoom(int i, int j);
	void placeEntities(int num_enemies);
	void placeTreasure(int num_treasures);
	void printLevelGrid();

	int width;
	int height;

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
	int chooseRandomDirection(int cur_dir, bool orthogonal);
	int createStartAndExit();

	bool checkPointInBounds(int i, int j)
	{ return ((i < width - 2) && (j < height - 2) && (i > 1) && (j > 1)); }
	
	float euclideanDistance(int x1, int y1, int x2, int y2) { return sqrtf((float)(x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)); }

	//stores information about each room in the level
	std::vector<std::vector<int>> rooms;

	//indices in the above vector that correspond to the player's starting room and exit rooms
	int player_room_index;
	int exit_room_index;

	int max_room_size;
	int min_room_size;
	
	float prob_room;
	float prob_turn;

	int direction_x;
	int direction_y;

	int num_rooms;
	int avg_i;
	int avg_j;

};


#endif //CSCI437_ALG_AGENT_BASED_H