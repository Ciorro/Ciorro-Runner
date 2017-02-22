#include "Menu.h"


void Menu::selectPresetPack()
{
	Button back(win.getSize().x / 2 - 100, win.getSize().y - 60, Text("", font, 20), &font, "res/images/back.png");

	effect.startEffect(Effects::FADE_IN);
	Effects fadeOut(win.getSize().x, win.getSize().y);

	while (win.isOpen())
	{
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				win.close();
				exit(0);
			}
			if (back.isMouseOn(&win))
			{
				if (back.click(&event, &win))
				{
					fadeOut.startEffect(Effects::FADE_OUT);
				}
			}
		}
		effect.update();
		if (fadeOut.update() == Effects::ENDED)
		{
			break;
		}
		joystickSteering();
		cursor.setPosition(Mouse::getPosition(win).x, Mouse::getPosition(win).y);
		menuBg.rotate(0.1);
		win.clear();
		win.draw(menuBg);
		win.draw(back);
		win.draw(cursor);
		win.draw(effect);
		win.draw(fadeOut);
		win.display();
	}
}

void Menu::credits()
{
	Texture headerTex;
	headerTex.loadFromFile("res/images/ciorrorunner.png");
	Sprite header(headerTex);
	header.setPosition(win.getSize().x / 2 - header.getGlobalBounds().width / 2, 25);
	RectangleShape darkBg(Vector2f(win.getSize().x, win.getSize().y));
	darkBg.setFillColor(Color(0, 0, 0, 170));
	Button back(win.getSize().x / 2 - 100, win.getSize().y - 60, Text("", font, 20), &font, "res/images/back.png");

	std::vector<Text> credit = {
		Text("Programming:",arial,20),Text("Julian Zalewski\n\n",arial,20),Text(),
		Text("Music:",arial,20),
		Text("bart (opengameart.org)",arial,20),
		Text("BBandRage (opengameart.org)",arial,20),
		Text("Snabisch (opengameart.org)",arial,20),
		Text("Furtive Vinyl from Jukedeck - create your own at http://jukedeck.com",arial,20)
	};

	for (size_t i = 0; i < credit.size(); i++)
	{
		credit[i].setPosition(win.getSize().x / 2 - credit[i].getGlobalBounds().width / 2, win.getSize().y / 4 +i * 30);
	}

	effect.startEffect(Effects::FADE_IN);
	Effects fadeOut(win.getSize().x, win.getSize().y);

	while (win.isOpen())
	{
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				win.close();
				exit(0);
			}
			if (back.isMouseOn(&win))
			{
				if (back.click(&event, &win))
				{
					fadeOut.startEffect(Effects::FADE_OUT);
				}
			}
		}
		effect.update();
		if (fadeOut.update() == Effects::ENDED)
		{
			break;
		}
		joystickSteering();
		cursor.setPosition(Mouse::getPosition(win).x, Mouse::getPosition(win).y);
		menuBg.rotate(0.1);
		win.clear();
		win.draw(menuBg);
		win.draw(darkBg);
		win.draw(back);
		win.draw(header);
		
		for (size_t i = 0; i < credit.size(); i++)
		{
			win.draw(credit[i]);
		}

		win.draw(cursor);
		win.draw(effect);
		win.draw(fadeOut);
		win.display();
	}
}

