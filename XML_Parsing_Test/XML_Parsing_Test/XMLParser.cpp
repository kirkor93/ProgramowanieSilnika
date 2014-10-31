#include "XMLParser.h"


XMLParser::XMLParser()
{
}

XMLParser::~XMLParser()
{
	delete XMLDocument;
}

bool XMLParser::Initialize(string filename)
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

void XMLParser::BuildLevel()
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

	char* rowPositionX;
	char* rowPositionY;
	char* elementSizeX;
	char* elementSizeY;
	char* offset;
	string textureName;

	xml_node <> * root = doc.first_node();

	for (xml_node <> * branch_1 = root->first_node(); branch_1; branch_1 = branch_1->next_sibling()) 
	{ 
		rowPositionX = branch_1->first_attribute()->value();
		rowPositionY = branch_1->last_attribute()->value();

		cout << "Row: posX: " << rowPositionX << " posY: " << rowPositionY << endl;

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

			

			cout << "Element: sizeX: " << elementSizeX <<
				" sizeY: " << elementSizeY <<
				" offset: " << offset <<
				" textureName: " << textureName << endl;
		}
	}
	doc.clear(); // (12)
}

