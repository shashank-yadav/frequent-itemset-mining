#include "apriori.h"

using namespace std;

size_t my_hash::operator()(const vector<int> &v) const {
return boost::hash_value(v);
}


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

			vector<int> v =  {T[i][j]};
			reverse_hash[ v ].push_back(i);
		}
	}

	vector<int> temp_v;
	int n = T.size();

	for (auto it = count.begin(); it != count.end(); ++it){
		if( (float)it->second / (float)n >= minsup ){
			// cout<<(float)it->second / (float)n<<endl;
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
		
		vector<int> subset(c.size()-1 , 0);
		int it = 0;

		for (int j = 0; j < c.size(); ++j){
			if( j != i)
				subset[it++]  =  c[j];
		}

		if( !checkSubset(subset , k) )
			return true;
	}

	return false;
}

void apriori::copy_vec(vector<int> &c , vector<int> &x , int end){
	
	for( int i = 0; i < x.size(); i++)
		c[i] = x[i];

	c[ c.size() - 1] = end;
}

vector<vector<int> > apriori::candidate_gen(int k){
	vector<vector<int> > Ck;

	unordered_map< vector<int> , vector<int> , my_hash > new_reverse_hash;
	
	for (int i = 0; i < F[k].size(); ++i){
		for (int j = i+1; j < F[k].size(); ++j){
			
			vector<int> c( k+2, 0 );
			
			if ( isMatch( F[k][i] , F[k][j]) ){
				if ( F[k][i].back() < F[k][j].back() ){
					copy_vec( c , F[k][i] , F[k][j].back() );
					// c = F[k][i];
					// c.push_back(F[k][j].back());
				}else{
					copy_vec( c , F[k][j] , F[k][i].back() );
					// c = F[k][j];
					// c.push_back(F[k][i].back());
				}

				vector<int> &intersec = new_reverse_hash[ c ];
				set_intersection( reverse_hash[F[k][i]].begin() , reverse_hash[F[k][i]].end(), reverse_hash[F[k][j]].begin() , reverse_hash[F[k][j]].end(),   std::back_inserter(intersec) );

				// new_reverse_hash[ c ] = intersec;

				float support = (float)intersec.size()/(float)T.size();
				if( support >= minsup && !toPrune( c , k)){
					Ck.push_back(c);
				}
			}		
		}
	}

	reverse_hash = new_reverse_hash;

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
			cout<<F[i][j][k];
		}
		cout<<endl;
	}
}


void apriori::write( string filename ){
	
	ofstream f(filename.c_str());

	for( int i = 0; i < F.size(); i++ ){
		for (int j = 0; j < F[i].size(); ++j){
			for (int k = 0; k < F[i][j].size(); ++k){
				f<<F[i][j][k];
				if( k != F[i][j].size()-1)
					f<<" ";
			}
			f<<'\n';
		}
	}

	f.close();
}

void apriori::algo(){
	
	init_pass();
	// cout<<"init_pass"<<endl;

	unordered_map< vector<int> , int , my_hash > count;
	int n = T.size();

	for (int i = 1; F[i-1].size() > 0; ++i){

		vector<vector<int> > Ck = candidate_gen(i-1);
		// cout<<"candidate_gen "<<i-1<<endl;

		vector< vector<int> > temp_v;
		
		// cout<<Ck.size()<<endl;

		for (int j = 0; j < Ck.size(); ++j){
			temp_v.push_back( Ck[j] );
		}

		F.push_back( temp_v );
		
		// cout<<"end1 "<<i-1<<endl;

	}
}