void Menu::options()
{
	bool optionsOpened = true;
	enum NEXT{QUITOPTIONS,CONTROL};
	NEXT next;

	Text header("Options", font, 60);
	Text resLabel("Resolution", arial, 20);
	Text fullLabel("Fullscreen", arial, 20);
	Text soundsLabel("Sounds volume", arial, 20);
	Text musicLabel("Music volume", arial, 20);

	header.setPosition(win.getSize().x / 2 - header.getGlobalBounds().width / 2, 25);
	header.setStyle(Text::Underlined);
	Button back(win.getSize().x / 2 - 205, win.getSize().y - 60, Text("", arial, 20), &arial, "res/images/back.png");
	Button save(win.getSize().x / 2 + 5, win.getSize().y - 60, Text("", arial, 20), &arial, "res/images/save.png");
	Button controls(win.getSize().x / 2 - 205, win.getSize().y - 120, Text("", arial, 20), &arial, "res/images/controlssettings.png");

	TrackBar sounds(win.getSize().x / 2 + 5, 150, 200, 100);
	TrackBar music(win.getSize().x / 2 - 205, 150, 200, 100);
	sounds.setState(SettingsManager::loadSoundsVolume());
	music.setState(SettingsManager::loadMusicVolume());
	soundsLabel.setPosition(win.getSize().x / 2 + 5, 110);
	musicLabel.setPosition(win.getSize().x / 2 - 205, 110);

	DropDownList fullscreens(win.getSize().x / 2 + 5, 230, 200, 25, &arial);
	DropDownList resolutions(win.getSize().x / 2 - 205, 230, 200, 25, &arial);
	resLabel.setPosition(win.getSize().x / 2 - 205, 200);
	fullLabel.setPosition(win.getSize().x / 2 + 5, 200);

	std::vector<std::wstring> resList =
	{
		L"1024x768",L"1280x720",L"1280x768",L"1366x768",L"1440x900",L"1600x900",L"1680x1050",L"1920x1080"
	};
	std::vector<std::wstring> fullList =
	{
		L"Yes",L"No"
	};
	resolutions.setOptions(resList);
	fullscreens.setOptions(fullList);
	resolutions.setState(SettingsManager::loadResolutionListOptionNumber());
	fullscreens.setState(SettingsManager::loadResolution().z);

	effect.setEffectSize(win.getSize().x, win.getSize().y);
	effect.startEffect(Effects::FADE_IN);

	Effects fadeOut(win.getSize().x, win.getSize().y);

	while (optionsOpened)
	{
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				win.close();
				exit(0);
			}

			if (back.isMouseOn(&win))
			{
				if (back.click(&event, &win))
				{
					fadeOut.startEffect(Effects::FADE_OUT);
					next = QUITOPTIONS;
				}
			}
			if (controls.isMouseOn(&win))
			{
				if (controls.click(&event, &win))
				{
					fadeOut.startEffect(Effects::FADE_OUT);
					next = CONTROL;
				}
			}
			if (save.isMouseOn(&win))
			{
				if (save.click(&event, &win))
				{
					int optionsChoose = resolutions.getCurrentOption();
					int isFullscreen = fullscreens.getCurrentOption();
					int width, height;
					switch (optionsChoose)
					{
					case 1:
						width = 1024;
						height = 768;
						break;
					case 2:
						width = 1280;
						height = 720;
						break;
					case 3:
						width = 1280;
						height = 768;
						break;
					case 4:
						width = 1366;
						height = 768;
						break;
					case 5:
						width = 1440;
						height = 900;
						break;
					case 6:
						width = 1600;
						height = 900;
						break;
					case 7:
						width = 1680;
						height = 1050;
						break;
					case 8:
						width = 1920;
						height = 1080;
						break;
					default:
						width = 1680;
						height = 1050;
						break;
					}

					if (isFullscreen==1)
						win.create(VideoMode(width, height), L"Ciorro Runner", Style::Fullscreen);
					else
						win.create(VideoMode(width, height), L"Ciorro Runner", Style::Close);
					win.setVerticalSyncEnabled(true);
					menuBg.setPosition(win.getSize().x / 2, win.getSize().y / 2);
					win.setMouseCursorVisible(false);

					SettingsManager::save(sounds.getState(), music.getState(), width, height, isFullscreen, optionsChoose);
					mainTheme.setVolume(SettingsManager::loadMusicVolume());
				
					Image icon;
					icon.loadFromFile("res/images/icon.png");
					win.setIcon(128, 128, icon.getPixelsPtr());
					run();
				}
			}
			resolutions.handle(&event, &win);
			fullscreens.handle(&event, &win);
			sounds.handle(&win);
			music.handle(&win);
		}
		effect.update();
		if (fadeOut.update() == Effects::ENDED)
		{
			break;
		}
		cursor.setPosition(Mouse::getPosition(win).x, Mouse::getPosition(win).y);
		joystickSteering();
		menuBg.rotate(0.1);
		win.clear();
		win.draw(menuBg);
		win.draw(header);
		win.draw(controls);
		win.draw(back);
		win.draw(save);
		win.draw(resolutions);
		win.draw(fullscreens);
		win.draw(resLabel);
		win.draw(fullLabel);
		win.draw(sounds);
		win.draw(music);
		win.draw(soundsLabel);
		win.draw(musicLabel);
		win.draw(cursor);
		win.draw(effect);
		win.draw(fadeOut);
		win.display();
	}
	if (next == CONTROL)
	{
		controlSettings();
		options();
	}
}

