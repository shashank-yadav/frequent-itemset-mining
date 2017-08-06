#include "apriori.h"

using namespace std;

std::vector< std::vector<int> > T;

int main(int argc, char const *argv[])
{
	apriori a("retail.dat",2);
	a.init_pass();	
	return 0;
}