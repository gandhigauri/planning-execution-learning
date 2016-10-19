#include "planner_a.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
		cout<<"usage: "<< argv[0] <<" <filename>"<<endl;
	else
	{
		ifstream infile(argv[1]);
		node* start = new node;
		node* goal = new node;
		string STRING;
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
					vector<int> v;
					v.push_back(x);
					v.push_back(y);
					targetLocs.push_back(v);
				}

			}
		}
	}
}