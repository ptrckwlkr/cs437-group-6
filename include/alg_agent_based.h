#ifndef CSCI437_ALG_AGENT_BASED_H
#define CSCI437_ALG_AGENT_BASED_H

#include <vector>
#include "macros.h"
#include <cstdlib>
#include <math.h>



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
	void printLevelGrid();

	int width;
	int height;

	//player's initial coordinates
	int player_x;
	int player_y;

	//vector of enemy initial coordinates
	std::vector<std::vector<int>> enemy_coords;

	std::vector<std::vector<char>> level_grid;

private:
	int chooseRandomDirection(int cur_dir, bool orthogonal);

	bool checkPointInBounds(int i, int j)
	{ return ((i < width - 2) && (j < height - 2) && (i > 1) && (j > 1)); }

	float euclideanDistance(float x1, float y1, float x2, float y2) { return sqrtf((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)); }

	int createStartAndExit();

	//stores information to calculate appropriate entity and exit locations
	std::vector<std::vector<int>> rooms;
	std::vector<int> dungeon_corners;
	int player_room_index;

	int max_room_size;
	int min_room_size;
	
	int prob_room;
	int prob_turn;

	int direction_x;
	int direction_y;

	int num_rooms;
	float avg_i;
	float avg_j;

};


#endif //CSCI437_ALG_AGENT_BASED_H