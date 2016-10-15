#include "breadth_first.h"

using namespace std;

std::list<state> bfs(node* start_node, node* goal_node, int board_dim, std::vector<char>& spaceships)
{
	cout<<"starting plan"<<endl;
	found_goal = 0;
	node* item = NULL;
	node* last_node = NULL;
	open_list.push(start_node);
	int total_states = 0;
	while (!open_list.empty())
	{
		item = open_list.front();
		open_list.pop();
		total_states = total_states + 1;
		if (closed_list.find(item->st) == closed_list.end())
		{
			for (int i = 0 ; i < item->st.size(); i++)
			//cout<<" new extended state "<<item->st[i];
			//cout<<endl;
			closed_list.insert(item->st);
			successors = get_successors(item, board_dim, spaceships);
			for (std::list<node*>::iterator itr = successors.begin(); itr != successors.end(); itr ++)
			{
				node* temp = *itr;
				temp->parent = item;
				if (temp->st[0] == goal_node->st[0])
					{
						last_node = temp;
						found_goal = 1;
						cout<<"found goal"<<endl;
						break;						
					}
				else
					if (closed_list.find(temp->st) == closed_list.end())
						open_list.push(*itr);			
						//cout<<"pushed successor to open list"<<endl; 	
			}			
		}
		if (found_goal)
			break;	
	}
	cout<<"making final plan"<<endl;
	while (last_node && last_node->st != start_node->st)
	{
		if (last_node->st == goal_node->st)
			path.push_front(goal_node->st);
		else
			path.push_front(last_node->st);
		if (last_node->parent != NULL)
			last_node = last_node->parent;
	}
	cout<<"returning plan"<<endl;
	cout<<"Total states explored "<<total_states<<endl;
	path.push_front(start_node->st);
	int num_steps = 0;
	for (std::list<state>::iterator itr = path.begin(); itr != path.end(); itr ++)
	{
		state next_state = *itr;
		num_steps = num_steps + 1;
		cout<<"t = "<<num_steps;
		for (int i = 0; i < next_state.size(); i++)
		{
			int spaceship_location = next_state[i];
			int grid_coordinates[2] = {floor(spaceship_location%board_dim), (spaceship_location/board_dim)};
			cout<<"  spaceship "<<i<<" at ("<<grid_coordinates[0]<<","<<grid_coordinates[1]<<")";
			
		}
		cout<<endl;
	}
	return path;
}

std::list<node*> get_successors(node* item, int board_dim, std::vector<char>& spaceships)
{
	std::list<node*> neighbor_states;
	neighbor_states = find_feasible_neighbors(item, board_dim, spaceships);
	return neighbor_states;
}

int locationToId(int board_dim, int x, int y)
{
	return ((y*board_dim) + x);
}


int main(int argc, char *argv[])
{
	cout<<"initializing"<<endl;
	if (argc != 2)
		cout<<"Please pass the arguments"<<endl;
	else
	{
		ifstream infile(argv[1]);
	    string STRING;
	    node* start = new node;
		node* goal = new node;
		int problem_num;
		while (getline(infile, STRING))
		{
			string prob = "problem ";
			if (STRING.find(prob)!=STRING.npos)
				problem_num = atoi(STRING.substr(prob.length()).c_str());
			string bd = "board dimensions ";
			if (STRING.find(bd)!=STRING.npos)
				dim_board = atoi(STRING.substr(bd.length()).c_str());
			string num_ob = "number of objects ";
			if (STRING.find(num_ob)!=STRING.npos)
				num_objects = atoi(STRING.substr(num_ob.length()).c_str());
			string ob = "spaceships ";
			if (STRING.find(ob)!=STRING.npos)
				for (int i = 0; i < num_objects; i++)
					spaceships.push_back(STRING.substr(ob.length()+i)[0]);
			string sr = "start ";
			if (STRING.find(sr)!=STRING.npos)
			{
				string locs = STRING.substr(sr.length());
				for (int i = 0; i < num_objects; i++)
					if (locs.find(spaceships[i])!=locs.npos)
					{
						int len_x = locs.find_first_of(",",locs.find(spaceships[i])) - locs.find_first_of(" ",locs.find(spaceships[i])) - 1;
						int len_y;
						if (i!=(num_objects - 1))
							len_y = locs.find_last_of(" ",locs.find(spaceships[i+1])) - locs.find_first_of(",",locs.find(spaceships[i])) - 1;
						else
							len_y = locs.substr(locs.find_first_of(",",locs.find(spaceships[i]))).length()-1;
						int x = atoi(locs.substr(locs.find(spaceships[i])+2,len_x).c_str());
						int y = atoi(locs.substr(locs.find_first_of(",",locs.find(spaceships[i]))+1,len_y).c_str());
						start->st.push_back(locationToId(dim_board,x,y));
					}
			}
			string gl = "goal ";
			if (STRING.find(gl)!=STRING.npos)
			{
				string locs = STRING.substr(gl.length());
				for (int i = 0; i < num_objects; i++)
					if (locs.find(spaceships[i])!=locs.npos)
					{
						int len_x = locs.find_first_of(",",locs.find(spaceships[i])) - locs.find_first_of(" ",locs.find(spaceships[i])) - 1;
						int len_y;
						if (i!=(num_objects - 1))
							len_y = locs.find_last_of(" ",locs.find(spaceships[i+1])) - locs.find_first_of(",",locs.find(spaceships[i])) - 1;
						else
							len_y = locs.substr(locs.find_first_of(",",locs.find(spaceships[i]))).length()-1;
						int x = atoi(locs.substr(locs.find(spaceships[i])+2,len_x).c_str());
						int y = atoi(locs.substr(locs.find_first_of(",",locs.find(spaceships[i]))+1,len_y).c_str());
						goal->st.push_back(locationToId(dim_board,x,y));
					}
			}
				
		}
		cout<<"solving lunar lockout puzzle number "<<problem_num<<endl;
		for (int i = 0; i < num_objects; i++)
		{
			cout<<"spaceship "<<i<<" : "<<spaceships[i]<<" ";
		}
		cout<<endl;
		bfs(start,goal, dim_board, spaceships);
		}
}

