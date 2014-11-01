#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "./RapidXML/rapidxml.hpp"

#include "GameObject.h"
#include "Converter.h"

using namespace std;
using namespace rapidxml;

class LevelBuilder
{
public:
	LevelBuilder();
	~LevelBuilder();
	bool Initialize(string filename);
	void BuildLevel(vector<GameObject*> &levelObjects);

private:
	char* XMLDocument;
};

