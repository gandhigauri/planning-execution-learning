#include "dijkstra.h"

using namespace std;

float dijkstra(node* start_node, std::vector<node*> goals, int gridSize, std::vector<std::vector<float> > gridCost)
{
	cout<<"starting"<<endl;
	std::set<node*> openSet;
	std::set<state> closedSet;
	std::list<node*> successors;
	bool found_goal;
	node* current = NULL;
	node* last_node = NULL;
	start_node->g = 0;
	start_node->h = 0;
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
		for (int i = 0; i < goals.size(); i++)
			if ((current->st[0]==goals[i]->st[0]) && (current->st[1]==goals[i]->st[1]))//if (isEqual(current->st, goal_node->st))
			{
				last_node = current;
				found_goal = 1;
				break;
			}
		if (found_goal)
			break;
		openSet.erase(current);
		closedSet.insert(current->st);
		total_states = total_states + 1;
		//cout<<"total_states"<<total_states<<endl;
		successors = getDijkstraSuccessors(current, gridSize);
		for (std::list<node*>::iterator itr = successors.begin(); itr != successors.end(); itr ++)
		{
			node* neighbor = *itr;
			if (closedSet.find(neighbor->st) != closedSet.end())
				continue;
			float neighbor_g = current->g + edgeCostDijkstra(current->st, neighbor->st, gridCost);
			if (openSet.find(neighbor) == openSet.end())
				openSet.insert(neighbor);
			else if (neighbor_g >= neighbor->g)
				continue;
			neighbor->parent = current;
			neighbor->g = neighbor_g;
			neighbor->h = 0;
			neighbor->f = neighbor->g + neighbor->h;
		}
	
	}
	return last_node->g;
}

std::list<node*> getDijkstraSuccessors(node* current, int gridSize)
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

inline float edgeCostDijkstra(state start, state goal, std::vector<std::vector<float> > gridCost)
{
	return gridCost[goal[0]][goal[1]];
}
