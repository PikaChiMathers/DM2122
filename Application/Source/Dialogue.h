#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Dialogue
{
private:
	std::ifstream file;
	int totalLines;
	std::string personTalking;

public:
	Dialogue(std::string fileName);
	~Dialogue();

	int getTotalLines();
	std::string getPersonTalking();
	std::string Update();
};