#ifndef CSCI437_ALG_AGENT_BASED_H
#define CSCI437_ALG_AGENT_BASED_H

#include <vector>
#include "macros.h"
#include <cstdlib>



/*
	Uses Agent Based algorithm to generate rooms within a 2D character vector 
	and paths between the rooms
*/
class AgentBasedGenerator
{
public:
	AgentBasedGenerator(int width, int height, float prob_room, float prob_turn, int room_size_modifier);
	~AgentBasedGenerator() = default;

	std::vector<std::vector<char>> &createLevelGrid();
	bool placeRoom(int i, int j);
	void printLevelGrid();

	int width;
	int height;

	std::vector<std::vector<char>> level_grid;

private:
	int chooseRandomDirection(int cur_dir, bool orthogonal);

	bool checkPointInBounds(int i, int j)
	{ return ((i < width - 2) && (j < height - 2) && (i > 1) && (j > 1)); }


	int max_room_size;
	int min_room_size;
	
	int prob_room;
	int prob_turn;

	int direction_x;
	int direction_y;

	int num_rooms;

};


#endif //CSCI437_ALG_AGENT_BASED_H