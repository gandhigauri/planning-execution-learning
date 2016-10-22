#include "planner_a.h"

using namespace std;

float dijkstra(node* start_node, node* goal_node)
{
	cout<<"starting plan"<<endl;
	node* current = NULL;
	node* last_node = NULL;
	start_node->g = 0;
	goal_node->g = numeric_limits<float>::infinity();
	start_node->h = computeHeuristic(start_node, goal_node);
	start_node->f = start_node->g + start_node->h;
	openSet.insert(start_node);
	int total_states = 0;
	found_goal = 0;
	while (!openSet.empty())
	{	
		float minF = numeric_limits<float>::max();
		node* temp;
		for (set<node*>::iterator itr = openSet.begin(); itr!=openSet.end(); itr++)
		{
			temp = *itr;
			if (temp->f < minF)
			{
				minF = temp->f;
				current = temp;
			}
		}
		if (equal(current->st.begin(),current->st.end(),goal_node->st.begin()))//if (isEqual(current->st, goal_node->st))
		{
			last_node = current;
			cout<<"found goal"<<endl;
			found_goal = 1;
			break;
		}
		openSet.erase(current);
		closedSet.insert(current->st);
		total_states = total_states + 1;
		successors = getSuccessors(current);
		for (std::list<node*>::iterator itr = successors.begin(); itr != successors.end(); itr ++)
		{
			node* neighbor = *itr;
			if (closedSet.find(neighbor->st) != closedSet.end())
				continue;
			float neighbor_g = current->g + edgeCost(current->st, neighbor->st);
			if (openSet.find(neighbor) == openSet.end())
				openSet.insert(neighbor);
			else if (neighbor_g >= neighbor->g)
				continue;
			neighbor->parent = current;
			neighbor->g = neighbor_g;
			neighbor->h = computeHeuristic(neighbor, goal_node);
			neighbor->f = neighbor->g + neighbor->h;
		}
	
	}
	if (!found_goal)
		cout<<"plan not complete"<<endl;
	cout<<"making final plan"<<endl;
	cout<<"total cost of plan "<<last_node->g<<endl;
	while (last_node->st != start_node->st)
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
	int num_steps = path.size();//0;
	cout<<"total time steps "<<num_steps<<endl;
	/*for (std::list<state>::iterator itr = path.begin(); itr != path.end(); itr ++)
	{
		state next_state = *itr;
		num_steps = num_steps + 1;
		cout<<"t = "<<num_steps;
		cout<<endl;
	}*/
	return last_node->g;
}

std::list<node*> getSuccessors(node* current)
{
	std::list<node*> neighbor_states;
	node* left = new node;
	left->st.push_back(current->st[0]);
	left->st.push_back(current->st[1]-1);
	if (left->st[1]>=0)
		neighbor_states.push_back(left);
	node* right = new node;
	right->st.push_back(current->st[0]);
	right->st.push_back(current->st[1]+1);
	if (right->st[1]<gridSize)
		neighbor_states.push_back(right);
	node* up = new node;
	up->st.push_back(current->st[0]-1);
	up->st.push_back(current->st[1]);
	if (up->st[0]>=0)
		neighbor_states.push_back(up);
	node* down = new node;
	down->st.push_back(current->st[0]+1);
	down->st.push_back(current->st[1]);
	if (down->st[0]<gridSize)
		neighbor_states.push_back(down);	
	return neighbor_states;
}

float edgeCost(state start, state goal)
{
	return gridCost[goal[0]][goal[1]];
}

float computeHeuristic(node* start, node* goal)
{
	return 0;
}

