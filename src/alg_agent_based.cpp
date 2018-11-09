#include "alg_agent_based.h"
#include <iostream>

AgentBasedGenerator::AgentBasedGenerator(int width, int height, int prob_room, int prob_turn, int room_size_modifier)
{
	this->width = width;
	this->height = height;
	this->prob_room = prob_room;
	this->prob_turn = prob_turn;

	num_rooms = 0;

	max_room_size = 9 + room_size_modifier;
	min_room_size = 3 + room_size_modifier;

	//seeds random generator for testing purposes
	//srand(123456789);
	srand(420);

	std::vector<std::vector<char>> level_grid(height, std::vector<char>(width, '-'));
	this->level_grid = level_grid;
}


std::vector<std::vector<char>> AgentBasedGenerator::createLevelGrid()
{
	//determine digger's initial coordinates and place first room
	int digger_x, digger_y;
	do {
		digger_x = rand() % width;
		digger_y = rand() % height;
	} while (!placeRoom(digger_x, digger_y));
	level_grid[digger_y][digger_x] = 'a';

	chooseRandomDirection(true);
	printf("direction x:%d, y:%d\n", direction_x, direction_y);
	printf("position x:%d, y:%d\n", digger_x, digger_y);

	//move digger by 1 unit in random direction until the end of the room is reached
	while (level_grid[digger_y][digger_x] == '0' || level_grid[digger_y][digger_x] == 'a')
	{
		digger_x += direction_x;
		digger_y += direction_y;
		printf("position x:%d, y:%d\n", digger_x, digger_y);
	}
	
	if (checkPointInBounds(digger_x, digger_y))
	{
		level_grid[digger_y][digger_x] = '1';
	}



	return level_grid;
}


/*
	returns true if a room is placed and false if the room cannot be placed
	NOTE THAT ROOMS CAN BE PLACED ON TOP OF EACHOTHER
*/
bool AgentBasedGenerator::placeRoom(int i, int j)
{
	/*j and i without any changes represent the top left corner of room so by subtracting a random offset
	that is less than the room size you can generate a room where the passed values of i and j are not the top left  */
	//generates random number between min and max room size
	int room_width = (rand() % (max_room_size + 1 - min_room_size)) + min_room_size;
	int room_height = (rand() % (max_room_size + 1 - min_room_size)) + min_room_size;
	//offset is between 0 and room_width - 1 (and room_height - 1) so that (i, j) is still in the room
	i -= (rand() % room_width);
	j -= (rand() % room_height);
	
	// area that bounds are checked is one unit smaller than actual bounds so that there is a wall between a room and the void
	if (j > 0 && i > 0 && j < (height - 2) - max_room_size &&  i < (width - 2) - max_room_size)
	{
		
		for (int a = 0; a < room_height; a++)
		{
			for (int b = 0; b < room_width; b++)
				level_grid[j + a][i + b] = '0';
		}

		num_rooms++;
		return true;
	}

	return false;
}



/*
	Updates the direction members randomly. If they have not been set, then the direction could be any of the 
	four cardinal directions. If the direction has been set before then the new direction will be orthogonal
	to the old direction
*/
void AgentBasedGenerator::chooseRandomDirection(bool first_time)
{
	if (!first_time) //only generate orthogonal directions if a direction already exists (ie not first time)
	{
		// generates random number between 0 and 1
		int dir = rand() % 2;

		if (direction_x != 0)	// direction is currently East or West
		{
			direction_x = 0;
			direction_y = 2 * dir - 1;	//direction becomes North if dir = 0 and South if dir = 1
		}
		else					// direction is currently North or South
		{
			direction_x = 2 * dir - 1; //direction becomes West if dir = 0 and East if dir = 1
			direction_y = 0;
		}
	
	}
	else //generate 4 possible directions for the first time
	{
		// generates random number between 0 and 3
		int dir = rand() % 4;
		if (dir == 0)						//let 0 represent North
			direction_x = 0, direction_y = -1;
		else if (dir == 1)					//let 1 represent East
			direction_x = 1, direction_y = 0;
		else if (dir == 2)					//let 2 represent South
			direction_x = 0, direction_y = 1;
		else								//let 3 represent West
			direction_x = -1, direction_y = 0;
	}

}


void AgentBasedGenerator::printLevelGrid()
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			std::cout << level_grid[j][i];
		}
		std::cout << std::endl;
	}
}