#include "LevelBuilder.h"


LevelBuilder::LevelBuilder()
{
}

LevelBuilder::~LevelBuilder()
{
	delete XMLDocument;
}

bool LevelBuilder::Initialize(string filename)
{
	ifstream file(filename);
	if (file.bad())
		return false;

	filebuf * pbuf = file.rdbuf();
	long fileSize = pbuf->pubseekoff(0, ios::end, ios::in);
	file.seekg(0);
	XMLDocument = new char[fileSize + 1];
	file.read(XMLDocument, fileSize);

	return true;
}

void LevelBuilder::BuildLevel(vector<GameObject*> &levelObjects)
{
	xml_document <> doc;
	try 
	{
		doc.parse < 0 >(this->XMLDocument); 
	}
	catch (parse_error p) 
	{
		p.what();
	}

	string rowPositionX;
	string rowPositionY;
	string elementSizeX;
	string elementSizeY;
	string offset;
	string textureName;

	xml_node <> * root = doc.first_node();

	for (xml_node <> * branch_1 = root->first_node(); branch_1; branch_1 = branch_1->next_sibling()) 
	{ 
		rowPositionX = branch_1->first_attribute()->value();
		rowPositionY = branch_1->last_attribute()->value();

		for (xml_node <> * branch_2 = branch_1->first_node(); branch_2; branch_2 = branch_2->next_sibling())
		{
			xml_attribute <>* attribute = branch_2->first_attribute();
			elementSizeX = attribute->value();
			attribute = attribute->next_attribute();
			elementSizeY = attribute->value();
			attribute = attribute->next_attribute();
			offset = attribute->value();
			attribute = attribute->next_attribute();
			textureName = attribute->value();


			int i_rowPositionX = atoi(rowPositionX.c_str());
			int i_rowPositionY = atoi(rowPositionY.c_str());
			int i_elementSizeX = atoi(elementSizeX.c_str());
			int i_elementSizeY = atoi(elementSizeY.c_str());
			int i_offset = atoi(offset.c_str());

			wchar_t wCharOutput[1023];
			size_t* sizeOut = new size_t;
			size_t sizeInWords = 256;

			const char* cStr;
			cStr = textureName.c_str();
			mbstowcs_s(sizeOut, wCharOutput, sizeInWords, cStr, strlen(cStr) + 1);

			levelObjects.push_back(new GameObject(wCharOutput, i_elementSizeX, i_elementSizeY, (i_rowPositionX + i_offset), i_rowPositionY));
		}

		
	}
}

