#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <boost/functional/hash.hpp>

using namespace std;

class apriori
{

public:

	float minsup;
	vector< vector<int> > T;
	vector< vector< vector<int> > > F;

	apriori(string filename, float X);
	~apriori();

	void printF(int i);
	void init_pass();
	bool isMatch( vector<int> f1 , vector<int> f2 );
	bool checkSubset(vector<int> subset , int k);
	bool toPrune(vector<int> c, int k);
	vector<vector<int> > candidate_gen(int k);
	bool isSubset(vector<int> Ck, vector<int> t );
	void algo();
	
};