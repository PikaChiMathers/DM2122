#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Dialogue
{
private:
	unsigned mode;

	std::ifstream file;
	int currentLine;
	int totalLines;
	std::string personTalking;

	std::string choice[3];

public:
	enum MODE
	{
		DIALOGUE,
		TRIVIA,
	};

	Dialogue(std::string fileName, unsigned mode);
	~Dialogue();

	int getCurrentLine();
	int getTotalLines();
	std::string getPersonTalking();
	std::string Update();

	std::string getChoice1();
	std::string getChoice2();
	std::string getChoice3();
};