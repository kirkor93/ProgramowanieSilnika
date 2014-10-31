#include "XMLParser.h"

int main()
{
	XMLParser myParser;
	myParser.Initialize("./Level.xml");
	myParser.BuildLevel();

	int a;
	cin >> a;
	return 0;
}