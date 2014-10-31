#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class XMLParser
{
public:
	XMLParser();
	~XMLParser();
	bool Initialize(string filename);
	void BuildLevel();

private:
	char* XMLDocument;
};

