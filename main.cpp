#include "apriori.h"

using namespace std;

std::vector< std::vector<int> > T;

int main(int argc, char const *argv[])
{
	apriori a("retail.dat",2);
	a.algo();


	for (int i = 0; i < a.F.size(); ++i){
		a.printF(i);
	}
	return 0;
}