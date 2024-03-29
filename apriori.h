#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <boost/functional/hash.hpp>
#include <omp.h>

// #include <unistd.h>

// sysconf(_SC_NPROCESSORS_ONLN);

using namespace std;

class my_hash {
public:
  size_t operator()(const vector<int> &v) const;
};



class apriori
{

public:

	float minsup;
	vector< vector<int> > T;
	vector< vector< vector<int> > > F;
	unordered_map< vector<int> , vector<int> , my_hash > reverse_hash;

	apriori(string filename, float X);
	~apriori();

	void printF(int i);
	void init_pass();
	bool isMatch( vector<int> f1 , vector<int> f2 );
	bool checkSubset(vector<int> subset , int k);
	bool toPrune(vector<int> c, int k);
	void copy_vec(vector<int> &c , vector<int> &x , int end);
	vector<vector<int> > candidate_gen(int k);
	bool isSubset(vector<int> Ck, vector<int> t );
	void write( string filename );
	void algo();
	
};