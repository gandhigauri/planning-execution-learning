#include "representation.h"

using namespace std;

std::list<node*> find_feasible_neighbors(node* item, int board_dim, std::vector<char>& spaceships)
{
	std::list<node*> neighbor_states;
	total_objects = spaceships.size();
	total_directions = sizeof(directions)/sizeof(directions[0]);
	for (int i = 0; i < total_objects; i++)
	{
		for (int j = 0; j < total_directions; j++)
		{
			if (CanMove(i, spaceships[i], directions[j], item->st, board_dim))
			{
				node* new_state = new node;
				new_state->st = Move(i, spaceships[i], directions[j], item->st, board_dim);
				neighbor_states.push_back(new_state);
			}
		} 
	}
	return neighbor_states;
}

/*predicates*/
bool At(int spaceship_index, object spaceship, location grid_position, state current_state)
{
	if (current_state[spaceship_index] == grid_position)
		return true;
	else
		return false;
}

bool CanMove(int spaceship_index, object spaceship, direction dir, state current_state, int board_dim)
{
	location spaceship_location = current_state[spaceship_index];
	int grid_coordinates[] = {floor(spaceship_location%board_dim), (spaceship_location/board_dim)};
	bool dir_flag = 0;
	switch (dir)
	{
		case 'l' : 
		{
			while (spaceship_location>(grid_coordinates[1]*5) && (InBoard(spaceship_location, board_dim)))
			{
				grid_coordinates[0] = grid_coordinates[0] - 1;
				spaceship_location = (grid_coordinates[0]) + (grid_coordinates[1])*board_dim;
				if (!IsEmpty(spaceship_location, current_state))
				{
					dir_flag = 1;
					break;
				}
			} break;
		}
		case 'r' :
		{
			while (spaceship_location<((grid_coordinates[1]+1)*board_dim-1) && (InBoard(spaceship_location, board_dim)))
			{
				grid_coordinates[0] = grid_coordinates[0] + 1;
				spaceship_location = (grid_coordinates[0]) + ((grid_coordinates[1])*board_dim);
				if (!IsEmpty(spaceship_location, current_state))
				{
					dir_flag = 1;
					break;
				}
			} break;
		}		
		case 'u' :
		{
			while (spaceship_location<((board_dim-1)*board_dim + grid_coordinates[0]) && (InBoard(spaceship_location, board_dim)))
			{
				grid_coordinates[1] = grid_coordinates[1] + 1;
				spaceship_location = (grid_coordinates[0]) + ((grid_coordinates[1])*board_dim);
				if (!IsEmpty(spaceship_location, current_state))
				{
					dir_flag = 1;
					break;
				}
			} break;
		}		
		case 'd' :
		{
			while (spaceship_location>(grid_coordinates[0]) && (InBoard(spaceship_location, board_dim)))
			{
				grid_coordinates[1] = grid_coordinates[1] - 1;
				spaceship_location = (grid_coordinates[0]) + ((grid_coordinates[1])*board_dim);
				if (!IsEmpty(spaceship_location, current_state))
				{
					dir_flag = 1;
					break;
				}
			} break;
		}
		default : cout<<"invalid direction"<<endl;
	}
	if (dir_flag)
		return true;
	else
		return false;
}

bool IsEmpty(location grid_position, state current_state)
{
	if (std::find(current_state.begin(), current_state.end(), grid_position) == current_state.end())
		return true;
	else
		return false;
}

bool InBoard(location grid_position, int board_dim)
{
	int grid_coordinates[] = {floor(grid_position%board_dim), (grid_position/board_dim)};
	if ((grid_coordinates[0]<0) || (grid_coordinates[0]>(board_dim-1)) || (grid_coordinates[1]<0) || (grid_coordinates[1]>(board_dim-1)))
		return false;
	else
		return true;
}


/*actions*/
state Move(int spaceship_index, object spaceship, direction dir, state current_state, int board_dim)
{
	location spaceship_location = current_state[spaceship_index];
	state new_state = current_state;
	bool feasible_move = 0;
	switch (dir)
	{
		case 'l' : 
		{
			while (IsEmpty(spaceship_location - 1, current_state))
			{
				new_state[spaceship_index] = spaceship_location - 1;
				spaceship_location = spaceship_location - 1;
				feasible_move = 1;
				
			} break;
		}
		case 'r' :
		{
			while (IsEmpty(spaceship_location + 1, current_state))
			{
				new_state[spaceship_index] = spaceship_location + 1;
				spaceship_location = spaceship_location + 1;
				feasible_move = 1;
			} break;
		}		
		case 'u' :
		{
			while (IsEmpty(spaceship_location + board_dim, current_state))
			{
				new_state[spaceship_index] = spaceship_location + board_dim;
				spaceship_location = spaceship_location + board_dim;
				feasible_move = 1;
			} break;
		}		
		case 'd' :
		{
			while (IsEmpty(spaceship_location - board_dim, current_state))
			{
				new_state[spaceship_index] = spaceship_location - board_dim;
				spaceship_location = spaceship_location - board_dim;
				feasible_move = 1;
			} break;
		}
		default : cout<<"invalid direction"<<endl;
	}
	if (feasible_move)
		return new_state;
}



