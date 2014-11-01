#include "Converter.h"

wchar_t* Converter::StringToWchar(string caption)
{
	wchar_t* wCharOutput = new wchar_t[1023];
	size_t* sizeOut = new size_t;
	size_t sizeInWords = 256;

	const char* cStr;
	cStr = caption.c_str();
	mbstowcs_s(sizeOut, wCharOutput, sizeInWords, cStr, strlen(cStr) + 1);

	return wCharOutput;
}

int Converter::StringToInt(string caption)
{
	return atoi(caption.c_str());
}