#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Dialogue
{
private:
	std::ifstream file;
	int currentLine;
	int totalLines;
	std::string personTalking;

public:
	Dialogue(std::string fileName);
	~Dialogue();

	int getCurrentLine();
	int getTotalLines();
	std::string getPersonTalking();
	std::string Update();
};