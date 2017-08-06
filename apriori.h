#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class apriori
{

	float minsup;
	vector< vector<int> > T;
	vector< vector<int> > F;

public:
	apriori(string filename, float X);
	~apriori();

	void init_pass();
	void algo();
	
};