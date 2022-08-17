#include <iostream>
#include "function.h"
using namespace std;

int main()
{
	char a[11];
	strcpy(a,"");
	cout<<strlen(a);
	char key = 0;
	nhapChuoi(a, 8, key,NO_SPACE);
	cout<<endl<<a;

	return 0;
}
