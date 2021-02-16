#include "Dialogue.h"

Dialogue::Dialogue(std::string fileName) : totalLines(0)
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

std::string Dialogue::Update()
{
	std::string line;
	std::getline(file, line);
	return line;
}