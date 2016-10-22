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

typedef std::vector<int> state;

struct node
{
	state st;
	node *parent;
	float f,g,h;
};

std::list<node*> getDijkstraSuccessors(node*, int);
float edgeCostDijkstra(state, state, std::vector<std::vector<float> >);
