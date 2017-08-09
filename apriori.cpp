#include "apriori.h"

using namespace std;

class my_hash {
public:
  size_t operator()(const vector<int> &v) const {
    return boost::hash_value(v);
  }
};

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

	vector<int> temp_v;
	int n = T.size();

	for (auto it = count.begin(); it != count.end(); ++it){
		if( (float)it->second / (float)n >= minsup ){
			cout<<(float)it->second / (float)n<<endl;
			temp_v.push_back(it->first);
		}
	}

	sort(temp_v.begin() , temp_v.end() );

	vector< vector<int> > f;

	for (int i = 0; i < temp_v.size(); ++i){
		vector<int> temp = {temp_v[i]};
		f.push_back(temp);
	}
	
	F.push_back(f);
}

bool apriori::isMatch( vector<int> f1 , vector<int> f2 ){
	if( f1.size() != f2.size() )
		return false;

	for (int i = 0; i < f1.size() - 1; ++i){
		if( f1[i] != f2[i] )
			return false;
	}

	return true;
}

bool apriori::checkSubset(vector<int> subset , int k){
	for (int i = 0; i < F[k].size(); ++i){
		if( F[k][i] == subset )
			return true;
	}

	return false;	
}

bool apriori::toPrune(vector<int> c, int k){

	for (int i = 0; i < c.size(); ++i){
		vector<int> subset;

		for (int j = 0; j < c.size(); ++j){
			if( j != i)
				subset.push_back( c[j] );
		}

		if( !checkSubset(subset , k) )
			return true;
	}

	return false;
}

vector<vector<int> > apriori::candidate_gen(int k){
	vector<vector<int> > Ck;

	for (int i = 0; i < F[k].size(); ++i){
		for (int j = i+1; j < F[k].size(); ++j){
			
			vector<int> c;
			
			if ( isMatch( F[k][i] , F[k][j]) ){
				if ( F[k][i].back() < F[k][j].back() ){
					c = F[k][i];
					c.push_back(F[k][j].back());
				}else{
					c = F[k][j];
					c.push_back(F[k][i].back());
				}
				
				if( !toPrune( c , k)){
					Ck.push_back(c);
				}
			}		
		}
	}

	return Ck;
}

bool apriori::isSubset(vector<int> Ck, vector<int> t ){
	if( Ck.size() > t.size() ){
		return false;
	}

	int it = 0;
	for (int i = 0; i < t.size(); ++i){
		if ( Ck[it] == t[i] ){
			it ++;
		}
		if( it == Ck.size()  ){
			return true;
		}
	}

	return false;
}

void apriori::printF(int i){

	cout<<i<<" "<<F[i].size()<<endl;
	for (int j = 0; j < F[i].size(); ++j){
		for (int k = 0; k < F[i][j].size(); ++k){
			cout<<F[i][j][k]<<" ";
		}
		cout<<endl;
	}
}

void apriori::algo(){
	
	init_pass();

	unordered_map< vector<int> , int , my_hash > count;
	int n = T.size();

	for (int i = 1; F[i-1].size() > 0; ++i){

		vector<vector<int> > Ck = candidate_gen(i-1);

		for (int j = 0; j < T.size(); ++j){
			for (int k = 0; k < Ck.size(); ++k){
				if (isSubset( Ck[k] , T[j] ) ){
					
					if( count.find( Ck[k] ) == count.end() ){
						count[ Ck[k] ] = 1;				
					}else{
						count[ Ck[k] ] += 1;
					}
				}
			}
		}

		vector< vector<int> > temp_v;
		
		for (int j = 0; j < Ck.size(); ++j){
			if( (float)count[ Ck[j] ]/(float)n >= minsup ){
				temp_v.push_back( Ck[j] );
			}
		}

		F.push_back( temp_v );		
	}
}
