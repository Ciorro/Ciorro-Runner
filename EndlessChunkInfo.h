#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class EndlessChunkInfo
{
	int startingBlockLevel, endingBlockLevel;
	std::string mapCode[15];
public:
	EndlessChunkInfo(std::string filePath);
	void getCode(std::string code[]);
	int getStartingBlockLevel();
	int getEndingBlockLevel();
	~EndlessChunkInfo();
};

