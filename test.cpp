#include <iostream>
#include "sub_function.h"
using namespace std;

int main()
{
	char input;
	do{
		input=getch();
		cout<<(int)input<<endl;
	}while(input!=ENTER);
	return 0;
}
