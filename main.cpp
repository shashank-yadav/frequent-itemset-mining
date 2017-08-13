#include "apriori.h"

using namespace std;

std::vector< std::vector<int> > T;

int main(int argc, char const *argv[])
{
	if( argc != 3){
		cout<<"Usage: ./main inputFile minsup"<<endl;
		return 1;
	}


	float minsup = strtof( argv[2] , 0 );
	
	if( minsup < 0 || minsup > 100){
		cout<<"Invalid minsup"<<endl;
		return 1;
	}

	cout<<argv[1]<<" "<<minsup<<endl;

	apriori a( argv[1] , minsup );
	a.algo();	
	a.write( "2013CS50799.txt");

	return 0;
}