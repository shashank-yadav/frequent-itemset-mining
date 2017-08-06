#include "apriori.h"

using namespace std;

apriori::apriori(string filename, float X){
	
	ifstream f(filename.c_str());
	string line;
	while (getline(f, line))
	{
	    std::istringstream iss(line);
	    int temp;
	    std::vector<int> temp_v;

	    while( iss>>temp ){
	    	temp_v.push_back(temp);
	    }

	    T.push_back(temp_v);
	}

	minsup = X/100;
}

apriori::~apriori(){}

void apriori::init_pass(){
	unordered_map< int , int > count;

	for (int i = 0; i < T.size(); ++i){
		for (int j = 0; j < T[i].size(); ++j){
			if( count.find(T[i][j]) == count.end() ){
				count[ T[i][j] ] = 1;				
			}else{
				count[ T[i][j] ] += 1;
			}
		}
	}

	std::vector<int> temp_v;
	int n = T.size();

	for (auto it = count.begin(); it != count.end(); ++it){
		if( (float)it->second / (float)n >= minsup ){
			cout<<(float)it->second / (float)n<<endl;
			temp_v.push_back(it->first);
		}
	}

	sort(temp_v.begin() , temp_v.end() );

	F.push_back(temp_v);
}

void apriori::algo(){
	
	init_pass();

	for (int i = 1; F[i-1].size() > 0; ++i){
		//TODO
	}
}
