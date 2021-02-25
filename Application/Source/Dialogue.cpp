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
		std::string line;
		std::getline(file, line);

		if (currentLine == 0)
		{
			++currentLine;
		}
		else
		{
			for (int i = 0; i < 3; ++i)
			{
				std::string choice;
				std::getline(file, choice);
				this->choice[i] = choice;
			}

			char buf[50];
			file.getline(buf, 50);
			answer = std::string(buf + 4);

			currentLine += 5;
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
	if (mode == TRIVIA)
		return choice[0];
	else
	{
		std::cout << "Not in dialogue mode" << std::endl;
		return "";
	}
}

std::string Dialogue::getChoice2()
{
	if (mode == TRIVIA)
		return choice[1];
	else
	{
		std::cout << "Not in dialogue mode" << std::endl;
		return "";
	}
}

std::string Dialogue::getChoice3()
{
	if (mode == TRIVIA)
		return choice[2];
	else
	{
		std::cout << "Not in dialogue mode" << std::endl;
		return "";
	}
}

std::string Dialogue::getAnswer()
{
	return answer;
}
