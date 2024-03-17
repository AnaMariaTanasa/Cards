#include <iostream>
#include <cstring>
#include "Cards.h"
using namespace std;
int main()
{

	char s[][8] = { "PICA","CUPA","CARO","TREFLA" };
	Game g = { 0 };
	char* command = new char;
	help();
	while (1)
	{
		cout << "Type a command" << '\n';
		cin >> command;
		meniu(command, g, s);
	}
	delete command;
	command = 0;
	return 0;
}