void Menu::selectLvl()
{
	enum nextMenu { MAIN, SELECT_PRESET};
	nextMenu next;

	bool selectIsOpen = true;

	Text header("Select level", font, 60);
	header.setPosition(win.getSize().x / 2 - header.getGlobalBounds().width / 2, 25);
	header.setStyle(Text::Underlined);

	Button back(win.getSize().x / 2 - 100, win.getSize().y - 60, Text("", font, 20), &font, "res/images/back.png");
	Button endlessMode(win.getSize().x / 2 - 100, win.getSize().y - 120, Text("", font, 20), &font, "res/images/endlessmodebutton.png");

	std::vector<int>unlockedLevels;
	std::fstream loadUnlockedLevels("res/save.crsav", std::ios::in);
	if (loadUnlockedLevels.is_open())
	{
		while (!loadUnlockedLevels.eof())
		{
			int level;
			loadUnlockedLevels >> level;
			unlockedLevels.push_back(level);
		}
	}
	loadUnlockedLevels.close();

	std::vector<Button*> lvlButton;
	std::vector<std::string> maps;
	std::fstream loadMapNames("res/maps/maplist.crs", std::ios::in);

	effect.startEffect(Effects::FADE_IN);
	Effects fadeOut(win.getSize().x, win.getSize().y);

	if (loadMapNames.is_open())
	{
		int lines = 0;

		while (!loadMapNames.eof())
		{
			std::string mapName;
			getline(loadMapNames, mapName);
			maps.push_back(mapName);
			lines++;
		}
		int x = win.getSize().x/2-150, y = 140;

		for(int i=1;i<=lines;i++)
		{
			lvlButton.push_back(new Button(x, y, Text(std::to_string(i), font, 20), &font, "res/images/lvl.png"));
			bool unlocked = false;
			for (size_t j = 0; j < unlockedLevels.size(); j++)
			{
				if (unlockedLevels[j] == i-1)//because i=1 in loop
					unlocked = true;
			}
			lvlButton.back()->setActive(unlocked);
			x += 50;
			if (i % 6 == 0)
			{
				x = win.getSize().x / 2 - 150;
				y += 50;
			}
		}
	}


	while (selectIsOpen)
	{
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				win.close();
				exit(0);
			}
			if (back.isMouseOn(&win))
			{
				if (back.click(&event, &win))
				{
					fadeOut.startEffect(Effects::FADE_OUT);
					next = MAIN;
				}
			}
			if (endlessMode.isMouseOn(&win))
			{
				if (endlessMode.click(&event, &win))
				{
					/*fadeOut.startEffect(Effects::FADE_OUT);
					next = SELECT_PRESET;*/
					mainTheme.stop();
					game.init(&win, &font, maps[0], 0, true);
					game.run();
					win.setView(win.getDefaultView());
					mainTheme.play();
					while (win.pollEvent(event));
				}
			}
			for (size_t i = 0; i < lvlButton.size(); i++)
			{
				if (lvlButton[i]->isMouseOn(&win))
				{
					if (lvlButton[i]->click(&event, &win))
					{
						mainTheme.stop();
						game.init(&win, &font, maps[i], i, false);
						if (game.run())
						{
							if(lvlButton[i]!=lvlButton.back())
								lvlButton[i+1]->setActive(true);
						}
						win.setView(win.getDefaultView());
						mainTheme.play();
						while (win.pollEvent(event));
					}
				}
			}
		}
		effect.update();
		if (fadeOut.update() == Effects::ENDED)
		{
			break;
		}
		cursor.setPosition(Mouse::getPosition(win).x, Mouse::getPosition(win).y);
		joystickSteering();
		menuBg.rotate(0.1);
		win.clear();
		win.draw(menuBg);
		win.draw(back);
		win.draw(endlessMode);
		win.draw(header);
		for (size_t i = 0; i < lvlButton.size(); i++)
		{
			win.draw(*lvlButton[i]);
		}
		win.draw(cursor);
		win.draw(effect);
		win.draw(fadeOut);
		win.display();
	}
	if (next == MAIN)
		return;
	else
	{
		selectPresetPack();
		selectLvl();
	}
}

