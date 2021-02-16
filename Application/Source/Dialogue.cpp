#include "Dialogue.h"

Dialogue::Dialogue(std::string fileName) : totalLines(0), personTalking("")
{
	file.open(fileName);
	if (!file)
		std::cout << "Cannot open dialogue file" << std::endl;

	if (file.is_open())
		while (file.eof())
			++totalLines;

	file.close();

	file.open(fileName);
}

Dialogue::~Dialogue()
{
	file.close();
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
	char buf[2];
	file.getline(buf, 2);
	if (strncmp(buf, "1 ", 2))
		personTalking = "Player";
	else if(strncmp(buf, "2 ", 2))
		personTalking = "Boss Goose";
	else if (strncmp(buf, "3 ", 2))
		personTalking = "Boss Duck";

	std::string line;
	std::getline(file, line);
	return line;
}