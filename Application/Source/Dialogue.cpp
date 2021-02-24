#include "Dialogue.h"

Dialogue::Dialogue(std::string fileName, unsigned mode) : totalLines(0), personTalking(""), currentLine(0), mode(mode)
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
	if (mode == DIALOGUE)
	{
		char buf[300];
		file.getline(buf, 300);
		if (strncmp("1 ", buf, 2))
			personTalking = "Player";
		else if (strncmp("2 ", buf, 2))
			personTalking = "Boss Goose";
		else if (strncmp("3 ", buf, 2))
			personTalking = "Boss Duck";

		++currentLine;

		return std::string(buf + 2);
	}
	else if (mode == TRIVIA)
	{
		++currentLine;

		std::string line;
		std::getline(file, line);

		for (int i = 0; i < 3; ++i)
		{
			std::string choice;
			std::getline(file, choice);
			this->choice[i] = choice;
		}

		return line;
	}
	else
	{
		std::cout << "Mode is not is listed" << std::endl;
	}
}

std::string Dialogue::getChoice1()
{
	return choice[1];
}

std::string Dialogue::getChoice2()
{
	return choice[2];
}

std::string Dialogue::getChoice3()
{
	return choice[3];
}