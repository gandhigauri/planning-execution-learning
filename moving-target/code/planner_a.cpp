#include "planner_a.h"

using namespace std;

std::list<state> aStar(node* start_node, std::vector<node*> goals)
{
	cout<<"starting plan"<<endl;
	node* current = NULL;
	node* last_node = NULL;
	start_node->g = 0;
	for (int i = 0; i < goals.size(); i++)
		goals[i]->g = numeric_limits<float>::infinity();
	start_node->h = 0;//computeHeuristic(start_node, goal_node);
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
			if (equal(current->st.begin(),current->st.end(),goals[i]->st.begin()))//if (isEqual(current->st, goal_node->st))
			{
				last_node = current;
				cout<<"found goal"<<" x "<<current->st[0]<<" y "<<current->st[1]<<" t "<<current->st[2]<<endl;
				found_goal = 1;
				break;
			}
		if (found_goal)
			break;
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
			neighbor->h = 0;//computeHeuristic(neighbor, goal_node);
			neighbor->f = neighbor->g + neighbor->h;
		}
	
	}
	if (!found_goal)
	{
		cout<<"plan not complete"<<endl;
		return path;
	}
	else
	{
		cout<<"making final plan"<<endl;
		cout<<"total cost of plan "<<last_node->g<<endl;
		while (last_node->st != start_node->st)
		{
			path.push_front(last_node->st);
			if (last_node->parent != NULL)
				last_node = last_node->parent;
		}
		cout<<"returning plan"<<endl;
		cout<<"Total states explored "<<total_states<<endl;
		path.push_front(start_node->st);
		int pathLen = path.size();//0;
		cout<<"total path length "<<pathLen<<endl;
		for (std::list<state>::iterator itr = path.begin(); itr != path.end(); itr ++)
		{
			state next_state = *itr;
			cout<<" x "<<next_state[0]<<" y "<<next_state[1]<<" t "<<next_state[2]<<endl;
		}
		return path;
		
	}
}

std::list<node*> getSuccessors(node* current)
{
	std::list<node*> neighbor_states;
	node* left = new node;
	left->st.push_back(current->st[0]);
	left->st.push_back(current->st[1]-1);
	left->st.push_back(current->st[2]+1);
	if (left->st[2]<targetLocs.size())
	if (left->st[1]>=0)
		neighbor_states.push_back(left);
	node* right = new node;
	right->st.push_back(current->st[0]);
	right->st.push_back(current->st[1]+1);
	right->st.push_back(current->st[2]+1);
	if (right->st[2]<targetLocs.size())
	if (right->st[1]<gridSize)
		neighbor_states.push_back(right);
	node* up = new node;
	up->st.push_back(current->st[0]-1);
	up->st.push_back(current->st[1]);
	up->st.push_back(current->st[2]+1);
	if (up->st[2]<targetLocs.size())
	if (up->st[0]>=0)
		neighbor_states.push_back(up);
	node* down = new node;
	down->st.push_back(current->st[0]+1);
	down->st.push_back(current->st[1]);
	down->st.push_back(current->st[2]+1);
	if (down->st[2]<targetLocs.size())
	if (down->st[0]<gridSize)
		neighbor_states.push_back(down);	
	node* same = new node;
	same->st.push_back(current->st[0]);
	same->st.push_back(current->st[1]);
	same->st.push_back(current->st[2]+1);
	if (same->st[2]<targetLocs.size())
		neighbor_states.push_back(same);
	return neighbor_states;
}

float edgeCost(state start, state goal)
{
	return gridCost[goal[0]][goal[1]];
}

float computeHeuristic(node* start, node* goal)
{
	//float h = dijkstra(start, goal);
	//return h;
	return sqrt(pow(start->st[0]-goal->st[0],2) + pow(start->st[1]-goal->st[1],2));
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		cout<<"usage: "<< argv[0] <<" <filename>"<<endl;
	else
	{
		ifstream infile(argv[1]);
		node* start = new node;
		string STRING;
		int targetStep = 0;
		while (getline(infile, STRING))
		{
			if (STRING.find("N")!=STRING.npos)
			{
				string n;
				getline(infile, n);
				gridSize = atoi(n.c_str());
			}
			if (STRING.find("R")!=STRING.npos)
			{
				string r;
				getline(infile, r);
				int x = atoi(r.substr(0,r.find(",")).c_str());
				int y = atoi(r.substr(r.find(",")+1).c_str());
				start->st.push_back(x);
				start->st.push_back(y);
				start->st.push_back(0);
			}
			if (STRING.find("T")!=STRING.npos)
			{
				//string b;
				while (STRING.find("B")==STRING.npos)
				{
					string t;
					getline(infile, t);
					if (t.find("B")!=STRING.npos){
						for (int i = 0; i < gridSize; i++)
						{
							getline(infile, t);
							istringstream ss(t);
							vector<int> rowCost;
							while (ss)
							{
								if (!getline(ss,t,',')) break;
								int c = atoi(t.c_str());
								rowCost.push_back(c);

							}
							gridCost.push_back(rowCost);
						}
						break;
					}
					int x = atoi(t.substr(0,t.find(",")).c_str());
					int y = atoi(t.substr(t.find(",")+1).c_str());
					node* goal = new node;
					//vector<int> v;
					goal->st.push_back(x);
					goal->st.push_back(y);
					goal->st.push_back(targetStep);
					targetLocs.push_back(goal);
					targetStep = targetStep + 1;
				}

			}
		}
		aStar(start, targetLocs);
	}
}