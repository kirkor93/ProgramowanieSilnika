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

wchar_t* Converter::CopyWchar(wchar_t* caption)
{
	int j = 1;
	for (int i = 0; caption[i] != '\0'; i += 1)
	{
		j++;
	}

	wchar_t *output = new wchar_t[j+1];
	for (int i = 0; i < j + 2; i += 1)
	{
		output[i] = caption[i];
	}

	return output;
}
