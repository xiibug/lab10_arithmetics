#include <iostream>
#include"Stack.h"
#include"Polish.h"

int main()
{
	char* s;
	s = "5+3";
	TPolish P;

	cout << P.Calculation(s);
	return 0;
}
