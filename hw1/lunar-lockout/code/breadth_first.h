#include <iostream>
#include <cstdlib>
#include <queue>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>

typedef std::vector<int> state;

struct node
{
	state st;
	node *parent;/* data */
};

std::queue<node*> open_list;
std::set<state> closed_list;
std::list<node*> successors;
std::list<state> path;
bool found_goal;

std::list<state> bfs(node*, node*, int, std::vector<char>&);
std::list<node*> get_successors(node*, int, std::vector<char>&);
std::list<node*> find_feasible_neighbors(node*, int, std::vector<char>&);
int locationToId(int, int, int);

int dim_board;
int num_objects;
std::vector<char> spaceships;