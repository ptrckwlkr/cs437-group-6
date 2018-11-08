#include "alg_agent_based.h"
#include <iostream>

AgentBasedGenerator::AgentBasedGenerator(int prob_room, int prob_turn, int room_size_modifier)
{
	this->prob_room = prob_room;
	this->prob_turn = prob_turn;

	max_room_size = 8 + room_size_modifier;
	min_room_size = 3 + room_size_modifier;

	//seeds random generator for testing purposes
	srand(123456789);

	std::vector<std::vector<char>> level_grid(128, std::vector<char>(128, '-'));
	this->level_grid = level_grid;
}


std::vector<std::vector<char>> AgentBasedGenerator::createLevelGrid()
{
	return level_grid;
}


void AgentBasedGenerator::placeRoom(int i, int j)
{

}


void AgentBasedGenerator::printLevelGrid()
{
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			std::cout << level_grid[i][j];
		}
		std::cout << std::endl;
	}
}