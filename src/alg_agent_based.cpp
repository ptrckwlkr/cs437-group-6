#include "alg_agent_based.h"
#include <iostream>
#include <time.h>


/*
	params:
	int width : width of map;
	int height : height of map
	float prob_room : how much the probability that the digger will try to place a room increases
	float prob_turn : how much the probability that the digger will turn increases
	int room_size_modifier : increases min and max room size by this value
*/
AgentBasedGenerator::AgentBasedGenerator(int width, int height, float prob_room, float prob_turn, int room_size_modifier)
{
	this->width = width;
	this->height = height;
	this->prob_room = prob_room;
	this->prob_turn = prob_turn;

	max_room_size = 9 + room_size_modifier;
	min_room_size = 3 + room_size_modifier;

	//seeds random generator for testing purposes, using time(NULL) makes the level random every time
	//srand(123456789);
	srand((unsigned int) time(NULL));
}


/*
	Returns a 2D vector of chars representing the map of the level. Uses the Agent Based Algorithm
	discussed in class to create this level. Additionally chooses a cell for the player to start in
	and updates the member variable's player_x and player_y.

	max_rooms allows number of rooms to change

	param int fraction_total_size is essentially how much of the total map should the level cover,
	since it is a denominator, larger values == smaller size level
*/
std::vector<std::vector<char>> &AgentBasedGenerator::createLevelGrid(int max_rooms, int num_enemies, float fraction_total_size)
{
	std::vector<std::vector<char>> grid(height, std::vector<char>(width, '-'));
	this->level_grid = grid;

	//clears the vector of stored room information
	this->rooms.shrink_to_fit();

	num_rooms = 0;
	avg_i = 0, avg_j = 0;
	int distance_traveled = 0;

	//determine digger's initial coordinates and place first room
	int digger_x, digger_y;
	do {
		digger_x = rand() % width;
		digger_y = rand() % height;
	} while (!placeRoom(digger_x, digger_y));

	int cur_dir = chooseRandomDirection(-1, false);
	
	while (num_rooms < max_rooms || distance_traveled < (width * height)/fraction_total_size)
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
		float cur_prob_turn = 0, cur_prob_room = 0 - prob_room; // ensures room isn't generated immediately
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
	
	placeEntities(num_enemies);
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
		int a, b;
		
		for (a = 0; a < room_height; a++)
		{
			for (b = 0; b < room_width; b++)
				level_grid[j + a][i + b] = '0';
		}

		num_rooms++;
		avg_i += i;
		avg_j += j;

		//stores info about room in the member vector
		rooms.emplace_back(std::vector<int>{ i, j, room_width, room_height });
		return true;
	}

	return false;
}


/*
	Places specified number of enemies randomly within a random room that is not where the player starts.
	Additionally converts all coordinates to pixel space so that everything is drawn to the screen correctly later
*/
void AgentBasedGenerator::placeEntities(int num_enemies)
{
	int player_room = createStartAndExit();

	//mark exit cell
	level_grid[exit_y][exit_x] = 'E';

	//iterate through all rooms (except player's spawning room) and place an even number of enemies in the room
	for (int e = 0; e < num_enemies; e++)
	{
		//randomly choose a room that isn't the player's starting point
		int room;
		do {
			room = rand() % num_rooms;
		} while (room == player_room || euclideanDistance(player_x, player_y, rooms[room][0] + rooms[room][2] / 2, rooms[room][1] + rooms[room][3] / 2) < 12);

		std::vector<int> enemy_pos;

		do {
			enemy_pos = std::vector<int>{ (rooms[room][0] + rand() % rooms[room][2]), (rooms[room][1] + rand() % rooms[room][3]) };
		} //ensure that enemy position is not in a wall, far enough away from the player, and is unique 
		while (level_grid[enemy_pos[1]][enemy_pos[0]] != '0' || euclideanDistance(player_x, player_y, enemy_pos[0], enemy_pos[1]) <= 10
			|| (std::find(enemy_coords.begin(), enemy_coords.end(), enemy_pos) != enemy_coords.end()));
		
		//multiply by cell size and add small offset to center enemy before pushing to vector
		enemy_pos[0] = enemy_pos[0] * CELL_SIZE + CELL_SIZE / 2;
		enemy_pos[1] = enemy_pos[1] * CELL_SIZE + CELL_SIZE / 2;
		enemy_coords.emplace_back(enemy_pos);

	}
	// multiply coordinates by cell size before leaving function so that everything works properly in the graphics
	player_x *= CELL_SIZE, player_y *= CELL_SIZE;
	exit_x *= CELL_SIZE, exit_y *= CELL_SIZE;
}


