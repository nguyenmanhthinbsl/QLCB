#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	int i = 123555;
	stringstream ss;
	ss<<i;	
	string str = ss.str();
	cout<<str;
	return 0;
}
