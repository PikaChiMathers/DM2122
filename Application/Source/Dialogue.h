#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Dialogue
{
private:
	unsigned mode;				//dialogue/trivia mode 

	std::ifstream file;			//file to be kept open while dialogue/trivia is running
	int currentLine;			//used to check if file eof
	int totalLines;				//used to check if file eof
	std::string personTalking;	//for dialogue, indicates character talking

	std::string choice[3];		//for trivia, holds all 3 choices
	std::string answer;			//for trivia, correct answer

public:
	enum MODE
	{
		DIALOGUE,
		TRIVIA,
	};

	Dialogue(std::string fileName, unsigned mode);
	~Dialogue();

	std::string Update();	//returns next speech/question for dialogue/trivia respectively

	int getCurrentLine();
	int getTotalLines();
	std::string getPersonTalking();

	std::string getChoice1();
	std::string getChoice2();
	std::string getChoice3();
	std::string getAnswer();
};