void Menu::splahses()
{
	int logo = 0;
	win.setMouseCursorVisible(false);

	Texture sfmlTex;
	sfmlTex.loadFromFile("res/images/sfml.png");
	Sprite sfml(sfmlTex);
	sfml.setPosition(win.getSize().x / 2 - sfml.getGlobalBounds().width / 2, win.getSize().y / 2 - sfml.getGlobalBounds().height / 2);
	sfml.setColor(Color::Transparent);

	Texture yssTex;
	yssTex.loadFromFile("res/images/yss.png");
	Sprite yss(yssTex);
	yss.setPosition(win.getSize().x / 2 - yss.getGlobalBounds().width / 2, win.getSize().y/2-yss.getGlobalBounds().height/2);
	yss.setColor(Color::Transparent);

	Texture headerTex;
	headerTex.loadFromFile("res/images/ciorrorunner.png");
	Sprite header(headerTex);
	header.setPosition(win.getSize().x / 2 - header.getGlobalBounds().width / 2, win.getSize().y / 2 - header.getGlobalBounds().height / 2);
	header.setColor(Color::Transparent);
	while (win.isOpen())
	{
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				win.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				logo = 6;
			}
		}
		win.clear();
		if (logo == 0)
		{
			win.draw(sfml);
			if (sfml.getColor().a == 255)
			{
				logo++;
				sleep(seconds(2));
			}
			sfml.setColor(Color(255, 255, 255, sfml.getColor().a + 17));
		}
		if (logo == 1)
		{
			win.draw(sfml);
			if (sfml.getColor().a == 0)
			{
				logo++;
				//sleep(seconds(2));
			}
			sfml.setColor(Color(255, 255, 255, sfml.getColor().a - 17));
		}
		if (logo == 2)
		{
			win.draw(yss);
			if (yss.getColor().a == 255)
			{
				logo++;
				sleep(seconds(2));
			}
			yss.setColor(Color(255, 255, 255, yss.getColor().a + 17));
		}
		if (logo == 3)
		{
			win.draw(yss);
			if (yss.getColor().a == 0)
			{
				logo++;
				//sleep(seconds(2));
			}
			yss.setColor(Color(255, 255, 255, yss.getColor().a - 17));
		}
		if (logo == 4)
		{
			win.draw(header);
			if (header.getColor().a == 255)
			{
				logo++;
				sleep(seconds(2));
			}
			header.setColor(Color(255, 255, 255, header.getColor().a + 17));
		}
		if (logo == 5)
		{
			win.draw(header);
			if (header.getColor().a == 0)
			{
				logo++;
				//sleep(seconds(1));
			}
			header.setColor(Color(255, 255, 255, header.getColor().a - 17));
		}
		if (logo == 6)break;
		win.display();
	}
	////win.setMouseCursorVisible(false);
}

