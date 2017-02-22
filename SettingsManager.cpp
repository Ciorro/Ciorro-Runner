#include "SettingsManager.h"

unsigned int SettingsManager::soundsVolume = 0;
unsigned int SettingsManager::musicVolume = 0;
unsigned short SettingsManager::joystickId = 0;
FloatRect SettingsManager::renderingSize;
int SettingsManager::turnLeftKey = 0;
int SettingsManager::turnRightKey = 0;
int SettingsManager::jumpKey = 0;
int SettingsManager::downKey = 0;
int SettingsManager::runKey = 0;
int SettingsManager::slowmotionKey = 0;
bool SettingsManager::godMode = false;
std::string SettingsManager::version = "1.6";
bool SettingsManager::isJoystick = false;

SettingsManager::SettingsManager()
{
	for (short i = 0; i < 8; i++)
	{
		sf::Joystick::update();
		if (sf::Joystick::isConnected(i))
		{
			SettingsManager::isJoystick = true;
			SettingsManager::joystickId = i;
		}
	}
	SettingsManager::renderingSize = FloatRect(0, 0, 1680, 1050);
}

void SettingsManager::save(int sounds, int music, int scrWidth, int scrHeight, int fullscr, int optionNumber)
{
	std::fstream save("res/settings.crs", std::ios::out);
	save << sounds << std::endl << music << std::endl << scrWidth << std::endl << scrHeight << std::endl << fullscr << std::endl << optionNumber;
	save.close();
}

int SettingsManager::loadSoundsVolume()
{
	int sounds = 0;
	std::fstream load("res/settings.crs", std::ios::in);
	if (load.is_open())
	{
		load >> sounds;
	}
	soundsVolume = sounds;
	load.close();
	return sounds;
}

int SettingsManager::loadMusicVolume()
{
	int music = 0;
	std::fstream load("res/settings.crs", std::ios::in);
	if (load.is_open())
	{
		load >> music;
		load >> music;
	}
	musicVolume = music;
	load.close();
	return music;
}

sf::Vector3i SettingsManager::loadResolution()
{
	sf::Vector3i res;
	std::fstream load("res/settings.crs", std::ios::in);
	if (load.is_open())
	{
		load >> res.x;
		load >> res.x;
		load >> res.x;
		load >> res.y;
		load >> res.z;
	}
	load.close();
	return res;
}

int SettingsManager::loadResolutionListOptionNumber()
{
	int no;
	std::fstream load("res/settings.crs", std::ios::in);
	if (load.is_open())
	{
		for(int i=0;i<6;i++)
			load >> no;
	}
	load.close();
	return no;
}

bool SettingsManager::isJoystickConnected()
{
	return isJoystick;
}

std::string SettingsManager::getGameVersion()
{
	return version;
}


void SettingsManager::loadKeys()
{
	std::ifstream load("res/keys.crs");
	if (load.is_open())
	{
		load >> turnLeftKey;
		load >> turnRightKey;
		load >> jumpKey;
		load >> slowmotionKey;
		load >> downKey;
		load >> runKey;
	}
	load.close();
}

void SettingsManager::saveKeys()
{
	std::ofstream saveKey("res/keys.crs");
	if (saveKey.is_open())
	{
		saveKey << turnLeftKey << std::endl;
		saveKey << turnRightKey << std::endl;
		saveKey << jumpKey << std::endl;
		saveKey << slowmotionKey << std::endl;
		saveKey << downKey << std::endl;
		saveKey << runKey << std::endl;
	}
	saveKey.close();
}

SettingsManager::~SettingsManager()
{
}
