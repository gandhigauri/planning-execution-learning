#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <queue>
#include <set>
#include <list>
#include <map>
#include <limits>
#include <algorithm>

typedef std::vector<int> state;

struct node
{
	state st;
	node *parent;
	float f,g,h;
};

int gridSize;
std::vector<std::vector<int> > targetLocs;
std::vector<std::vector<int> > gridCost;

std::list<state> aStar(node*, node*);
std::list<node*> getSuccessors(node*);
float edgeCost(state, state);
//float computeHeuristic(node*, node*);

std::set<node*> openSet;
std::set<state> closedSet;
std::list<node*> successors;
std::list<state> path;
bool found_goal;