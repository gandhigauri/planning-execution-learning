#include "dijkstra.h"

using namespace std;

std::vector<std::vector<float> > dijkstra(std::vector<node*> goals, int gridSize, std::vector<std::vector<float> > gridCost)
{
	cout<<"starting"<<endl;
	std::set<node*> openSet;
	std::map<state,bool> closedCheck, openCheck;
	std::list<node*> successors;
	std::map<state,float> gmap;
	node* current = NULL;
	std::vector<std::vector<float> > mapH;
	for (int r = 0; r < gridSize; r++)
	{	
		vector<float> rowCost;
		for (int c = 0; c < gridSize; c++)
			rowCost.push_back(0);
		mapH.push_back(rowCost);
	}

	for (int i = 0; i < goals.size(); i++)
	{	
		goals[i]->g = 0;//gridCost[goals[i]->st[0]][goals[i]->st[1]];
		gmap[goals[i]->st] = 0;//gridCost[goals[i]->st[0]][goals[i]->st[1]];
		if (!openCheck[goals[i]->st])
		{
			openSet.insert(goals[i]);
			openCheck[goals[i]->st] = 1;
		}
	}
	while (!openSet.empty())
	{	
		float minG = numeric_limits<float>::max();
		node* temp;

		for (set<node*>::iterator itr = openSet.begin(); itr!=openSet.end(); itr++)
		{
			temp = *itr;
			if (temp->g < minG)
			{
				minG = temp->g;
				current = temp;
			}
		}

		
		openSet.erase(current);

		openCheck[current->st] = 0;

		closedCheck[current->st] = 1;
		if (closedCheck.size()%1000 == 0)
			cout<<closedCheck.size()<<endl;
		successors = getDijkstraSuccessors(current, gridSize);
		for (std::list<node*>::iterator itr = successors.begin(); itr != successors.end(); itr ++)
		{
			node* neighbor = *itr;
			if (closedCheck[neighbor->st])
				continue;
			float neighbor_g = current->g + edgeCostDijkstra(current->st, neighbor->st, gridCost);
			if (!openCheck[neighbor->st])
			{
				openSet.insert(neighbor);
				openCheck[neighbor->st] = 0;
				neighbor->g = neighbor_g;
				gmap[neighbor->st] = neighbor_g;				
			}
			else if (neighbor_g >= neighbor->g)
				continue;
			openSet.insert(neighbor);
			openCheck[neighbor->st] = 0;
			neighbor->g = neighbor_g;
			gmap[neighbor->st] = neighbor_g;

		}
	
	}
	for(map<state, float>::iterator itr = gmap.begin(); itr!=gmap.end(); itr++)
	{
		mapH[itr->first[0]][itr->first[1]] = itr->second;
	}		
	return mapH;
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