/*
	Determines the player's starting location and the exit's location using logic with the rooms
	returns the index of the player's starting room within the rooms vector for use in placeEntities
*/
int AgentBasedGenerator::createStartAndExit()
{
	//finds the average room coordinates for the starting values
	avg_i = avg_i / num_rooms, avg_j = avg_j / num_rooms;

	/* used to determine relative room placement for spawning player
	index 0 and 1 are x,y coordinates index 2 is the index of the room in rooms vector*/
	int top_room[3] = { avg_i, avg_j, -1 },			bot_room[3] = { avg_i, avg_j, -1 };
	int left_room[3] = { avg_i, avg_j, -1 },		right_room[3] = { avg_i, avg_j, -1 };
	int top_right_room[3] = { avg_i, avg_j, -1 },	top_left_room[3] = { avg_i, avg_j, -1 };
	int bot_right_room[3] = { avg_i, avg_j, -1 },	bot_left_room[3] = { avg_i, avg_j, -1 };

	//iterate through the rooms and determine each extreme
	for (int n = 0; n < num_rooms; n++)
	{
		//top vs bottom check
		if (rooms[n][1] < top_room[1])
			top_room[0] = rooms[n][0], top_room[1] = rooms[n][1], top_room[2] = n;
		else if (rooms[n][1] > bot_room[1])
			bot_room[0] = rooms[n][0], bot_room[1] = rooms[n][1], bot_room[2] = n;

		//top right vs top left check
		if (rooms[n][1] < top_right_room[1] && rooms[n][0] > top_right_room[0])
			top_right_room[0] = rooms[n][0], top_right_room[1] = rooms[n][1], top_right_room[2] = n;
		else if (rooms[n][1] < top_left_room[1] && rooms[n][0] < top_left_room[0])
			top_left_room[0] = rooms[n][0], top_left_room[1] = rooms[n][1], top_left_room[2] = n;

		//bottom left vs bottom right
		if (rooms[n][1] > bot_right_room[1] && rooms[n][0] > top_right_room[0])
			bot_right_room[0] = rooms[n][0], bot_right_room[1] = rooms[n][1], bot_right_room[2] = n;
		else if (rooms[n][1] > bot_left_room[1] && rooms[n][0] < bot_left_room[0])
			bot_left_room[0] = rooms[n][0], bot_left_room[1] = rooms[n][1], bot_left_room[2] = n;

		//left vs right
		if (rooms[n][0] > right_room[0])
			right_room[0] = rooms[n][0], right_room[1] = rooms[n][1], right_room[2] = n;
		else if (rooms[n][0] < left_room[0])
			left_room[0] = rooms[n][0], left_room[1] = rooms[n][1], left_room[2] = n;
	}

	int extreme_rooms[8] = { top_room[2], bot_room[2], left_room[2], right_room[2], top_right_room[2], top_left_room[2], bot_right_room[2], bot_left_room[2] };

	//of the rooms selected above, determine which two are furthest apart 
	float max_dist = 0.0;
	int furthest_rooms[2] = { -1, -1 };
	for (int a = 0; a < 8; a++)
	{
		for (int b = a + 1; b < 8; b++)
		{
			if (extreme_rooms[a] == -1 || extreme_rooms[b] == -1)	continue;

			float dist = euclideanDistance(rooms[extreme_rooms[a]][0], rooms[extreme_rooms[a]][1], rooms[extreme_rooms[b]][0], rooms[extreme_rooms[b]][1]);

			if ( dist >= max_dist)
			{
				max_dist = dist;
				furthest_rooms[0] = extreme_rooms[a], furthest_rooms[1] = extreme_rooms[b];
			}
		}
	}

	//finds the smaller room of the furthest room and sets that to the player spawn point
	if (rooms[furthest_rooms[0]][2] * rooms[furthest_rooms[0]][3] <= rooms[furthest_rooms[1]][2] * rooms[furthest_rooms[1]][3])
	{
		player_room_index = furthest_rooms[0];
		exit_room_index = furthest_rooms[1];
	}
	else
	{
		player_room_index = furthest_rooms[1];
		exit_room_index = furthest_rooms[0];
	}
	//player's initial coordinates and exit coordinates are set to middle of respective rooms
	player_x = (rooms[player_room_index][0] + rooms[player_room_index][2] / 2);
	player_y = (rooms[player_room_index][1] + rooms[player_room_index][3] / 2);
	exit_x = (rooms[exit_room_index][0] + rooms[exit_room_index][2] / 2);
	exit_y = (rooms[exit_room_index][1] + rooms[exit_room_index][3] / 2);

	return player_room_index;
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