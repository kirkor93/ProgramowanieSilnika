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
	xml_node <> * root = doc.first_node();

	for (xml_node <> * branch_1 = root->first_node(); branch_1; branch_1 = branch_1->next_sibling()) 
	{ 
		int i_rowPositionX = Converter::StringToInt(branch_1->first_attribute()->value());
		int i_rowPositionY = Converter::StringToInt(branch_1->last_attribute()->value());

		for (xml_node <> * branch_2 = branch_1->first_node(); branch_2; branch_2 = branch_2->next_sibling())
		{
			xml_attribute <>* attribute = branch_2->first_attribute();
			int i_elementSizeX = Converter::StringToInt(attribute->value());
			attribute = attribute->next_attribute();
			int i_elementSizeY = Converter::StringToInt(attribute->value());
			attribute = attribute->next_attribute();
			int i_offset = Converter::StringToInt(attribute->value());
			attribute = attribute->next_attribute();
			wchar_t* i_textureName = Converter::StringToWchar(attribute->value());

			levelObjects.push_back(new GameObject(i_textureName, i_elementSizeX, i_elementSizeY, (i_rowPositionX + i_offset), i_rowPositionY, 1));

			//delete[]i_textureName;
		}

		
	}

	doc.clear();
}

GameObject* LevelBuilder::BuildPlayer()
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
	xml_node <> * root = doc.first_node();

	xml_attribute <>* attr = root->first_attribute();
	int sizeX = Converter::StringToInt(attr->value());
	attr = attr->next_attribute();
	int sizeY = Converter::StringToInt(attr->value());
	attr = attr->next_attribute();
	int positionX = Converter::StringToInt(attr->value());
	attr = attr->next_attribute();
	int positionY = Converter::StringToInt(attr->value());
	attr = attr->next_attribute();
	wchar_t* i_textureName = Converter::StringToWchar(attr->value());
	attr = attr->next_attribute();
	int animationFramesCount = Converter::StringToInt(attr->value());

	return new GameObject(i_textureName, sizeX, sizeY, positionX, positionY, animationFramesCount);
}

void LevelBuilder::BuildOther(vector<GameObject*> &otherObjects)
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
	xml_node <> * root = doc.first_node();

	for (xml_node <>* branch = root->first_node(); branch; branch = branch->next_sibling())
	{
		xml_attribute <>* attr = branch->first_attribute();
		int sizeX = Converter::StringToInt(attr->value());
		attr = attr->next_attribute();
		int sizeY = Converter::StringToInt(attr->value());
		attr = attr->next_attribute();
		int positionX = Converter::StringToInt(attr->value());
		attr = attr->next_attribute();
		int positionY = Converter::StringToInt(attr->value());
		attr = attr->next_attribute();
		wchar_t* i_textureName = Converter::StringToWchar(attr->value());
		attr = attr->next_attribute();
		int animationFramesCount = Converter::StringToInt(attr->value());

		otherObjects.push_back(new GameObject(i_textureName, sizeX, sizeY, positionX, positionY, animationFramesCount));
	}
}
