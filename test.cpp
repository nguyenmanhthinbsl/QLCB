#include <iostream>
#include "function.h"
using namespace std;

int main()
{
	Day_time a = Time_now();
	cout<<tocharDate(a);
	char key = 0;
	input_date(a, key);
	return 0;
}
