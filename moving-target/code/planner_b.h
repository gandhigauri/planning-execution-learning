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
#include <math.h>
#include <ctime>

typedef std::vector<int> state;

struct node
{
	state st;
	node *parent;
	float f,g,h;
};

int gridSize;
std::vector<node*> targetLocs, target2D;
std::vector<std::vector<float> > gridCost, gridH;

std::list<state> aStar(node*, std::vector<node*>);
std::list<node*> getSuccessors(node*);
float edgeCost(state, state);
float computeHeuristic(node*, std::vector<node*>);
std::vector<std::vector<float> > dijkstra(std::vector<node*>, int, std::vector<std::vector<float> >);
