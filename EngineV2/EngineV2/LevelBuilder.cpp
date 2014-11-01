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
	file.close();

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


			int i_rowPositionX = Converter::StringToInt(rowPositionX);
			int i_rowPositionY = Converter::StringToInt(rowPositionY);
			int i_elementSizeX = Converter::StringToInt(elementSizeX);
			int i_elementSizeY = Converter::StringToInt(elementSizeY);
			int i_offset = Converter::StringToInt(offset);

			wchar_t* i_textureName = Converter::StringToWchar(textureName);

			levelObjects.push_back(new GameObject(i_textureName, i_elementSizeX, i_elementSizeY, (i_rowPositionX + i_offset), i_rowPositionY));
		}

		
	}

	doc.clear();
}

