#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>

typedef std::vector<int> state;

struct node
{
	state st;
	node *parent;/* data */
};

int gridSize;
std::vector<std::vector<int> > targetLocs;
std::vector<std::vector<int> > gridCost;