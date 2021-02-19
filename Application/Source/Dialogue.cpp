#include "Dialogue.h"

Dialogue::Dialogue(std::string fileName) : totalLines(0), personTalking(""), currentLine(0)
{
	file.open(fileName);
	if (!file)
		std::cout << "Cannot open dialogue file" << std::endl;

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			++totalLines;
		}
	}

	file.close();

	file.open(fileName);
}

Dialogue::~Dialogue()
{
	file.close();
}

int Dialogue::getCurrentLine()
{
	return currentLine;
}

int Dialogue::getTotalLines()
{
	return totalLines;
}

std::string Dialogue::getPersonTalking()
{
	return personTalking;
}

std::string Dialogue::Update()
{
	char buf[300];
	file.getline(buf, 300);
	if (strncmp("1 ", buf, 2))
		personTalking = "Player";
	else if(strncmp("2 ", buf, 2))
		personTalking = "Boss Goose";
	else if (strncmp("3 ", buf, 2))
		personTalking = "Boss Duck";

	++currentLine;

	return std::string(buf + 2);
}