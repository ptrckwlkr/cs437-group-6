#include "alg_agent_based.h"
#include <iostream>

AgentBasedGenerator::AgentBasedGenerator(int width, int height, float prob_room, float prob_turn, int room_size_modifier)
{
	this->width = width;
	this->height = height;
	this->prob_room = prob_room;
	this->prob_turn = prob_turn;

	num_rooms = 0;

	max_room_size = 9 + room_size_modifier;
	min_room_size = 3 + room_size_modifier;

	//seeds random generator for testing purposes
	srand(123456789);
	//srand(420);

	std::vector<std::vector<char>> level_grid(height, std::vector<char>(width, '-'));
	this->level_grid = level_grid;
}


std::vector<std::vector<char>> AgentBasedGenerator::createLevelGrid()
{
	int distance_traveled = 0;
	//determine digger's initial coordinates and place first room
	int digger_x, digger_y;
	do {
		digger_x = rand() % width;
		digger_y = rand() % height;
	} while (!placeRoom(digger_x, digger_y));

	int cur_dir = chooseRandomDirection(-1, false);

	
	while (num_rooms < 15 || distance_traveled < (width * height)/32.0)
	{
		//move digger by 1 unit in random direction until the end of the room is reached
		while (level_grid[digger_y][digger_x] == '0')
		{
			digger_x += direction_x;
			digger_y += direction_y;
			distance_traveled++;

			if (!checkPointInBounds(digger_x, digger_y)) // turn around if the point is out of bounds
				cur_dir = chooseRandomDirection(cur_dir, false);
		}

		//we are now outside the room and still in bounds,
		int cur_prob_turn = 0, cur_prob_room = 0 - prob_room; // ensures room isn't generated immediately
		int rand_turn, rand_room;
		do {
			level_grid[digger_y][digger_x] = '1';

			//generate random numbers between 1 and 100 for probabilities
			rand_turn = (rand() % 100) + 1;
			rand_room = (rand() % 100) + 1;

			//turn if random number is less than probability or if point is out of bounds
			if (rand_turn < cur_prob_turn)
			{
				cur_dir = chooseRandomDirection(cur_dir, true);
				cur_prob_turn = 0;
			}
			else
				cur_prob_turn += prob_turn; //increase probability of turn by passed value if no turn

			while (!checkPointInBounds(digger_x + direction_x, digger_y + direction_y))
			{
				cur_dir = chooseRandomDirection(cur_dir, true);
				cur_prob_turn = 0;
			}
			//increase probability of room and move the digger
			cur_prob_room += prob_room;	
			digger_x += direction_x, digger_y += direction_y;
			distance_traveled++;

		} while (rand_room > cur_prob_room || !placeRoom(digger_x, digger_y));


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
	four cardinal directions. If the direction has been set before then the new direction will be different
	(and optionally orthognal) from the previous direction.
*/
int AgentBasedGenerator::chooseRandomDirection(int cur_dir, bool orthogonal)
{
	//ensures the direction actually changes and is orthogonal
	int new_dir;
	do {
		//uniform distribution between 0 and 3
		new_dir = rand() % 4;
	} while (cur_dir == new_dir || (cur_dir % 2 == new_dir % 2 && orthogonal));

	if (new_dir == 0)						//let 0 represent North
		direction_x = 0, direction_y = -1;
	else if (new_dir == 1)					//let 1 represent East
		direction_x = 1, direction_y = 0;
	else if (new_dir == 2)					//let 2 represent South
		direction_x = 0, direction_y = 1;
	else								//let 3 represent West
		direction_x = -1, direction_y = 0;

	return new_dir;
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