#include <iostream>
#include <queue>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>

typedef std::vector<int> state;
typedef int location;
typedef char object;
typedef char direction;

struct node
{
	state st;
	node *parent;/* data */
};

/*objects*/
direction directions[] = {'l', 'r', 'u', 'd'};
int total_objects, total_directions;

/*predicates*/
bool At(int, object, location, state);
bool CanMove(int, object, direction, state, int);
bool IsEmpty(location, state);
bool InBoard(location, int);

/*actions*/
state Move(int, object, direction, state, int);


