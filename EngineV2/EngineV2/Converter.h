#pragma once

#include <string>

using namespace std;

class Converter
{
public:
	static wchar_t* StringToWchar(string caption);
	static int StringToInt(string caption);
	static wchar_t* CopyWchar(wchar_t* caption);
};

