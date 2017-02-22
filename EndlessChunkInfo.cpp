#include "EndlessChunkInfo.h"

EndlessChunkInfo::EndlessChunkInfo(std::string filePath)
{
	std::ifstream load(filePath);
	if (load.is_open())
	{
		load >> startingBlockLevel;
		load >> endingBlockLevel;
		getline(load, mapCode[0]);
		for (int i = 0; i < 15; i++)
		{
			getline(load, mapCode[i]);
		}
	}
	load.close();
}

void EndlessChunkInfo::getCode(std::string code[])
{
	for (int i = 0; i < 15; i++)
	{
		code[i] = mapCode[i];
	}
}

int EndlessChunkInfo::getStartingBlockLevel()
{
	return startingBlockLevel;
}

int EndlessChunkInfo::getEndingBlockLevel()
{
	return endingBlockLevel;
}

EndlessChunkInfo::~EndlessChunkInfo()
{
}