void Menu::joystickSteering()
{
	if (SettingsManager::isJoystickConnected())
	{
		//printf("%f|%f\n",Joystick::getAxisPosition(SettingsManager::joystickId,Joystick::Axis::X), Joystick::getAxisPosition(SettingsManager::joystickId, Joystick::Axis::Y));
		if (Joystick::hasAxis(SettingsManager::joystickId, Joystick::Axis::X) && abs(Joystick::getAxisPosition(SettingsManager::joystickId, Joystick::Axis::X)) > 30)
		{
			Mouse::setPosition(Vector2i(Mouse::getPosition(win).x + Joystick::getAxisPosition(SettingsManager::joystickId, Joystick::Axis::X) / 10, Mouse::getPosition(win).y), win);
		}
		if (Joystick::hasAxis(SettingsManager::joystickId, Joystick::Axis::Y) && abs(Joystick::getAxisPosition(SettingsManager::joystickId, Joystick::Axis::Y)) > 30)
		{
			Mouse::setPosition(Vector2i(Mouse::getPosition(win).x, Mouse::getPosition(win).y + Joystick::getAxisPosition(SettingsManager::joystickId, Joystick::Axis::Y) / 10), win);
		}
		if (Joystick::isButtonPressed(SettingsManager::joystickId, 0))
		{
			mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}

	}
}

void Menu::controlSettings()
{
	SettingsManager::loadKeys();
	
	Text header("Controls", font, 60);
	header.setPosition(win.getSize().x / 2 - header.getGlobalBounds().width / 2, 25);
	header.setStyle(Text::Underlined);

	Button back(win.getSize().x / 2 - 100, win.getSize().y - 60, Text("", font, 20), &font, "res/images/back.png");
	Button toDefaults(win.getSize().x / 2 - 205, win.getSize().y - 120, Text("", font, 20), &font, "res/images/todefaultbutton.png");

	bool checkedButton[6]{ false, false, false, false, false, false };//here
	int keys[6] = { SettingsManager::turnLeftKey , SettingsManager::turnRightKey,SettingsManager::jumpKey,SettingsManager::slowmotionKey,SettingsManager::downKey,SettingsManager::runKey };//here

	std::vector<Button*> options = {
		new Button (win.getSize().x / 2 - 205, 200, Text("", font, 25), &font, "res/images/slowdownoptionbutton.png"),
		new Button (win.getSize().x / 2 - 205, 260, Text("", font, 25), &font, "res/images/accelerateoptionbutton.png"),
		new Button (win.getSize().x / 2 - 205, 320, Text("", font, 25), &font, "res/images/jumpoptionbutton.png"),
		new Button (win.getSize().x / 2 - 205, 380, Text("", font, 25), &font, "res/images/slowmotionoptionbutton.png"),
		new Button(win.getSize().x / 2 - 205, 440, Text("", font, 25), &font, "res/images/punchdownoptionbutton.png"),
		new Button(win.getSize().x / 2 - 205, 500, Text("", font, 25), &font, "res/images/runoptionbutton.png")
		//here
	};

	effect.startEffect(Effects::FADE_IN);
	Effects fadeOut(win.getSize().x, win.getSize().y);

	while (win.isOpen())
	{
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				win.close();
				exit(0);
			}
			if (toDefaults.isMouseOn(&win))
			{
				if (toDefaults.click(&event, &win))
				{
					keys[0] = 71;
					keys[1] = 72;
					keys[2] = 57;
					keys[3] = 19;
					keys[4] = 74;
					keys[5] = 38;
					//here
					SettingsManager::saveKeys(); 
				}
			}
			if (back.isMouseOn(&win))
			{
				if (back.click(&event, &win))
				{
					fadeOut.startEffect(Effects::FADE_OUT);
				}
			}
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Right)
			{
				checkedButton[0] = checkedButton[1] = checkedButton[2] = checkedButton[3] = checkedButton[4] = checkedButton[5] = false;//here
			}
			for (size_t i = 0; i < options.size(); i++)
			{
				if (options[i]->isMouseOn(&win))
				{
					if (options[i]->click(&event, &win))
					{
						checkedButton[0] = checkedButton[1] = checkedButton[2] = checkedButton[3] = checkedButton[4] = checkedButton[5] = false;//here
						checkedButton[i] = true;
					}
				}
				if (event.type == Event::KeyPressed)
				{
					for (size_t j = 0; j < options.size(); j++)
					{
						if (checkedButton[i] == true)
						{
							keys[i] = event.key.code;
							checkedButton[0] = checkedButton[1] = checkedButton[2] = checkedButton[3] = checkedButton[4] = checkedButton[5] = false;//here
						}
					}
				}
			}
		}

		effect.update();
		if (fadeOut.update() == Effects::ENDED)
		{
			SettingsManager::turnLeftKey = keys[0];
			SettingsManager::turnRightKey = keys[1];
			SettingsManager::jumpKey = keys[2];
			SettingsManager::slowmotionKey = keys[3];
			SettingsManager::downKey = keys[4];
			SettingsManager::runKey = keys[5];
			//here
			SettingsManager::saveKeys();
			break;
		}

		joystickSteering();
		cursor.setPosition(Mouse::getPosition(win).x, Mouse::getPosition(win).y);
		menuBg.rotate(0.1);
		win.clear();
		win.draw(menuBg);
		win.draw(header);
		win.draw(back);
		win.draw(toDefaults);
		for (size_t i = 0; i < options.size(); i++)
		{
			if (checkedButton[i])
				options[i]->setColor(Color(120, 120, 120));
			else
				options[i]->setColor(Color::White);
			win.draw(*options[i]);
		}
		win.draw(cursor);
		win.draw(effect);
		win.draw(fadeOut);
		win.display();
	}
}

