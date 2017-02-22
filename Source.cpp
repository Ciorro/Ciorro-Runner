#include <SFML\Graphics.hpp>
#include "Menu.h"
#include "SettingsManager.h"
#include <ctime>

int main(int argc,char *argv[])
{
	SettingsManager manager;
	//SettingsManager::godMode = true;
	if (argc > 1)
	{
		if (strcmp(argv[1], "god") == 0)
		{
			SettingsManager::godMode = true;
			printf("Godmode enabled.\n");
		}
	}
	std::cout << "_______________________________________\n";
	std::cout << "|                                     |\n";
	std::cout << "|            Ciorro Runner            |\n";
	std::cout << "|       by Yellow Squares Studio      |\n";
	std::cout << "|_____________________________________|\n";
	Menu menu;
	menu.init();
	menu.run();
	srand(time(NULL));
	return 0;
}