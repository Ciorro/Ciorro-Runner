#pragma once
#include <fstream>
#include <SFML\Graphics.hpp>

using namespace sf;

class SettingsManager
{
	static bool isJoystick;
public:
	static unsigned int soundsVolume;
	static unsigned int musicVolume;
	static unsigned short joystickId;
	static FloatRect renderingSize;
	//keys
	static int turnLeftKey;
	static int turnRightKey;
	static int jumpKey;
	static int slowmotionKey;
	static int downKey;
	static int runKey;

	static bool godMode;
	SettingsManager();
	static void save(int sounds, int music, int scrWidth, int scrHeight, int fullscr, int optionNumber);
	static int loadSoundsVolume();
	static int loadMusicVolume();
	static sf::Vector3i loadResolution();
	static int loadResolutionListOptionNumber();
	static bool isJoystickConnected();
	static std::string getGameVersion();
	static std::string version;
	static void loadKeys();
	static void saveKeys();
	~SettingsManager();
};

