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
	AgentBasedGenerator(int prob_room, int prob_turn, int room_size_modifier);
	~AgentBasedGenerator() = default;

	std::vector<std::vector<char>> createLevelGrid();
	void placeRoom(int i, int j);
	void printLevelGrid();

	std::vector<std::vector<char>> level_grid;

private:

	int max_room_size;
	int min_room_size;
	
	int prob_room;
	int prob_turn;

	int direction_x;
	int direction_y;

};


#endif //CSCI437_ALG_AGENT_BASED_H