void Menu::checkUpdates()
{
	sf::Http http;
	http.setHost("http://www.yss.ct8.pl/");

	sf::Http::Request request("cr_version.ini");

	sf::Http::Response response = http.sendRequest(request);

	sf::Http::Response::Status status = response.getStatus();
	if (status == sf::Http::Response::Ok)
	{
		float newestVersion = std::stof(response.getBody());
		float currentVersion = std::stof(SettingsManager::getGameVersion());
		std::cout << "Current version: " << currentVersion << "\nNewest version: " << newestVersion << std::endl;
		if (currentVersion < newestVersion)
		{
			std::cout << "Update available! You can download it from yss.ct8.pl.\n";
			isUpdateAvailable = true;
		}
	}
	else
	{
		std::cout << "Error while checking for updates. Failed to handle game version file. Status: " << status << std::endl;
	}
}

Menu::Menu()
{
}

void Menu::init()
{
	ContextSettings settings(0, 0, 8);
	Image icon;
	icon.loadFromFile("res/images/icon.png");
	int fullscr = SettingsManager::loadResolution().z;
	win.create(VideoMode(SettingsManager::loadResolution().x, SettingsManager::loadResolution().y), "Ciorro Runner", (fullscr<2)?Style::Fullscreen : Style::Close, settings);
	win.setIcon(128, 128, icon.getPixelsPtr());
	//win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);

	font.loadFromFile("res/fonts/gyparody_rg.ttf");
	arial.loadFromFile("res/fonts/arial.ttf");
	
	menuBgTex.loadFromFile("res/images/menuBackground.png");
	menuBgTex.setSmooth(true);
	menuBg.setTexture(menuBgTex);
	menuBg.setOrigin(menuBg.getGlobalBounds().width / 2, menuBg.getGlobalBounds().height / 2);
	menuBg.setPosition(win.getSize().x / 2, win.getSize().y / 2);

	cursorTex.loadFromFile("res/images/cursor.png");
	cursor.setTexture(cursorTex);
	
	mainTheme.openFromFile("res/music/Jump_and_Run.ogg");
	mainTheme.setLoop(true);
	mainTheme.setVolume(SettingsManager::loadMusicVolume());
	mainTheme.play();

	isUpdateAvailable = false;

	splahses();
	checkUpdates();
}

void Menu::run()
{
	enum nextMenu{OPTIONS,CREDITS,SELECT};
	nextMenu next;

	Button startGame(win.getSize().x / 2 - 250, 720 / 2, Text("", font, 25), &font, "res/images/startbutton.png");
	//Button multiplayerGame(win.getSize().x / 2 - 250, 720 / 2 + 75, Text("", font, 25), &font, "res/images/multiplayerbutton.png");
	Button optionsButton(win.getSize().x / 2 - 250, 720 / 2 + 75, Text("", font, 25), &font, "res/images/optionsbutton.png");
	Button endGame(win.getSize().x / 2 - 250, 720 / 2 + 150, Text("", font, 25), &font, "res/images/quitbutton.png");
	Button enterCredits(win.getSize().x - 50, win.getSize().y - 50, Text("", font, 25), &font, "res/images/creditsbutton.png");
	Button downloadUpdate(win.getSize().x / 2 - 250, win.getSize().y - 60, Text("", font, 25), &font, "res/images/downloadupdatebutton.png");

	//multiplayerGame.setActive(false);

	Texture headerTex;
	headerTex.loadFromFile("res/images/ciorrorunner.png");
	Sprite header(headerTex);
	header.setPosition(win.getSize().x / 2 - header.getGlobalBounds().width / 2, 25);

	Text version("Ciorro Runner beta "+SettingsManager::getGameVersion(), arial, 20);///VERSION
	version.setPosition(5, win.getSize().y - 25);
	
	Text upToDateInfo("Your game is up-to-date", font, 22);
	upToDateInfo.setPosition(win.getSize().x / 2 - upToDateInfo.getGlobalBounds().width / 2, win.getSize().y - 60);

	effect.setEffectSize(win.getSize().x, win.getSize().y);
	effect.startEffect(Effects::FADE_IN);

	Effects fadeOut(win.getSize().x, win.getSize().y);

	while (win.isOpen())
	{
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				win.close();
				exit(0);
			}
			if (startGame.isMouseOn(&win))
			{
				if (startGame.click(&event, &win))
				{
					next = SELECT;
					fadeOut.startEffect(Effects::FADE_OUT);
				}
			}
			if (optionsButton.isMouseOn(&win))
			{
				if (optionsButton.click(&event, &win))
				{
					next = OPTIONS;
					fadeOut.startEffect(Effects::FADE_OUT);
				}
			}
			if (endGame.isMouseOn(&win))
			{
				if (endGame.click(&event, &win))
				{
					win.close();
					exit(0);
				}
			}
			/*if (multiplayerGame.isMouseOn(&win))
			{
				if (multiplayerGame.click(&event, &win))
				{
					win.close();
					exit(0);
				}
			}*/
			if (downloadUpdate.isMouseOn(&win) && isUpdateAvailable)
			{
				if (downloadUpdate.click(&event, &win))
				{
					ShellExecute(NULL, "open", "http://www.yss.ct8.pl/", "", "", SW_SHOWNORMAL);
				}
			}
			if (enterCredits.isMouseOn(&win))
			{
				if (enterCredits.click(&event, &win))
				{
					next = CREDITS;
					fadeOut.startEffect(Effects::FADE_OUT);
				}
			}
		}
		
		effect.update();
		if (fadeOut.update() == Effects::ENDED)
		{
			break;
		}
		cursor.setPosition(Mouse::getPosition(win).x, Mouse::getPosition(win).y);
		joystickSteering();
		menuBg.rotate(0.1);
		win.clear(Color(100,100,100));
		win.draw(menuBg);
		win.draw(header);
		win.draw(startGame);
		//win.draw(multiplayerGame);
		win.draw(optionsButton);
		win.draw(endGame);
		if (isUpdateAvailable)
		{
			win.draw(downloadUpdate);
		}
		else
		{
			win.draw(upToDateInfo);
		}
		win.draw(enterCredits);
		win.draw(version);
		win.draw(cursor);
		win.draw(effect);
		win.draw(fadeOut);
		win.display();
	}
	switch (next)
	{
	case OPTIONS:
		options();
		break;
	case CREDITS:
		credits();
		break;
	case SELECT:
		selectLvl();
		break;
	}
	run();
}


Menu::~Menu()
{
}